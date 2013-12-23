#ifndef CHIP8_VIDEO_HPP
#define CHIP8_VIDEO_HPP

#include <SDL.h>
#include <string>

namespace Chip8
{
    
    /**
    * @brief 
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

            Uint32 * getPixels();

            void drawSprite(int x, int y, const unsigned char *sprite, int height);

            void setPixelFormat(SDL_PixelFormat *format);

            static const int Width;
            static const int Height;
            static const int SpriteWidth;

        private:
            // For a correct singleton implementation it is necessary to make
            // the constructor, copy constructor and assignment operators private,
            // so that there isn't any accidental copying.
            Video();
            Video(const Video &other);
            Video & operator=(const Video &other);

            void copyDataToPixels();

            // 64 * 32
            Uint32 _pixels[2048];

            // 64 * 32 / 8
            unsigned char _data[256];
            SDL_PixelFormat *_format;

            static const std::string _Tag;
    };
}

#endif
