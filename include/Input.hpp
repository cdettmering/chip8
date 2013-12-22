/**
* @file Input.hpp
* @brief Makes handling input easier through convenience functions.
* @author Chad Dettmering
* @version 0.1
* @date 2013-12-21
*/

#ifndef CHIP8_INPUT_HPP
#define CHIP9_INPUT_HPP

#include <SDL_scancode.h>
#include <string>

namespace Chip8
{

    /**
    * @brief Manages input events from the user, and offers a few conenience
    *        functions to make things easier.
    */
    class InputManager
    {
        public:

            static InputManager & instance();

            /**
            * @brief Checks if a key is down.
            *
            * @param key The key to check.
            *
            * @return True if the key is currently down, false otherwise.
            */
            bool isKeyDown(SDL_Scancode key) const;

            /**
            * @brief Checks if any key is down.
            *
            * @return True if any key is down, false otherwise.
            */
            bool anyKeyDown() const;

            /**
            * @brief Halts execution and waits for a keypress.
            *
            * @return The key that was pressed.
            */
            unsigned char waitForKeyPress() const;

            /**
            * @brief Checks if the hex representation of the key is valid.
            *
            * @param key The hex number of the key.
            *
            * @return True if the key is valid, false othewise.
            */
            bool isValidKey(unsigned char key) const;

            /**
            * @brief Converts key to the hex representation.
            *
            * @param key The scancode to convert.
            * @param hex The hex representation will be stored in this variable.
            *
            * @return True if hex representation is stored in hex, false otherwise.
            */
            bool toHex(SDL_Scancode key, unsigned char &hex) const;

            static const SDL_Scancode Key0;
            static const SDL_Scancode Key1;
            static const SDL_Scancode Key2;
            static const SDL_Scancode Key3;
            static const SDL_Scancode Key4;
            static const SDL_Scancode Key5;
            static const SDL_Scancode Key6;
            static const SDL_Scancode Key7;
            static const SDL_Scancode Key8;
            static const SDL_Scancode Key9;
            static const SDL_Scancode KeyA;
            static const SDL_Scancode KeyB;
            static const SDL_Scancode KeyC;
            static const SDL_Scancode KeyD;
            static const SDL_Scancode KeyE;
            static const SDL_Scancode KeyF;
            static const SDL_Scancode Keys[];
        private:
            InputManager();
            InputManager(const InputManager &other);
            InputManager & operator=(const InputManager &other);

            static const std::string _Tag;
    };
}
#endif
