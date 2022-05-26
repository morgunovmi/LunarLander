#pragma once

#include <cctype>

#include "Image.h"
struct Glyph {
    Vec2i startPos;
    u16 width;
    u16 height;
};

class Font {
public:
    Font() : m_atlas() {}
    Font(std::string_view ppmPath) : m_atlas(ppmPath) {}

    const Image& getAtlas() const { return m_atlas; }

    // This is retarded
    Glyph getGlyph(char c) {
        switch (c) {
            case 'a':
                return Glyph{{0,0}, 10, 16};
            case 'b':
                return Glyph{{10,0}, 10, 16};
            case 'c':
                return Glyph{{20,0}, 10, 16};
            case 'd':
                return Glyph{{30,0}, 10, 16};
            case 'e':
                return Glyph{{40,0}, 10, 16};
            case 'f':
                return Glyph{{49,0}, 7, 16};
            case 'g':
                return Glyph{{56,0}, 9, 20};
            case 'h':
                return Glyph{{65,0}, 10, 16};
            case 'i':
                return Glyph{{75,0}, 4, 16};
            case 'j':
                return Glyph{{78,0}, 6, 20};
            case 'k':
                return Glyph{{84,0}, 10, 16};
            case 'l':
                return Glyph{{93,0}, 4, 16};
            case 'm':
                return Glyph{{97,0}, 16, 16};
            case 'n':
                return Glyph{{113,0}, 10, 16};
            case 'o':
                return Glyph{{123,0}, 10, 16};
            case 'p':
                return Glyph{{133,0}, 10, 20};
            case 'q':
                return Glyph{{143,0}, 10, 20};
            case 'r':
                return Glyph{{153,0}, 7, 17};
            case 's':
                return Glyph{{160,0}, 9, 17};
            case 't':
                return Glyph{{168,0}, 7, 17};
            case 'u':
                return Glyph{{175,0}, 10, 17};
            case 'v':
                return Glyph{{184,0}, 10, 17};
            case 'w':
                return Glyph{{193,0}, 14, 17};
            case 'x':
                return Glyph{{207,0}, 9, 16};
            case 'y':
                return Glyph{{216,0}, 9, 20};
            case 'z':
                return Glyph{{225,0}, 10, 16};
            case 'A':
                return Glyph{{0,23}, 12, 15};
            case 'B':
                return Glyph{{12,23}, 11, 15};
            case 'C':
                return Glyph{{23,23}, 12, 15};
            case 'D':
                return Glyph{{35,23}, 12, 15};
            case 'E':
                return Glyph{{46,23}, 11, 15};
            case 'F':
                return Glyph{{56,23}, 11, 15};
            case 'G':
                return Glyph{{67,23}, 12, 15};
            case 'H':
                return Glyph{{79,23}, 12, 15};
            case 'I':
                return Glyph{{92,23}, 4, 15};
            case 'J':
                return Glyph{{96,23}, 10, 15};
            case 'K':
                return Glyph{{107,23}, 11, 15};
            case 'L':
                return Glyph{{118,23}, 10, 15};
            case 'M':
                return Glyph{{128,23}, 15, 15};
            case 'N':
                return Glyph{{143,23}, 13, 15};
            case 'O':
                return Glyph{{156,23}, 13, 15};
            case 'P':
                return Glyph{{169,23}, 11, 15};
            case 'Q':
                return Glyph{{180,23}, 13, 17};
            case 'R':
                return Glyph{{192,23}, 12, 15};
            case 'S':
                return Glyph{{203,23}, 11, 15};
            case 'T':
                return Glyph{{214,23}, 11, 15};
            case 'U':
                return Glyph{{225,23}, 11, 15};
            case 'V':
                return Glyph{{236,23}, 12, 15};
            case 'W':
                return Glyph{{248,23}, 16, 15};
            case 'X':
                return Glyph{{264,23}, 11, 15};
            case 'Y':
                return Glyph{{275,23}, 11, 15};
            case 'Z':
                return Glyph{{286,23}, 10, 15};
            case '0':
                return Glyph{{0,45}, 10, 15};
            case '1':
                return Glyph{{10,45}, 10, 15};
            case '2':
                return Glyph{{20,45}, 11, 15};
            case '3':
                return Glyph{{30,45}, 10, 15};
            case '4':
                return Glyph{{40,45}, 11, 15};
            case '5':
                return Glyph{{51,45}, 10, 15};
            case '6':
                return Glyph{{61,45}, 10, 15};
            case '7':
                return Glyph{{70,45}, 11, 15};
            case '8':
                return Glyph{{81,45}, 10, 15};
            case '9':
                return Glyph{{91,45}, 10, 15};
            case ' ':
                return Glyph{{256,45}, 10, 15};
            case ':':
                return Glyph{{109,45}, 6, 15};
            case '.':
                return Glyph{{101,45}, 5, 15};
            case ',':
                return Glyph{{109,45}, 5, 18};
            case '!':
                return Glyph{{132,45}, 4, 15};
            default:
                throw std::runtime_error{"Trying to print undefined symbol"};
        }
    }

private:
    Image m_atlas;
};
