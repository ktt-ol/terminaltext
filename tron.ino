#include <SoftwareSerial.h>
#include "PSPad.h"

// \033[?7l disable autowrap
// \033[4h enable insert mode

class Screen {
public:
    int width;
    int height;
    Screen(int width=80, int height=24) : 
        width(width), height(height)
    {}
    virtual void put(char c, int col, int row) = 0;
    // virtual void put(char c) = 0;
    virtual void clear() = 0;
};

class TermScreen: public Screen {
public:

    SoftwareSerial *serial;

    TermScreen(SoftwareSerial *serial, int width=80, int height=24) :
        serial(serial), Screen(width, height)
    {};

    void init(const char *initString) {
        // puts("\033c"); // reset
        delay(100);
        puts(initString);
    }

    void moveTo(int col, int row) {
        if (row < 0 || row >= height || col < 0 || col >= width) {
            return;
        }
        serial->print("\033[");
        serial->print(row+1);
        serial->print(";");
        serial->print(col+1);
        serial->print("H");
    };
    
    void puts(const char *c) {
        while (*c != '\0') {
            put(*c);
            c++;
        }
    };

    virtual void put(char c, int col, int row) {
        moveTo(col, row);
        serial->print(c);
    };

    virtual void put(char c) {
        serial->print(c);
    };

    void refresh() {
        serial->print("\033[0;0H");
    };

    virtual void clear() {
        serial->print("\033[H\033[2J");      
    };

    void disableCursor() {
        serial->print("\033[3;4z");
    }
};

class ScreenWall : public Screen {
    static const byte maxScreens = 4;
    byte numScreens;
    TermScreen *screens[maxScreens];

public:
    ScreenWall() :
        Screen(0, 0), numScreens(0)
    {};

    void addScreen(TermScreen *screen) {
        if (numScreens >= maxScreens) {
            return;
        }

        screens[numScreens] = screen;
        numScreens += 1;
        width += screen->width;
        height = screen->height; 
    }

    void put(char c, int col, int row) {
        for (int i = 0; i < numScreens; i++) {
            if (col < screens[i]->width) {
                screens[i]->put(c, col, row);
                break;
            }
            col -= screens[i]->width;
        }
    }

    void clear() {
        for (int i = 0; i < numScreens; i++) {
            screens[i]->clear();
        }
    }

    void broadcast(char str, int col, int row) {
        for (int i = 0; i < numScreens; i++) {
            screens[i]->put(str, col, row);
        }
    }

    void broadcast(char *str, int col, int row) {
        for (int i = 0; i < numScreens; i++) {
            screens[i]->moveTo(col, row);
            screens[i]->puts(str);
        }
    }

};

typedef enum {
    LEFT, RIGHT, UP, DOWN, NONE
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

class Snake {
public:
    int x;
    int y;
    directions_t direction;
    PSPad *pad;
    char symb;
    int points;
    bool dead;
    bool active;
    bool moved;

    Snake(int x, int y, directions_t dir, char symb, PSPad *pad) :
        x(x), y(y), direction(dir), symb(symb),
        points(0), dead(false), active(false), moved(false),
        pad(pad)
    {};

    void updateController() {
        pad->update();
        directions_t dir = padDirection(pad);
        if (dir != NONE) {
            direction = dir;
        }
    }

    void move(Screen &screen) {
        switch (direction) {
            case LEFT:
                x -= 1;
                break;
            case RIGHT:
                x += 1;
                break;
            case UP:
                y -= 1;
                break;
            case DOWN:
                y += 1;
                break;
        }
        if (x < 0) {
            x = screen.width - 1;
        } else if (x >= screen.width) {
            x = 0;
        }

        if (y < 0) {
            y = screen.height - 1;
        } else if (y >= screen.height) {
            y = 0;
        }
        
        screen.put(symb, x, y);
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

ScreenMask visited(2*80, 24);

Snake *snakes[] = {&snake1, &snake2, &snake3, &snake4};

void setup()  
{
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
    screen1.init("\033[4l");
    screen2.clear();
    screen2.init("\033[4l");

    welcomeScreen();
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

char tmp_buf[5];
char *itos(int i) {
    snprintf(&tmp_buf[0], 5, "%d", i);
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

    FOREACH_ACTIVE_SNAKE(snake)
        snake->updateController();
        if (mode == RUN || (mode == SPEED_RUN && snake->pad->pressedCross())) {
            snake->move(screen);
            snake->moved = true;
        } else {
            snake->moved = false;
        }
    }

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

    FOREACH_ACTIVE_SNAKE(snake)
        if (snake->dead) {
            return DEAD;
        }
    }

    return RUNNING;
}

void printScores() {
    int textPos = 10;

    FOREACH_SNAKE(snake)
        if (snake->active) {
            screen.broadcast(snake->symb, textPos, 0);
            screen.broadcast(itos(snake->points), textPos + 2, 0);
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

    snake1.x = 35;
    snake1.y = 12;
    snake2.x = 45;
    snake2.y = 12;
    snake3.x = 40;
    snake3.y = 16;
    snake4.x = 40;
    snake4.y = 8;
    snake1.direction = LEFT;
    snake2.direction = RIGHT;
    snake3.direction = DOWN;
    snake4.direction = UP;

    printScores();

    game_status_t status;
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
        if (status != RUNNING) {
            break;
        }
    }

    FOREACH_ACTIVE_SNAKE(snake)
        if (!snake->dead) {
            snake->points += 1;
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

void loop() {
    if (collectPlayers()) {
        while (matchLoop()) 
        {};
        FOREACH_SNAKE(snake)
            snake->active = false;
            snake->points = 0;
        }
        welcomeScreen();
    }
    delay(50);
}
