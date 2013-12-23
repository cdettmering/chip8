#include <Video.hpp>
#include <Memory.hpp>
#include <BitUtils.hpp>

#include <glog/logging.h>

namespace Chip8 
{

    const int Video::Width = 64;
    const int Video::Height = 32;
    const int Video::SpriteWidth = 8;

    const std::string Video::_Tag = "Video:";

    Video::Video()
        : _format(0)
    {
    }

    Video & Video::instance()
    {
        static Video instance;
        return instance;
    }

    Uint32 * Video::getPixels()
    {
        return _pixels;
    }
            
    void Video::drawSprite(int x, int y, const unsigned char *sprite, int height)
    {
        // Don't handle wrapping yet
        if(x < 0 || y < 0 || x + SpriteWidth >= Width || y + height >= Height) {
            LOG(INFO) << _Tag << "Wrapping not yet implemented. Not drawing sprite.";
            return;
        }

        LOG(INFO) << _Tag << "Drawing sprite to location (" << x << ", " << y << ")";

        // Start at point x, y draw the sprite
        for(int j = 0; j < height; j++) {
            for(int i = 0; i < SpriteWidth; i++) {
                int screenPixelIndex = (x + i) + ((y + j) * Width);
                int spritePixelIndex = i + (j * SpriteWidth);
                unsigned char screenPixel = _data[screenPixelIndex];

                // The sprite pixel index is the exact bit to grab from the sprite.
                // However the sprite is stored in byte chunks, so need to divide by SpriteWidth
                // to grab the correct byte, and then bitquery the correct bit to get the
                // pixel.
                unsigned char spritePixel = BitUtils::bitQuery(sprite[spritePixelIndex / SpriteWidth], SpriteWidth - 1 - i);

                // Chip8 draws sprites by xoring the pixel and saving the result.
                // 1 means the pixel is active, 0 means the pixel is inactive.
                // If the draw causes any pixels to be set from 1 to 0, then
                // register F needs to be set to 1.
                unsigned char result = screenPixel ^ spritePixel;
                _data[screenPixelIndex] = result;
                
                if(screenPixel == 0x1 && result == 0x0) {
                    if(!Memory::instance().setRegister(0xF, 0x1)) {
                        LOG(INFO) << _Tag << "Failed to set data " << 0x1 << " to register " << 0xF;
                    }
                }
            }
        }

        // Copy the data to the screen, after drawing.
        copyDataToPixels();
    }

    void Video::clearScreen()
    {
        for(int i = 0; i < Width * Height; i++) {
            _data[i] = 0;
        } 
        copyDataToPixels();
    }
            
    void Video::setPixelFormat(SDL_PixelFormat *format)
    {
        _format = format;
    }
            
    void Video::copyDataToPixels()
    {
        // Handle 1 byte at a time
        for(int i = 0; i < Width * Height; i++) {
                // White
                if(_data[i] == 0x1) {
                    _pixels[i] = SDL_MapRGBA(_format, 255, 255, 255, 255);
                }
                // Black
                else if(_data[i] == 0x0) {
                    _pixels[i] = SDL_MapRGBA(_format, 0, 0, 0, 255);
                }
                // Error
                else {
                    LOG(INFO) << _Tag << "Unknown pixel type";
            }
        }
    }

}