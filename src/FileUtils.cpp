#include <fstream>
#include <FileUtils.hpp>

namespace Chip8
{
    std::vector <unsigned char> FileUtils::readRom(const std::string &filename)
    {
        std::fstream file;
        std::vector<unsigned char> data;

        // Open the file.
        file.open(filename.c_str(), std::fstream::in | std::fstream::binary);

        if(file.is_open()){
            // Find the length of the file.
            file.seekg(0, file.end);
            int length = file.tellg();
            file.seekg(0, file.beg);

            // Store the file into a buffer. 
            char *buffer = new char[length];
            file.read(buffer, length);

            // Put the file in our vector.
            for(int i = 0; i < length; i++){
                data.push_back(buffer[i]);
            }

            // Clean up.
            delete[] buffer;
            file.close();
        }
        return data;
    }
}
