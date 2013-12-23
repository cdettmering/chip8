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

            void jump(unsigned int address);

            /**
            * @brief Calls the subroutine at address.
            *
            * @param address The address of the subroutine to call.
            */
            void call(unsigned int address);

            void skipNextInstruction();

            unsigned char add(unsigned char a, unsigned char b) const;
            unsigned char sub(unsigned char a, unsigned char b) const;
            unsigned char randomByte() const;

        private:
            // For a correct singleton implementation it is necessary to make
            // the constructor, copy constructor and assignment operators private,
            // so that there isn't any accidental copying.
            Cpu();
            Cpu(const Cpu &other);
            Cpu & operator=(const Cpu &other);

            unsigned int extractAddress(unsigned char upper, unsigned char lower);

            // Program Counter
            unsigned int _pc;

            static const std::string _Tag;
    };
}

#endif
