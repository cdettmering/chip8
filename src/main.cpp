#include <Memory.hpp>
#include <Cpu.hpp>
#include <BitUtils.hpp>

#include <glog/logging.h>                            s
#include <iostream>

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

    unsigned char data1 = 0xAB;
    unsigned char data2 = 0xCD;
    std::cout << (unsigned int) Chip8::BitUtils::combine(data1, data2) << std::endl;
    return 0;
}
