/**
* @file Video.hpp
* @brief Handles video related tasks.
* @author Chad Dettmering
* @version 0.1
* @date 2013-12-23
*/

#ifndef CHIP8_VIDEO_HPP
#define CHIP8_VIDEO_HPP

#include <SDL.h>
#include <string>

namespace Chip8
{
    
    /**
    * @brief Handles drawing sprites to the screen.
    */
    class Video
    {
        public:

            /**
            * @brief Gets the singleton instance of the Video module.
            *
            * @return Singleton instance of the Video module.
            */
            static Video & instance();

            /**
            * @brief Gets the pixels that SDL needs to draw the screen.
            *
            * @return Array of pixels guranteed to be of size Width * Height
            */
            Uint32 * getPixels();

            /**
            * @brief Draws a sprite to the pixel buffer.
            *
            * @param x The x coordinate to place the upper left part of the sprite at.
            * @param y The y coordinate to place the upper left part of the sprite at.
            * @param sprite The byte buffer that contains the sprite data. This buffer
            *               must be of size SpriteWidth * height
            * @param height The number of rows this sprite has.
            */
            void drawSprite(int x, int y, const unsigned char *sprite, int height);

            /**
            * @brief Clears the screen to black. (NOTE: It's up to the Chip8
            *        programmer to clear the screen at startup.)
            */
            void clearScreen();

            /**
            * @brief Sets the pixel format for determining what the pixel ints
            *        look like.
            *
            * @param format PixelFormat struct.
            */
            void setPixelFormat(SDL_PixelFormat *format);

            /**
            * @brief Width of the Chip8 display.
            */
            static const int Width;

            /**
            * @brief Height of the Chip8 display.
            */
            static const int Height;

            /**
            * @brief Width of a sprite in Chip8.
            */
            static const int SpriteWidth;

        private:
            // For a correct singleton implementation it is necessary to make
            // the constructor, copy constructor and assignment operators private,
            // so that there isn't any accidental copying.
            Video();
            Video(const Video &other);
            Video & operator=(const Video &other);

            // Copies the 0 or 1 pixel data from _data and maps it to 0 = Black
            // 1 = White pixels and stores it in _pixels.
            void copyDataToPixels();

            // 64 * 32
            Uint32 _pixels[2048];
            unsigned char _data[2048];
            SDL_PixelFormat *_format;

            static const std::string _Tag;
    };
}

#endif
