#include <BitUtils.hpp>

namespace Chip8
{
    unsigned char BitUtils::bitQuery(unsigned char data, unsigned char bit)
    {
        return data >> bit | 0x1;
    }
}
