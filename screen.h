#ifndef _SCREEN_H_
#define _SCREEN_H_

const int DEFAULT_SCREEN_HEIGHT = 24;
const int DEFAULT_SCREEN_WIDTH = 80;

class Screen {
public:
    int width;
    int height;
    Screen(int width=DEFAULT_SCREEN_WIDTH, int height=DEFAULT_SCREEN_HEIGHT) : 
        width(width), height(height)
    {}
    virtual void put(char c, int col, int row) = 0;
    // virtual void put(char c) = 0;
    virtual void clear() = 0;
};

class TermScreen: public Screen {
public:

    SoftwareSerial *serial;

    TermScreen(SoftwareSerial *serial, int width=DEFAULT_SCREEN_WIDTH, int height=DEFAULT_SCREEN_HEIGHT) :
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

#endif