#include <Memory.hpp>
#include <Cpu.hpp>
#include <BitUtils.hpp>
#include <Video.hpp>
#include <Fonts.hpp>

#include <SDL.h>
#include <glog/logging.h>

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

    // Init SDL
    int error = SDL_Init(SDL_INIT_VIDEO);
    if(error < 0) {
        LOG(FATAL) << "Failed to init SDL - " << SDL_GetError(); 
    }
    SDL_Window *window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Chip8::Video::Width, Chip8::Video::Height, 0);
    if(window == NULL) {
        LOG(FATAL) << "Failed to create window - " << SDL_GetError();
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        LOG(FATAL) << "Failed to create renderer - " << SDL_GetError();
    }

    // Create the texture that will be drawn to the screen every frame.
    SDL_Texture *texture  = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, Chip8::Video::Width, Chip8::Video::Height);
    if(texture == NULL) {
        LOG(FATAL) << "Failed to create texture - " << SDL_GetError();
    }
    
    // Make sure to set the correct pixel format for the Video module
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    if(format == NULL) {
        LOG(FATAL) << "Failed to create format - " << SDL_GetError();
    }

    Chip8::Video::instance().setPixelFormat(format);
    SDL_Event event;
    Chip8::Video::instance().drawSprite(0, 0, Chip8::Fonts::Zero, Chip8::Fonts::SpriteHeight);
    do {
        SDL_PollEvent(&event);

        SDL_RenderClear(renderer);
        SDL_UpdateTexture(texture, NULL, Chip8::Video::instance().getPixels(), Chip8::Video::Width * sizeof(Uint32));
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    } while(event.type != SDL_QUIT);

    SDL_FreeFormat(format);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
