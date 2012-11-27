#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
#include "ktt_text.h"
#include "screen.h"

SoftwareSerial mySerial1(2, 3);
SoftwareSerial mySerial2(5, 4);
TermScreen screen1(&mySerial1);
TermScreen screen2(&mySerial2);

void setup()
{
    mySerial1.begin(9600);
    mySerial2.begin(9600);

    screen1.clear();
    screen2.clear();
}

void textMoveRight(TermScreen &screen1, TermScreen &screen2) {
    // \033[?7l disable autowrap
    // \033[4h enable insert mode
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

void textMoveLeft(TermScreen &screen1, TermScreen &screen2) {
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


void textAppear(TermScreen &screen1, TermScreen &screen2, int textIdx1, int textIdx2) {
    screen1.init("\033[4l\033[?7l");
    screen2.init("\033[4l\033[?7l");
    delay(100);
    char c = 0;
    int x, y;
    int yOffset1, yOffset2;

    yOffset1 = 24 / 2 - rnd_text_rows[textIdx1] / 2;
    yOffset2 = 24 / 2 - rnd_text_rows[textIdx2] / 2;

    for (int i = 0; i < max(rnd_text_chars[textIdx1], rnd_text_chars[textIdx2]); i++) {
        if (i < rnd_text_chars[textIdx1]) {
            rnd_text_char(textIdx1, i, &x, &y, &c);
            screen1.moveTo(x, y + yOffset1);
            screen1.put(c);
        }
        if (i < rnd_text_chars[textIdx2]) {
            rnd_text_char(textIdx2, i, &x, &y, &c);
            screen2.moveTo(x, y + yOffset2);
            screen2.put(c);
        }
        delay(1);
    }
}



void textAppear(TermScreen &screen1, int textIdx1) {
    screen1.init("\033[4l\033[?7l");
    delay(100);
    char c = 0;
    int x, y;
    int yOffset1;

    yOffset1 = 24 / 2 - rnd_text_rows[textIdx1] / 2;

    for (int i = 0; i < rnd_text_chars[textIdx1]; i++) {
        if (i < rnd_text_chars[textIdx1]) {
            rnd_text_char(textIdx1, i, &x, &y, &c);
            screen1.moveTo(x, y + yOffset1);
            screen1.put(c);
        }
        // delay(1);
    }
}


void loop() {
    textAppear(screen1, 0);
    delay(1500);
    screen1.clear();

    textAppear(screen1, 1);
    delay(1500);
    screen1.clear();

    textAppear(screen1, 2);
    delay(1500);
    screen1.clear();

    textAppear(screen1, 3);
    // ktt-ol.de URL
    delay(3000);
    screen1.clear();
}
