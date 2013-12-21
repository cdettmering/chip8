#include <BitUtils.hpp>
#include <glog/logging.h>

namespace Chip8
{

    const std::string BitUtils::_Tag = "BitUtils:";

    unsigned char BitUtils::bitQuery(unsigned char data, unsigned char bit)
    {
        return data >> bit | 0x1;
    }

    unsigned char BitUtils::upper(unsigned char data)
    {
        return data >> 4 & 0xF;
    }

    unsigned char BitUtils::lower(unsigned char data)
    {
        return data & 0xF;
    }

    unsigned int BitUtils::combine(unsigned char data1, unsigned char data2)
    {
        unsigned int ret = data1;
        ret = (ret << 8) | data2;
        return ret;
    }
}
