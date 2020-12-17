#include "FileFunctions.h"

#include <filesystem>
#include <math.h>

namespace Sakura
{
void WriteString(std::ostream& out, const std::string& v)
{
    size_t size = v.size();
    while(size > 127)
    {
        Write<uint8_t>(out, (size & 127) | 128); //C# enocdes this pretty weirdly
    }
    Write<uint8_t>(out,size);
    out.write(v.c_str(),v.size());
}

std::string ReadString(std::istream& in)
{
    std::string returnV;

    size_t size = 0;
    size_t count = 0;
    uint8_t byte = 0;
    do
    {
        byte = Read<uint8_t>(in);
        size += (byte & 127) << (count * 7);
        count ++;
    }
    while( ((byte >> 7)&0x01) != 0);

    returnV.resize(size);
    for(size_t i=0; i < size; i++)
        returnV[i]=in.get();
    return returnV;
}

bool FileExists(const std::string& file)
{
    return std::filesystem::exists(file);
}

void CreatePath(const std::string& path)
{
    std::filesystem::create_directories(path);
}

std::vector<uint8_t> ReadBytes(std::istream& in,size_t count)
{
    std::vector<uint8_t> returnV(count);
    in.read((char*)&(returnV[0]), count);
    return returnV;
}
}
