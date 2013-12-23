#include <Input.hpp>

#include <SDL_keyboard.h>
#include <SDL_events.h>
#include <glog/logging.h>

namespace Chip8
{
    const SDL_Scancode InputManager::Key0 = SDL_SCANCODE_1;
    const SDL_Scancode InputManager::Key1 = SDL_SCANCODE_2;
    const SDL_Scancode InputManager::Key2 = SDL_SCANCODE_3;
    const SDL_Scancode InputManager::Key3 = SDL_SCANCODE_4;
    const SDL_Scancode InputManager::Key4 = SDL_SCANCODE_Q;
    const SDL_Scancode InputManager::Key5 = SDL_SCANCODE_W;
    const SDL_Scancode InputManager::Key6 = SDL_SCANCODE_E;
    const SDL_Scancode InputManager::Key7 = SDL_SCANCODE_R;
    const SDL_Scancode InputManager::Key8 = SDL_SCANCODE_A;
    const SDL_Scancode InputManager::Key9 = SDL_SCANCODE_S;
    const SDL_Scancode InputManager::KeyA = SDL_SCANCODE_D;
    const SDL_Scancode InputManager::KeyB = SDL_SCANCODE_F;
    const SDL_Scancode InputManager::KeyC = SDL_SCANCODE_Z;
    const SDL_Scancode InputManager::KeyD = SDL_SCANCODE_X;
    const SDL_Scancode InputManager::KeyE = SDL_SCANCODE_C;
    const SDL_Scancode InputManager::KeyF = SDL_SCANCODE_V;
    const SDL_Scancode InputManager::Keys[] = {Key0, Key1, Key2, Key3, Key4, Key5, Key6,
                                               Key7, Key8, Key9, KeyA, KeyB, KeyC, KeyD,
                                               KeyE, KeyF};
    const std::string InputManager::_Tag = "InputManager:";

    InputManager::InputManager()
    {

    }
            
    InputManager & InputManager::instance()
    {
        static InputManager instance;
        return instance;
    }

    bool InputManager::isKeyDown(SDL_Scancode key) const
    {
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        return keys[key] == 1;
    }

    bool InputManager::anyKeyDown() const
    {
        return isKeyDown(Key0) ||
               isKeyDown(Key1) ||
               isKeyDown(Key2) ||
               isKeyDown(Key3) ||
               isKeyDown(Key4) ||
               isKeyDown(Key5) ||
               isKeyDown(Key6) ||
               isKeyDown(Key7) ||
               isKeyDown(Key8) ||
               isKeyDown(Key9) ||
               isKeyDown(KeyA) ||
               isKeyDown(KeyB) ||
               isKeyDown(KeyC) ||
               isKeyDown(KeyD) ||
               isKeyDown(KeyE) ||
               isKeyDown(KeyF);

    }
    
    unsigned char InputManager::waitForKeyPress() const
    {
        LOG(INFO) << _Tag << "Waiting for key press";
        bool keypress = false;
        unsigned char ret = 0;
        while(!keypress) {
            SDL_Event event;
            while(event.type != SDL_KEYDOWN) {
                SDL_PollEvent(&event);
                switch(event.type) {
                    case SDL_KEYDOWN:
                    {
                        // Verify the keypress is actually a chip8 key.
                        unsigned char hex = 0;
                        if(toHex(event.key.keysym.scancode, hex)) {
                            ret = hex;
                            keypress = true;
                            LOG(INFO) << _Tag << "Key press = " << ret;
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        return ret;
    }
            
    bool InputManager::isValidKey(unsigned char key) const
    {
        return key >= 0 && key < 0xF;
    }
            
    bool InputManager::toHex(SDL_Scancode key, unsigned char &hex) const
    {
        for(unsigned char i = 0; i < 0xF; i++) {
            if(Keys[i] == key) {
                hex = i;
                return true;
            }
        }
        return false;
    }
}
