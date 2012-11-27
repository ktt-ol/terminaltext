#include "screen.h"
#include "tron_text.h"

typedef struct {
    TermScreen *screen1;
    TermScreen *screen2;
    int textIdx1;
    int textIdx2;
    int x, y, yOffset1, yOffset2;
    int i;
    int num_chars;
} text_appear_t;

void text_appear_init(text_appear_t *text_appear, TermScreen *screen1, TermScreen *screen2, int textIdx1, int textIdx2) {
    text_appear->screen1 = screen1;
    text_appear->screen2 = screen2;
    text_appear->textIdx1 = textIdx1;
    text_appear->textIdx2 = textIdx2;
    text_appear->i = 0;
    text_appear->num_chars = max(rnd_text_chars[textIdx1], rnd_text_chars[textIdx2]);

    screen1->clear();
    screen2->clear();
    delay(100);
    text_appear->yOffset1 = 24 / 2 - rnd_text_rows[textIdx1] / 2;
    text_appear->yOffset2 = 24 / 2 - rnd_text_rows[textIdx2] / 2;
}

bool text_appear_step(text_appear_t *text_appear) {
    char c;
    int x, y;
    int i = text_appear->i;
    if (i < rnd_text_chars[text_appear->textIdx1]) {
        rnd_text_char(text_appear->textIdx1, i, &x, &y, &c);
        text_appear->screen1->moveTo(x, y + text_appear->yOffset1);
        text_appear->screen1->put(c);
    }
    if (i < rnd_text_chars[text_appear->textIdx2]) {
        rnd_text_char(text_appear->textIdx2, i, &x, &y, &c);
        text_appear->screen2->moveTo(x, y + text_appear->yOffset2);
        text_appear->screen2->put(c);
    }
    if (text_appear->i < text_appear->num_chars) {
        text_appear->i += 1;
        return true;
    }
    return false;
}

bool text_disappear_step(text_appear_t *text_appear) {
    char c;
    int x, y;
    int i = text_appear->i;
    if (i < rnd_text_chars[text_appear->textIdx1]) {
        rnd_text_char(text_appear->textIdx1, i, &x, &y, &c);
        text_appear->screen1->moveTo(x, y + text_appear->yOffset1);
        text_appear->screen1->put(' ');
    }
    if (i < rnd_text_chars[text_appear->textIdx2]) {
        rnd_text_char(text_appear->textIdx2, i, &x, &y, &c);
        text_appear->screen2->moveTo(x, y + text_appear->yOffset2);
        text_appear->screen2->put(' ');
    }
    if (text_appear->i > 1) {
        text_appear->i -= 1;
        return true;
    }
    return false;
}