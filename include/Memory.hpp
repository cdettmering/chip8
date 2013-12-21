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

        private:
            // For a correct singleton implementation it is necessary to make
            // the constructor, copy constructor and assignment operators private,
            // so that there isn't any accidental copying.
            Memory();
            Memory(const Memory &other);
            Memory & operator=(const Memory &other);
    };
}

#endif
