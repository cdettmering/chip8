#include <Cpu.hpp>
#include <BitUtils.hpp>

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

    unsigned char Cpu::fetch()
    {
        // Read next memory address past the PC
        // Memory::instance().read(_pc)
        _pc++;
    }

    void Cpu::step()
    {
        unsigned char upper = fetch();
        unsigned char lower = fetch();
        unsigned int address = extractAddress(upper, lower);
        unsigned char firstLevelOpcode = BitUtils::upper(upper);

        switch(firstLevelOpcode) {
        }
    }

    unsigned int Cpu::extractAddress(unsigned char upper, unsigned char lower)
    {
        return 0;
    }
}
