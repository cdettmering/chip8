#include <Cpu.hpp>

namespace Chip8
{
    Cpu::Cpu()
    {

    }

    Cpu & Cpu::instance()
    {
        static Cpu instance;
        return instance;
    }
}
