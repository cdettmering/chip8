#ifndef CHIP8_CPU_HPP
#define CHIP8_CPU_HPP

#include <string>

namespace Chip8
{
    
    /**
    * @brief Emulates the Chip8 CPU, which has an 8 bit architecture with 35 opcodes.
    */
    class Cpu
    {
        public:

            /**
            * @brief Gets the singleton instance of the Cpu module.
            *
            * @return Singleton instance of the Cpu module.
            */
            static Cpu & instance();

            /**
            * @brief Fetches the next byte from the ROM. Increases
            *        the PC by 1.
            *
            * @return The next byte of the rom.
            */
            unsigned char fetch();

            /**
            * @brief Executes the current instruction on the CPU.
            */
            void step();

            /**
            * @brief Jumps execution to address.
            *
            * @param address The memory address to jump to.
            */
            void jump(unsigned int address);

            /**
            * @brief Calls the subroutine at address.
            *
            * @param address The address of the subroutine to call.
            */
            void call(unsigned int address);

            /**
            * @brief Returns from the current subroutine.
            */
            void ret();

            /**
            * @brief Skips the next Chip8 instruction (2 bytes).
            */
            void skipNextInstruction();

            /**
            * @brief Adds a + b. Sets VF to 1 if a carry occurred when adding.
            *
            * @param a First number.
            * @param b Second number.
            *
            * @return a + b
            */
            unsigned char add(unsigned char a, unsigned char b) const;

            /**
            * @brief Subtracts a - b. Sets VF to 1 if NO borrow occurred when subtracting.
            *
            * @param a First number.
            * @param b Second number.
            *
            * @return a - b
            */
            unsigned char sub(unsigned char a, unsigned char b) const;

            /**
            * @brief Generates a random byte (0-255)
            *
            * @return A number between 0 - 255
            */
            unsigned char randomByte() const;

            /**
             * @brief Flag telling the CPU to wait for a key press before continuing
             */
            static bool IsWaitingForKeyPress;

        private:
            // For a correct singleton implementation it is necessary to make
            // the constructor, copy constructor and assignment operators private,
            // so that there isn't any accidental copying.
            Cpu();
            Cpu(const Cpu &other);
            Cpu & operator=(const Cpu &other);
                
            // Extracts the 16 bit address out of the instruction defined by upper + lower
            unsigned int extractAddress(unsigned char upper, unsigned char lower);

            // Program Counter and Stack Pointer
            int _pc;
            int _sp;

            unsigned int _stack[16];

            static const std::string _Tag;
    };
}

#endif
