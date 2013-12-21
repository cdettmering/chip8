/**
* @file Memory.hpp
* @brief Manages the memory.
* @author Lucas Wolford
* @version 0.1
* @date 2013-12-21
*/

#ifndef CHIP8_MEMORY_HPP
#define CHIP8_MEMORY_HPP

namespace Chip8
{
    
    /**
    * @brief Emulates the Chip8 memory architecture. Chip8 has 4096 bytes of memory
    *        where the first 0x200 bytes are reserved for the interpreter.
    */
    class Memory
    {
        public:

            /**
            * @brief Gets the singleton instance of the Memory module.
            *
            * @return Singleton instance of the Memory module.
            */
            static Memory & instance();

            /**
            * @brief Reads an address in memory.
            *
            * @param address The address to be read.
            * @param byte The reference to be given a value.
            *
            * @return A boolean denoting success or failure. 
            */
            bool read(unsigned int address, unsigned char &byte) const;

            /**
            * @brief Writes a value to an address in memory. 
            *
            * @param address The address to recieve the value.
            * @param byte The value to be written.
            *
            * @return A boolean denoting success or failure. 
            */
            bool write(unsigned int address, unsigned char byte);

            /**
            * @brief The maximum number of memory addresses.
            */
            static const unsigned int MaxAddress;

        private:
            // For a correct singleton implementation it is necessary to make
            // the constructor, copy constructor and assignment operators private,
            // so that there isn't any accidental copying.
            Memory();
            Memory(const Memory &other);
            Memory & operator=(const Memory &other);

            bool validAddress(unsigned int address) const;

            unsigned char _memory[4096];
    };
}

#endif
