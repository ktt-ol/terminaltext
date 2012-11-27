# -:- encoding: utf8 -:-
import subprocess
import random

def figlet(text, font='standard', width=80, center=False):
    cmd = ['figlet', '-S', '-f', font, '-D', '-w', str(width), text]
    if center:
        cmd.insert(1, '-c')
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    stdout = p.communicate()[0]
    return stdout


def vertical_text(text):
    columns = []
    text = figlet(text, width=999)
    lines = text.split("\n")


    for line in lines:
        print "// " + line

    print

    for line in lines:
        if not line.strip():
            continue
        if not columns:
            for c in line:
                columns.append([])
        for i, c in enumerate(line):
            columns[i].append(c)
    columns.reverse()

    from pprint import pprint

    print "int dataCols = %d;" % len(columns)
    print "int dataRows = %d;" % len(columns[0])

    print "PROGMEM prog_uchar data[] = {",
    data = repr(''.join(''.join(col) for col in columns))
    print '"' + data[1:-1] + '"',
    print "};"


    print """
    char inline dataChar(int x, int y) {
        return pgm_read_byte_near(data + x * dataRows + y);
    }
    """

def random_appear_text(texts):

    text_chars = []
    num_chars = []
    num_rows = []
    offsets = [0]

    for text in texts:
        chars = []

        text = figlet(text, width=80, center=True)

        for line in text.split('\n'):
            print "// " + line

        for y, line in enumerate(text.split('\n')):
            for x, c in enumerate(line):
                if c != ' ':
                    chars.append(c + chr(x) + chr(y))

        random.shuffle(chars)
        num_chars.append(len(chars))
        offsets.append(offsets[-1] + len(chars) * 3)
        num_rows.append(y + 1)
        text_chars.append(''.join(chars))

    all_chars = ''.join(text_chars)
    offsets = offsets[:-1]

    print "int rnd_text_num = %d;" % len(text_chars)
    print "int rnd_text_chars[] = {%s};" % ', '.join('%d' % c for c in num_chars)
    print "int rnd_text_rows[] = {%s};" % ', '.join('%d' % c for c in num_rows)
    print "int rnd_text_char_offsets[] = {%s};" % ', '.join('%d' % c for c in offsets)

    print "PROGMEM prog_uchar rnd_text_char_data[] = {",
    print '"' + repr(all_chars).replace('"', '\\"')[1:-1] + '"',
    print "};"

    print """
    void inline rnd_text_char(int textIdx, int charIdx, int *x, int *y, char *c) {

        *c = pgm_read_byte_near(rnd_text_char_data + rnd_text_char_offsets[textIdx] + charIdx * 3);
        *x = pgm_read_byte_near(rnd_text_char_data + rnd_text_char_offsets[textIdx] + charIdx * 3 + 1);
        *y = pgm_read_byte_near(rnd_text_char_data + rnd_text_char_offsets[textIdx] + charIdx * 3 + 2);
    }
    """

if __name__ == '__main__':
    # { -> ä, } -> ü see Figlet manpage
    text = "Kreativit{t trifft Technik\tBetaSpace"
    text = text.replace('\t', ' ' * 20)
    vertical_text(text)

    # random_appear_text(["Kreativit{t trifft Technik", "BetaSpace", "Der Oldenburger Hackspace", "http://ktt-ol.de"])
    random_appear_text(["Mainframe", "Tron", "Der Oldenburger Hackspace", "http://ktt-ol.de"])
