#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
#include "ktt_text.h"

// \033[?7l disable autowrap
// \033[4h enable insert mode

class TermScreen {
public:

    const int width;
    const int height;
    SoftwareSerial *serial;

    TermScreen(SoftwareSerial *serial, int width=80, int height=24) :
        serial(serial), width(width), height(height)
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

    void put(char c, int col, int row) {
        moveTo(col, row);
        serial->print(c);
    };

    void put(char c) {
        serial->print(c);
    };

    void refresh() {
        serial->print("\033[0;0H");
    };

    void clear() {
        serial->print("\033[H\033[2J");      
    };

    void disableCursor() {
        serial->print("\033[3;4z");
    }

};

// SoftwareSerial(RX, TX) (MAX232 Pins: 9/10, 12/11)
SoftwareSerial mySerial1(2, 3);
SoftwareSerial mySerial2(5, 4);
TermScreen screen1(&mySerial1);
TermScreen screen2(&mySerial2);


void setup()  
{
    pinMode(13, OUTPUT);

    mySerial1.begin(9600);
    mySerial2.begin(9600);
}

void textMoveRight() {
    screen1.init("\033[4h\033[?7l");
    screen2.init("\033[4h\033[?7l");
    delay(100);
    int yOffset = 24 / 2 - dataRows / 2;
    for (int x = 0; x < 160 + dataCols; x++) {
        for (int y = 0; y < dataRows; y++) {
            screen1.moveTo(0, y + yOffset);
            delay(1);
            screen2.moveTo(0, y + yOffset);

            delay(2);
            if (x < 80 + dataCols) {
                if (x < dataCols) {
                    screen1.put(dataChar(x, y));
                } else {
                    screen1.put(' ');
                }
            }
            if (x >= 80) {
                delay(1);
                if ((x - 80) < dataCols) {
                    screen2.put(dataChar(x-80, y));
                } else {
                    screen2.put(' ');
                }
            }
            delay(5);
        }
    }
}

void textMoveLeft() {
    screen1.init("\033[4h\033[?7l");
    screen2.init("\033[4h\033[?7l");
    delay(100);
    char c;
    int yOffset = 24 / 2 - dataRows / 2;
    for (int x = 0; x < 160 + dataCols; x++) {
        for (int y = 0; y < dataRows; y++) {
            screen1.moveTo(0, y + yOffset);
            screen1.puts("\033[0P");
            screen2.moveTo(0, y + yOffset);
            screen2.puts("\033[0P");
            screen1.moveTo(79, y + yOffset);
            screen2.moveTo(79, y + yOffset);
            if (x < 80 + dataCols) {
                if (x < dataCols) {
                    screen2.put(dataChar(dataCols-x-1, y));
                } else {
                    screen2.put(' ');
                }
            }
            if (x >= 80) {
                if ((x - 80) < dataCols) {
                    screen1.put(dataChar(dataCols-(x-80)-1, y));
                } else {
                    screen1.put(' ');
                }
            }
        }
    }
}


void textAppear(int textIdx1, int textIdx2) {
    screen1.init("\033[4l\033[?7l");
    screen2.init("\033[4l\033[?7l");
    delay(100);
    char c = 0;
    int x, y;
    int yOffset1, yOffset2;

    yOffset1 = 24 / 2 - numRows[textIdx1] / 2;
    yOffset2 = 24 / 2 - numRows[textIdx2] / 2;

    for (int i = 0; i < max(numChars[textIdx1], numChars[textIdx2]); i++) {
        if (i < numChars[textIdx1]) {
            randomDataChar(textIdx1, i, &x, &y, &c);
            screen1.moveTo(x, y + yOffset1);
            screen1.put(c);
        }
        if (i < numChars[textIdx2]) {
            randomDataChar(textIdx2, i, &x, &y, &c);
            screen2.moveTo(x, y + yOffset2);
            screen2.put(c);
        }
        delay(2);
    }
}


void loop() {
    textAppear(0, 1);
    delay(1000);
    screen1.clear();
    screen2.clear();

    textAppear(2, 3);
    delay(1000);
    screen1.clear();
    screen2.clear();

    textMoveLeft();

    textAppear(0, 1);
    delay(1000);
    screen1.clear();
    screen2.clear();

    textAppear(2, 3);
    delay(1000);
    screen1.clear();
    screen2.clear();

    textMoveRight();
}