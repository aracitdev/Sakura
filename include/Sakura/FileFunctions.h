/**
  * @file FileFunctions.h
  * Provides some functions for loading/saving binary data.
  */

#ifndef FILEFUNCTIONS_H_INCLUDED
#define FILEFUNCTIONS_H_INCLUDED
#include <fstream>
#include <vector>


/**
  * @namespace Sakura
  */
namespace Sakura
{

/**
  * @param in The stream to load from.
  * @tparam T The type to load.
  * @param v The value to load into.
  * Loads a value from a binary stream.
  */
template <class T>
void Read(std::istream& in, T& v)
{
    in.read((char*)(&v),sizeof(T));
}


/**
  * @param in The stream to load from.
  * @tparam The type to load.
  * @return The loaded value.
  * Loads a value from a stream and returns it.
  */
template <class T>
T Read(std::istream& in)
{
    T returnV;
    in.read((char*)(&returnV), sizeof(T));
    return returnV;
}


/**
  * @param out The stream to save to.
  * @tparam T The type to save.
  * @param v The value to save.
  * Saves a value to a stream.
  */
template <class T>
void Write(std::ostream& out, T v)
{
    out.write((const char*)(&v), sizeof(T));
}


/**
  * @param in The stream to read from.
  * @param count The number of bytes to read.
  * @return The read bytes.
  * Reads count bytes from the stream and returns it as a vector of characters.
  */
std::vector<uint8_t> ReadBytes(std::istream& in,size_t count);


/**
  * @param file The name of the file.
  * @return True if the file exists, false if it doesn't.
  * A platform agnostic way of checking if a file exists or not.
  */
bool FileExists(const std::string& file);

/**
  * @param in The stream to read from
  * @return The read string.
  * Reads a string encoded in the C# format from the stream.
  * Specifically this is:
  * Size: 7 bits used to encode bits, 8th bit used to indicate whether more bits avaliable
  * After size comes the data.
  */
std::string ReadString(std::istream& in);

/**
  * @param out The stream to save to.
  * @param v The string to save.
  * Saves a string to a file stream in the C# encoded format (check ReadString for details).
  */
void WriteString(std::ostream& out, const std::string& v);

/**
  * @param path The path to create.
  * A platform agnostic way of creating paths.
  * Creates all sub directories needed to make it.
  */
void CreatePath(const std::string& path);


}
#endif // FILEFUNCTIONS_H_INCLUDED
