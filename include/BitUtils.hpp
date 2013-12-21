/**
* @file BitUtils.hpp
* @brief  Utils for bit operations. This class will include functions that make 
*         dealing with bits easier.
* @author cdettmering
* @version 0.1
* @date 2013-12-21
*/
#ifndef CHIP8_BITUTILS_HPP
#define CHIP8_BITUTILS_HPP


namespace Chip8
{

    /**
    * @brief Utils for bit operations, makes dealing with bits easier.
    */
    class BitUtils
    {
        public:

            /**
            * @brief Queries a bit from a byte.
            *
            * @param data The byte to query from.
            * @param bit The bit to query (0-7 where 0 is the least significant bit
            *            and 7 is the most significant bit in big endian).
            *
            * @return The bit at index bit from data.
            */
            static unsigned char bitQuery(unsigned char data, unsigned char bit);
    };
}
#endif
