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
        if (!isalnum(c)) {
            throw std::runtime_error{"Tried to print something not alphanumeric. Oh well....\n"};
        }

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
                return Glyph{{0,0}, 10, 10};
            case 'B':
                return Glyph{{0,0}, 10, 10};
            case 'C':
                return Glyph{{0,0}, 10, 10};
            case 'D':
                return Glyph{{0,0}, 10, 10};
            case 'E':
                return Glyph{{0,0}, 10, 10};
            case 'F':
                return Glyph{{0,0}, 10, 10};
            case 'G':
                return Glyph{{0,0}, 10, 10};
            case 'H':
                return Glyph{{0,0}, 10, 10};
            case 'I':
                return Glyph{{0,0}, 10, 10};
            case 'J':
                return Glyph{{0,0}, 10, 10};
            case 'K':
                return Glyph{{0,0}, 10, 10};
            case 'L':
                return Glyph{{0,0}, 10, 10};
            case 'M':
                return Glyph{{0,0}, 10, 10};
            case 'N':
                return Glyph{{0,0}, 10, 10};
            case 'O':
                return Glyph{{0,0}, 10, 10};
            case 'P':
                return Glyph{{0,0}, 10, 10};
            case 'Q':
                return Glyph{{0,0}, 10, 10};
            case 'R':
                return Glyph{{0,0}, 10, 10};
            case 'S':
                return Glyph{{0,0}, 10, 10};
            case 'T':
                return Glyph{{0,0}, 10, 10};
            case 'U':
                return Glyph{{0,0}, 10, 10};
            case 'V':
                return Glyph{{0,0}, 10, 10};
            case 'W':
                return Glyph{{0,0}, 10, 10};
            case 'X':
                return Glyph{{0,0}, 10, 10};
            case 'Y':
                return Glyph{{0,0}, 10, 10};
            case 'Z':
                return Glyph{{0,0}, 10, 10};
            case '0':
                return Glyph{{0,0}, 10, 10};
            case '1':
                return Glyph{{0,0}, 10, 10};
            case '2':
                return Glyph{{0,0}, 10, 10};
            case '3':
                return Glyph{{0,0}, 10, 10};
            case '4':
                return Glyph{{0,0}, 10, 10};
            case '5':
                return Glyph{{0,0}, 10, 10};
            case '6':
                return Glyph{{0,0}, 10, 10};
            case '7':
                return Glyph{{0,0}, 10, 10};
            case '8':
                return Glyph{{0,0}, 10, 10};
            case '9':
                return Glyph{{0,0}, 10, 10};
            default:
                throw std::runtime_error{"Undefined symbol"};
        }
    }

private:
    Image m_atlas;
};
