#include <Memory.hpp>
#include <Fonts.hpp>

namespace Chip8 
{
    const unsigned int Memory::MaxAddress = 4096;
    const unsigned int Memory::StartAddress = 0x200;
    const unsigned char Memory::FirstRegisterAddress = 0x0;
    const unsigned char Memory::LastRegisterAddress = 0xF;

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
    
    bool Memory::setRegister(unsigned char reg, unsigned char data)
    {
        if(validRegisterAddress(reg)) {
            _registers[reg] = data;
            return true;
        }
        return false;
    }

    bool Memory::getRegister(unsigned char reg, unsigned char &data) const
    {
        if(validRegisterAddress(reg)) {
            data = _registers[reg];
            return true;
        }
        return false;
    }

    void Memory::setI(unsigned int data)
    {
        _addressRegister = data;
    }

    unsigned int Memory::getI() const
    {
        return _addressRegister;
    }
            
    unsigned int Memory::getFontAddress(unsigned char hex) const
    {
        // Fonts are loaded at 0x0 and have a byte size of Fonts::SpriteHeight.
        return 0x0 + hex * Fonts::SpriteHeight;
    }

    bool Memory::validAddress(unsigned int address) const
    {
        return address < MaxAddress;
    }

    bool Memory::validRegisterAddress(unsigned char reg) const
    {
        return reg >= FirstRegisterAddress && reg <= LastRegisterAddress;
    }
}
