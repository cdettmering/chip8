#include <Memory.hpp>
namespace Chip8 
{
    const unsigned int Memory::MaxAddress = 4095;

    Memory::Memory()
    {

    }

    Memory & Memory::instance()
    {
        static Memory instance;
        return instance;
    }

    bool Memory::read(unsigned int address, unsigned char &byte) const
    {
        if(validAddress(address)){
            byte = _memory[address];
            return true;
        }
        return false;
    }

    bool Memory::write(unsigned int address, unsigned char byte)
    {
        if(validAddress(address)){
            _memory[address] = byte;
            return true;
        }
        return false;
    }

    bool Memory::validAddress(unsigned int address) const
    {
        return address < MaxAddress;
    }
}
