#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
#include "Psx.h"
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
};


int x = 0;
int y = 0;

struct coord {
    byte x;
    byte y;
};

typedef enum {
    LEFT, RIGHT, UP, DOWN, NONE
} directions_t;

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
    char symb;
    int points;

    Snake(int x, int y, directions_t dir, char symb) :
        x(x), y(y), direction(dir), symb(symb), points(0)
    {};


    void move(directions_t pressed, Screen &screen) {
        if (pressed != NONE) {
            direction = pressed;
        }

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


// SoftwareSerial(RX, TX) (MAX232 Pins: 9/10, 12/11)
SoftwareSerial mySerial1(2, 3);
SoftwareSerial mySerial2(5, 4);
TermScreen screen1(&mySerial1);
TermScreen screen2(&mySerial2);
ScreenWall screen = ScreenWall();

Snake snake1(10, 12, RIGHT, 'X');
Snake snake2(70, 12, LEFT, 'O');
ScreenMask visited(2*80, 24);

PSPad pad1(10, 9, 12, 11, PSPAD_MULTITAP_PAD1);
PSPad pad2(10, 9, 12, 11, PSPAD_MULTITAP_PAD2);

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

}

directions_t padDirection(PSPad pad) {
    if (pad.pressedLeft())
        return LEFT;
    else if (pad.pressedRight())
        return RIGHT;
    else if (pad.pressedUp())
        return UP;
    else if (pad.pressedDown())
        return DOWN;
    else
        return NONE;
}

directions_t padDirectionButtons(PSPad pad) {
    if (pad.pressedSquare())
        return LEFT;
    else if (pad.pressedCircle())
        return RIGHT;
    else if (pad.pressedTriangle())
        return UP;
    else if (pad.pressedCross())
        return DOWN;
    else
        return NONE;
}

void loop() {
    directions_t dir1 = NONE;
    directions_t dir2 = NONE;

    pad1.update();
    pad2.update();
    dir1 = padDirection(pad1);
    dir2 = padDirection(pad2);


    // digitalWrite(13, LOW);
    // delay(500);
    // digitalWrite(13, HIGH);

    // return;

    bool end = false;

    if (pad1.pressedStart()) {
        end = true;
        snake1.points = 0;
        snake2.points = 0;        
        visited.clear();
        screen.clear();
    }

    snake1.move(dir1, screen);
    snake2.move(dir2, screen);

    if (snake1.x == snake2.x && snake1.y == snake2.y) {
        end = true;
    }

    if (visited.isSet(snake1.x, snake1.y)) {
        screen.put('0', snake1.x, snake1.y);
        snake2.points += 1;
        end = true;
    }

    if (visited.isSet(snake2.x, snake2.y)) {
        screen.put('0', snake2.x, snake2.y);
        snake1.points += 1;
        end = true;
    }

    visited.set(snake1.x, snake1.y);
    visited.set(snake2.x, snake2.y);

    if (end) {
        delay(2000);
        visited.clear();
        screen.clear();
        snake1.x = 10;
        snake1.y = 12;
        snake2.x = 70;
        snake2.y = 12;
        snake1.direction = RIGHT;
        snake2.direction = LEFT;
    }
    screen.put('0' +  snake1.points, 0, 0);
    screen.put('0' +  snake2.points, 79, 0);


    digitalWrite(13, LOW);
    delay(50);
    digitalWrite(13, HIGH);


}