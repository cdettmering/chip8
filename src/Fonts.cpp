#include <Fonts.hpp>

namespace Chip8
{
    std::vector<const unsigned char *> Fonts::_fonts;
    const unsigned char * Fonts::getSprite(unsigned char hex)
    {
        if(hex < 0 || hex > 0xF) {
            return 0;
        }
        return getFonts().at(hex);
    }

    std::vector<const unsigned char *> Fonts::getFonts()
    {
        if(_fonts.size() == 0) {
            _fonts.push_back(Zero);
            _fonts.push_back(One);
            _fonts.push_back(Two);
            _fonts.push_back(Three);
            _fonts.push_back(Four);
            _fonts.push_back(Five);
            _fonts.push_back(Six);
            _fonts.push_back(Seven);
            _fonts.push_back(Eight);
            _fonts.push_back(Nine);
            _fonts.push_back(A);
            _fonts.push_back(B);
            _fonts.push_back(C);
            _fonts.push_back(D);
            _fonts.push_back(E);
            _fonts.push_back(F);
        }

        return _fonts;
    }

    const unsigned char Fonts::Zero[] = { 0xF0, 0x90, 0x90, 0x90, 0xF0 };
    const unsigned char Fonts::One[] = { 0x20, 0x60, 0x20, 0x20, 0x70 };
    const unsigned char Fonts::Two[] = { 0xF0, 0x10, 0xF0, 0x80, 0xF0 };
    const unsigned char Fonts::Three[] = { 0xF0, 0x10, 0xF0, 0x10, 0xF0 };
    const unsigned char Fonts::Four[] = { 0x90, 0x90, 0xF0, 0x10, 0x10 };
    const unsigned char Fonts::Five[] = { 0xF0, 0x80, 0xF0, 0x10, 0xF0 };
    const unsigned char Fonts::Six[] = { 0xF0, 0x80, 0xF0, 0x90, 0xF0 };
    const unsigned char Fonts::Seven[] = { 0xF0, 0x10, 0x20, 0x40, 0x40 };
    const unsigned char Fonts::Eight[] = { 0xF0, 0x90, 0xF0, 0x90, 0xF0 };
    const unsigned char Fonts::Nine[] = { 0xF0, 0x90, 0xF0, 0x10, 0xF0 };
    const unsigned char Fonts::A[] = { 0xF0, 0x90, 0xF0, 0x90, 0x90 };
    const unsigned char Fonts::B[] = { 0xE0, 0x90, 0xE0, 0x90, 0xE0 };
    const unsigned char Fonts::C[] = { 0xF0, 0x80, 0x80, 0x80, 0xF0 };
    const unsigned char Fonts::D[] = { 0xE0, 0x90, 0x90, 0x90, 0xE0 };
    const unsigned char Fonts::E[] = { 0xF0, 0x80, 0xF0, 0x80, 0xF0 };
    const unsigned char Fonts::F[] = { 0xF0, 0x80, 0xF0, 0x80, 0x80 };

    const unsigned char Fonts::SpriteHeight = 5;
}
