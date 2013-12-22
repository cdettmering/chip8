#include <Cpu.hpp>
#include <BitUtils.hpp>

namespace Chip8
{
    const std::string _Tag = "Cpu:";

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
        unsigned char byte = 0;
        if(Memory::instance().read(_pc, byte)) {
            LOG(FATAL) << _Tag << "Failed to fetch next instruction at " << _pc;
        }
        _pc++;
        return byte;
    }

    void Cpu::step()
    {
        unsigned char upper = fetch();
        unsigned char lower = fetch();
        unsigned int address = extractAddress(upper, lower);
        unsigned char firstLevelOpcode = BitUtils::upper(upper);

        switch(firstLevelOpcode) {
         case 0x0:
            break;
         case 0x1:
            break;
         case 0x2:
            break;
         case 0x3:
            break;
         case 0x4:
            break;
         case 0x5:
            break;
         case 0x6:
            break;
         case 0x7:
            break;
         case 0x8:
            break;
         case 0x9:
            break;
         case 0xA:
            break;
         case 0xB:
            break;
         case 0xC:
            break;
         case 0xD:
            break;
         case 0xE:
            break;
         case 0xF:
            break;
         default:
            LOG(INFO) << _Tag << "First level opcode not recognized " << firstLevelOpcode;
        }
    }

    unsigned int Cpu::extractAddress(unsigned char upper, unsigned char lower)
    {
        return BitUtils::combine(BitUtils::lower(upper), lower);
    }
}
