#include <Memory.hpp>
#include <Cpu.hpp>
#include <BitUtils.hpp>
#include <Video.hpp>
#include <Fonts.hpp>
#include <FileUtils.hpp>
#include <Timers.hpp>

#include <SDL.h>
#include <glog/logging.h>

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

    // Setup SDL.
    // Chip8 has a render size of 64x32.
    
    int error = SDL_Init(SDL_INIT_VIDEO);
    if(error < 0) {
        LOG(FATAL) << "Failed to init SDL - " << SDL_GetError(); 
    }
    //SDL_Window *window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Chip8::Video::Width, Chip8::Video::Height, 0);
    SDL_Window *window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == NULL) {
        LOG(FATAL) << "Failed to create window - " << SDL_GetError();
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        LOG(FATAL) << "Failed to create renderer - " << SDL_GetError();
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    error = SDL_RenderSetLogicalSize(renderer, Chip8::Video::Width, Chip8::Video::Height);
    if(error < 0) {
        LOG(FATAL) << "Failed to set render size - " << SDL_GetError(); 
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

    // HARDCODE TEST
    std::string romName = "IBM.ch8";
    LOG(INFO) << "Reading rom " << romName;
    std::vector<unsigned char> rom = Chip8::FileUtils::readRom(romName);
    LOG(INFO) << "Rom size = " << rom.size();
    for(unsigned int i = 0; i < rom.size(); i++) {
        if(!Chip8::Memory::instance().write(Chip8::Memory::StartAddress + i, rom.at(i))) {
            LOG(INFO) << "Failed to load rom into " << (int) Chip8::Memory::StartAddress + i;
        }
    }
    LOG(INFO) << "Loaded rom";
    for(unsigned int i = 0; i < rom.size(); i++) {
        unsigned char data = 0;
        Chip8::Memory::instance().read(Chip8::Memory::StartAddress + i, data);
        LOG(INFO) << (int) data;
    }
    // END HARDCODE TEST

    // Jump to start of rom
    Chip8::Cpu::instance().jump(Chip8::Memory::StartAddress);

    do {
        // Handle event
        SDL_PollEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    SDL_FreeFormat(format);
                    SDL_DestroyTexture(texture);
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;
                }
                break;
        }

        // Cpu step
        Chip8::Cpu::instance().step();
        Chip8::Timers::instance().step();

        // Render screen
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
