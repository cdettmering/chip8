#ifndef CHIP8_BITUTILS_HPP
#define CHIP8_BITUTILS_HPP

namespace Chip8
{
    class BitUtils
    {
        public:
            static unsigned char bitQuery(unsigned char data, unsigned char bit);
    };
}
#endif
