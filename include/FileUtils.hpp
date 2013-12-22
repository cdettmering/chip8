/**
* @file FileUtils.hpp
* @brief Utility for common file functions.
* @author Lucas Wolford
* @version 0.1
* @date 2013-12-21
*/

#ifndef CHIP8_FILEUTILS_HPP
#define CHIP8_FILEUTILS_HPP

#include <vector>
#include <string>

namespace Chip8
{
    class FileUtils
    {
        public:
            /**
            * @brief Reads in the ROM file.
            *
            * @param fileName The path to the ROM file.
            *
            * @return The ROM file. 
            */
            static std::vector <unsigned char> readRom(const std::string &fileName);
    };
}
#endif
