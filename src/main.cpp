#include <Memory.hpp>
#include <Cpu.hpp>
#include <BitUtils.hpp>
#include <Video.hpp>
#include <Fonts.hpp>
#include <FileUtils.hpp>
#include <Timers.hpp>
#include <Input.hpp>

#include <SDL.h>
#include <glog/logging.h>

#include <iostream>

void printUsage()
{
    std::cout << "Usage: chip8 [romfile]" << std::endl;
}

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

    // Setup the filename
    if(argc != 2) {
    	printUsage();
    	return 1;
    } else {
        std::string romName = argv[1];
        LOG(INFO) << "Reading rom " << romName;
        std::vector<unsigned char> rom = Chip8::FileUtils::readRom(romName);
        LOG(INFO) << "Rom size = " << rom.size();
        for(unsigned int i = 0; i < rom.size(); i++) {
            if(!Chip8::Memory::instance().write(Chip8::Memory::StartAddress + i, rom.at(i))) {
                LOG(INFO) << "Failed to load rom into " << (int) Chip8::Memory::StartAddress + i;
                std::cout << "Failed to load rom into " << (int) Chip8::Memory::StartAddress + i << std::endl;
                return 1;
            }
        }
        LOG(INFO) << "Loaded rom";
        for(unsigned int i = 0; i < rom.size(); i++) {
            unsigned char data = 0;
            Chip8::Memory::instance().read(Chip8::Memory::StartAddress + i, data);
            LOG(INFO) << (int) data;
        }
    }

    // Setup SDL.
    // Chip8 has a render size of 64x32 
    int upScale = 24;
    int error = SDL_Init(SDL_INIT_VIDEO);
    if(error < 0) {
        LOG(FATAL) << "Failed to init SDL - " << SDL_GetError(); 
    }
    SDL_Window *window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Chip8::Video::Width * upScale, Chip8::Video::Height * upScale, SDL_WINDOW_RESIZABLE);
    //SDL_Window *window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == NULL) {
        LOG(FATAL) << "Failed to create window - " << SDL_GetError();
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        LOG(FATAL) << "Failed to create renderer - " << SDL_GetError();
    }
    SDL_RenderSetScale(renderer, upScale, upScale);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0); 
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

    // Load fonts into memory
    for(unsigned char  i = 0; i < 0xF + 1; i++) {
        LOG(INFO) << "Getting font sprite " << (int) i;
        const unsigned char *sprite = Chip8::Fonts::getSprite(i);
        for(unsigned char j = 0; j < Chip8::Fonts::SpriteHeight; j++) {
            unsigned int address = 0x0 + (i * Chip8::Fonts::SpriteHeight) + j;
            LOG(INFO) << "Loading font sprite byte " << (int) j << " to memory address " << address;
            if(!Chip8::Memory::instance().write(address, sprite[j])) {
               LOG(INFO) << "Failed to load font sprite " << (int) i << " into memory address " << address;
            }
        } 
    }

    // Jump to start of rom
    Chip8::Cpu::instance().jump(Chip8::Memory::StartAddress);

    SDL_Event event;
    Uint32 lastFrame = SDL_GetTicks();
    Uint32 sixtyFrame = 1000 / 60;
    do {
        Uint32 currentFrame = SDL_GetTicks();
        Uint32 elapsed = currentFrame - lastFrame;
        lastFrame = currentFrame;
        if(elapsed < sixtyFrame) {
            SDL_Delay(sixtyFrame - elapsed);
        }

        // Handle event
        SDL_PollEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                LOG(INFO) << "Key pressed " << event.key.keysym.scancode;
                if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    LOG(INFO) << "Escape pressed exiting now";
                    SDL_FreeFormat(format);
                    SDL_DestroyTexture(texture);
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;
                } else if(Chip8::InputManager::instance().IsWaitingForKeyPress) {
                    unsigned char hex;
                    Chip8::InputManager::instance().toHex(event.key.keysym.scancode, hex);
                    LOG(INFO) << "InputManager waiting for key press key pressed = " << hex;
                    if(Chip8::InputManager::instance().isValidKey(hex)) {
                        LOG(INFO) << "Valid key detected, setting register " << Chip8::InputManager::instance().KeyPressRegister;
                        Chip8::InputManager::instance().IsWaitingForKeyPress = false;
                        Chip8::Memory::instance().setRegister(Chip8::InputManager::KeyPressRegister, hex);
                    }
                }
                break;
        }

        if(!Chip8::InputManager::instance().IsWaitingForKeyPress) {
            // Cpu step
            Chip8::Cpu::instance().step();
            Chip8::Timers::instance().step();
        }

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
