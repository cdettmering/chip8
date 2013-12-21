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

#include <string>

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

            /**
            * @brief Extracts the upper 4 bits of data.
            *
            * @param data The byte to extract the upper 4 bits from.
            *
            * @return The upper 4 bits of data.
            */
            static unsigned char upper(unsigned char data);

            /**
            * @brief Extracts the lower 4 bits of data.
            *
            * @param data The byte to extract the lower 4 bits from.
            *
            * @return  The lower 4 bits of data.
            */
            static unsigned char lower(unsigned char data);

            /**
            * @brief Combines data1 and data2, where data1 will be the upper half
            *        and data 2 will be the lower half.
            *
            * @param data1 The upper byte.
            * @param data2 The lower byte.
            *
            * @return The combined bytes of data1 and data2.
            */
            static unsigned int combine(unsigned char data1, unsigned char data2);

        private:

            static const std::string _Tag;
    };
}
#endif
