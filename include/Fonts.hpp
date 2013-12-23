/**
* @file Fonts.hpp
* @brief Stores all font data structures.
* @author Chad Dettmering
* @version 0.1
* @date 2013-12-23
*/

#ifndef CHIP8_FONTS_HPP
#define CHIP8_FONTS_HPP
namespace Chip8
{

    /**
    * @brief Storage for all font data structures. Chip8 has built in font sprites
    *        for 1 digit hex numbers (0-F), which the system can use to display.
    */
    class Fonts
    {
        public:

            /**
            * @brief Converts the hex number to the Sprite.
            *
            * @param hex The hexidecimal number to get the Sprite for.
            *
            * @return Array of bytes that is guranteed to be of length FontSpriteSize.
            */
            static const unsigned char * getSprite(unsigned char hex);

            // Spite declaratins for each single digit hex number.
            static const unsigned char Zero[];
            static const unsigned char One[];
            static const unsigned char Two[];
            static const unsigned char Three[];
            static const unsigned char Four[];
            static const unsigned char Five[];
            static const unsigned char Six[];
            static const unsigned char Seven[];
            static const unsigned char Eight[];
            static const unsigned char Nine[];
            static const unsigned char A[];
            static const unsigned char B[];
            static const unsigned char C[];
            static const unsigned char D[];
            static const unsigned char E[];
            static const unsigned char F[];

            // The number of rows he Font sprites contain. Each row is 8 bits.
            static const unsigned char SpriteHeight;
    };
}
#endif
