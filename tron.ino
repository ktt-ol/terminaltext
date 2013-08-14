#include <SoftwareSerial.h>
#include "screen.h"
#include "textappear.h"
#include "PSPad.h"

// \033[?7l disable autowrap
// \033[4h enable insert mode


typedef enum {
    NONE=0, LEFT=1, RIGHT, UP, DOWN
} directions_t;

directions_t padDirection(PSPad *pad) {
    if (pad->pressedLeft())
        return LEFT;
    else if (pad->pressedRight())
        return RIGHT;
    else if (pad->pressedUp())
        return UP;
    else if (pad->pressedDown())
        return DOWN;
    else
        return NONE;
}

class ScreenMask {
    byte *screen_bytes;
    int width;
    int height;
    int y_stride;
public:
    ScreenMask(int width, int height) :
        width(width), height(height), y_stride(width / 8)
    {
        screen_bytes = (byte *)calloc(sizeof(byte), y_stride * height);
    }

    ~ScreenMask() {
        free(screen_bytes);
    }

    void set(int x, int y) {
        byte x_byte = x / 8;
        screen_bytes[y * y_stride + x_byte] |= 1 << (x % 8);
    }
    bool isSet(int x, int y) {
        byte x_byte = x / 8;
        return (screen_bytes[y * y_stride + x_byte] & (1 << (x % 8))) >= 1;
    }

    void clear() {
        memset(screen_bytes, 0, y_stride * height);
    }

};

void limitToScreen(int *x, int *y, Screen *screen) {
        if (*x < 0) {
            *x = screen->width - 1;
        } else if (*x >= screen->width) {
            *x = 0;
        }

        if (*y < 0) {
            *y = screen->height - 1;
        } else if (*y >= screen->height) {
            *y = 0;
        }
}

void updatePos(int *x, int*y, directions_t direction) {
    switch (direction) {
        case LEFT:
            *x -= 1;
            break;
        case RIGHT:
            *x += 1;
            break;
        case UP:
            *y -= 1;
            break;
        case DOWN:
            *y += 1;
            break;
    }
}

bool sameOrOpositeDirection(directions_t a, directions_t b) {
    if (a == b) {
        return true;
    }

    if (a >= UP && b >= UP) {
        return true;
    }
    if (a < UP && a >= LEFT && b < UP && b >= LEFT) {
        return true;
    }

    return false;
}

class Snake {
public:
    int x;
    int y;
    directions_t direction;
    PSPad *pad;
    char symb;
    long points;
    bool dead;
    bool active;
    bool moved;
    bool autoPilot;

    Snake(int x, int y, directions_t dir, char symb, PSPad *pad) :
        x(x), y(y), direction(dir), symb(symb),
        points(0), dead(false), active(false), moved(false),
        autoPilot(false), pad(pad)
    {};

    void updateController() {
        pad->update();
        directions_t dir = padDirection(pad);
        if (dir != NONE || sameOrOpositeDirection(dir, direction)) {
            direction = dir;
        }
    }

    void move(Screen *screen) {
        updatePos(&x, &y, direction);
        limitToScreen(&x, &y, screen);

        screen->put(symb, x, y);
    };

};

void welcomeScreen();


// SoftwareSerial(RX, TX) (MAX232 Pins: 9/10, 12/11)
SoftwareSerial mySerial1(2, 3);
SoftwareSerial mySerial2(5, 4);
TermScreen screen1(&mySerial1);
TermScreen screen2(&mySerial2);
ScreenWall screen = ScreenWall();

PSPad pad1(10, 9, 12, 11, PSPAD_MULTITAP_PAD1);
PSPad pad2(10, 9, 12, 11, PSPAD_MULTITAP_PAD2);
PSPad pad3(10, 9, 12, 11, PSPAD_MULTITAP_PAD3);
PSPad pad4(10, 9, 12, 11, PSPAD_MULTITAP_PAD4);

Snake snake1(10, 12, RIGHT, 'A', &pad1);
Snake snake2(70, 12, LEFT,  'B', &pad2);
Snake snake3(10, 12, RIGHT, 'C', &pad3);
Snake snake4(70, 12, LEFT,  'D', &pad4);

ScreenMask visited(2*DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

text_appear_t text_appear;

Snake *snakes[] = {&snake1, &snake2, &snake3, &snake4};

void setup()
{
    // wait for terminals to boot
    delay(1000);

    screen.addScreen(&screen1);
    screen.addScreen(&screen2);

    // pinMode(13, OUTPUT);
    // digitalWrite(13, HIGH);
    Serial.begin(9600);
    // 1 - brown - data
    // 2 - orange - command
    // 4 - black - gnd
    // 5 - red - vcc
    // 6 - yellow - att
    // 7 - blue - clock
    // 9 - green - ack

    // Data Pin #, CMND Pin #, ATT Pin #, CLK Pin #
    // psc.setupPins(6, 7, 10, 8, 50);

    mySerial1.begin(9600);
    mySerial2.begin(9600);

    // \033[4h enable insert mode
    screen1.clear();
    delay(200);

    screen1.init("\033[4l");
    screen1.init("\033[3;4z");
    // screen1.init("\033[?5l");
    screen1.init("\033[1;1Z");

    screen2.clear();
    delay(200);
    screen2.init("\033[4l");
    screen2.init("\033[3;4z");
    // screen2.init("\033[?5l");
    screen2.init("\033[1;1Z");

    delay(500);

    // welcomeScreen();
}

directions_t padDirectionButtons(PSPad *pad) {
    if (pad->pressedSquare())
        return LEFT;
    else if (pad->pressedCircle())
        return RIGHT;
    else if (pad->pressedTriangle())
        return UP;
    else if (pad->pressedCross())
        return DOWN;
    else
        return NONE;
}

char tmp_buf[7];
char *itos(int i) {
    snprintf(&tmp_buf[0], sizeof(tmp_buf), "%d", i);
    return &tmp_buf[0];
}

typedef enum {
    RUNNING, DEAD, STOP
} game_status_t;

typedef enum {
    SPEED_RUN, RUN
} game_loop_mode_t;

#define FOREACH_SNAKE(s) \
    for (int s ## _i=0; s ## _i < 4; s ## _i++) { \
        Snake *s = snakes[s ## _i];

#define FOREACH_ACTIVE_SNAKE(s) \
    for (int s ## _i=0; s ## _i < 4; s ## _i++) { \
        Snake *s = snakes[s ## _i]; \
        if (!s->active) { \
            continue; \
        }

game_status_t gameLoop(game_loop_mode_t mode) {
    FOREACH_ACTIVE_SNAKE(snake)
        if (snake->pad->pressedStart()) {
            return STOP;
        }
    }

    // handle movement
    FOREACH_ACTIVE_SNAKE(snake)
        if (snake->dead) {
            continue;
        }
        snake->updateController();
        if (mode == RUN || (mode == SPEED_RUN && snake->pad->pressedCross())) {
            snake->move(&screen);
            snake->moved = true;
            snake->points += 1;
        } else {
            snake->moved = false;
        }
    }

    // check hits between two snakes
    for (int i=0; i < 4; i++) {
        if (!snakes[i]->active) {
            continue;
        }
        for (int j=i+1; j < 4; j++) {
            if (!snakes[j]->active) {
                continue;
            }
            if (snakes[i]->x == snakes[j]->x && snakes[i]->y == snakes[j]->y) {
                snakes[i]->dead = true;
                snakes[j]->dead = true;
            }
        }
    }

    // check hits
    FOREACH_ACTIVE_SNAKE(snake)
        if (snake->moved && visited.isSet(snake->x, snake->y)) {
            screen.put('0', snake->x, snake->y);
            snake->dead = true;
        }
    }
    FOREACH_ACTIVE_SNAKE(snake)
        if (snake->moved) {
            visited.set(snake->x, snake->y);
        }
    }

    int snakesAlive = 0;
    int snakesActive = 0;
    FOREACH_ACTIVE_SNAKE(snake)
        snakesActive += 1;
        if (!snake->dead) {
            snakesAlive += 1;
        }
    }

    if (snakesActive >= 2 && snakesAlive <= 1) {
        return DEAD;
    }
    if (snakesActive == 1 && snakesAlive <= 0) {
        return DEAD;
    }

    return RUNNING;
}

/* printScores for snake. -1 for all scores */
void printScores(int snakeNum=-1) {
    int textPos = 10;
    
    FOREACH_SNAKE(snake)
        if (snakeNum == -1 || snakeNum == snake_i) {
            if (snake->active) {
                screen.broadcast(snake->symb, textPos, 0);
                screen.broadcast(itos(snake->points), textPos + 2, 0);
            }
        }
        textPos += 20;
    }
}

void welcomeScreen() {
    screen.clear();
    screen.broadcast("Want to play a game?", 30, 12);
    screen.broadcast("Press X!", 35, 14);
}

void updateControllers() {
    FOREACH_ACTIVE_SNAKE(snake)
        snake->updateController();
    }
}

bool matchLoop() {
    visited.clear();
    screen.clear();

    snake1.x = 20;
    snake1.y = 12;
    snake2.x = 60;
    snake2.y = 12;
    snake3.x = DEFAULT_SCREEN_WIDTH+20;
    snake3.y = 12;
    snake4.x = DEFAULT_SCREEN_WIDTH+60;
    snake4.y = 12;
    snake1.direction = UP;
    snake2.direction = DOWN;
    snake3.direction = UP;
    snake4.direction = DOWN;

    printScores();

    game_status_t status;

    long loopCounter = 0;
    while (true) {
        updateControllers();
        delay(10);
        updateControllers();
        delay(10);

        status = gameLoop(SPEED_RUN);
        if (status != RUNNING) {
            break;
        }
        updateControllers();
        delay(10);
        updateControllers();
        delay(10);
        status = gameLoop(RUN);
        
        printScores(loopCounter % 4);
        loopCounter += 1;

        if (status != RUNNING) {
            break;
        }
    }

    FOREACH_ACTIVE_SNAKE(snake)
        if (!snake->dead) {
            snake->points += 500;
        }
        snake->dead = false;
    }

    printScores();

    delay(2000);

    if (status == STOP) {
        return false;
    } else {
        return true;
    }
}

byte collectPlayersLoop() {
    Snake *s;
    byte activePlayers = 0;
    FOREACH_SNAKE(snake)
        s = snake;
        if (s->active) {
            activePlayers += 1;
            continue;
        }
        s->updateController();
        if (s->pad->pressedCross()) {
            s->active = true;
            activePlayers += 1;
        }
    }

    return activePlayers;
}

bool collectPlayers() {
    unsigned long startTime = millis();
    byte numPlayers = collectPlayersLoop();
    if (numPlayers >= 1) {
        screen.clear();
        screen.broadcast("Game starts in 5", 30, 12);
        screen.broadcast("Press X!", 35, 14);
        while ((millis() - startTime) <= 5000 && numPlayers < 4) {
            printScores();
            screen.broadcast("Game starts in ", 30, 12);
            screen.broadcast('5' - ((millis() - startTime)/1000), 45, 12);
            numPlayers = collectPlayersLoop();
        }
        return true;
    }
    return false;
}

#define COLLECT_JMP() \
    if (collectPlayers()) {\
        goto collected;\
    }\

#define WAIT_COLLECT_JMP(ms) \
    for (int i = 0; i < ms/20; ++i) {\
        COLLECT_JMP()\
        delay(20);\
    }\

void loop() {
    text_appear_init(&text_appear, &screen1, &screen2, 0, 1);
    while (text_appear_step(&text_appear)) {
        COLLECT_JMP();
    }
    WAIT_COLLECT_JMP(3000);
    while (text_disappear_step(&text_appear)) {
        COLLECT_JMP();
    }
        
    welcomeScreen();
    WAIT_COLLECT_JMP(3000);
    
    text_appear_init(&text_appear, &screen1, &screen2, 1, 0);
    while (text_appear_step(&text_appear)) {
        COLLECT_JMP();
    }
    WAIT_COLLECT_JMP(3000);
    while (text_disappear_step(&text_appear)) {
        COLLECT_JMP();
    }

    welcomeScreen();
    WAIT_COLLECT_JMP(3000);

    if (0) {
collected:
        while (matchLoop())
        {};
        FOREACH_SNAKE(snake)
            snake->active = false;
            snake->points = 0;
        }
        // welcomeScreen();
    }
    delay(50);
}

