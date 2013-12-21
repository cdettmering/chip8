#include <Memory.hpp>
namespace Chip8 
{
    Memory::Memory()
    {

    }

    Memory & Memory::instance()
    {
        static Memory instance;
        return instance;
    }
}
