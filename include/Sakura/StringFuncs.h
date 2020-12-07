/**
 * @file StringFuncs.h
 * Specifies some functions for dealing with strings.
 */

#ifndef STRINGFUNCS_H_INCLUDED
#define STRINGFUNCS_H_INCLUDED
#include <vector>
#include <string>

/**
  * @namespace Sakura
  */
namespace Sakura
{

/**
  * @param subject The string to spit.
  * @param lineDelimiter delimiter what character counts as "end of line" or new row
  * @param elementDelimiter what character separates elements or new column
  * @return A tokenized version of the string.
  * Separates a string into a 2D array.
  * line delimiter represents a new row (creates a new vector on the output)
  * char delimiter represents a new column (creates a new integer on the latest vector)
  */
std::vector<std::vector<int>> SplitStringToIntArray(const std::string& subject, char lineDelimiter, char elementDelimiter);


/**
  * @param subject The string to tokenize
  * @param delimiter The separating character for tokens.
  * @return The split up strings.
  * Separates a string into multiple character arrays (strings), broken apart by the delimiter character.
  */
std::vector<std::vector<char>> SplitStringToCharArray(const std::string& subject, char delimiter);

/**
  * @param subject The string to split.
  * @param delimiter The separating character for tokens.
  * @return The split up strings.
  * Separates a string into multiple strings, broken apart by the delimiter character.
  */
std::vector<std::string> SplitString(const std::string& subject, char delimiter);


/**
  * @param subject The string to replace in.
  * @param search The string to search for.
  * @param replace The string to replace search with.
  * Replaces all instances of search with replace in the string subject.
  */
void StringReplace(std::string& subject, const std::string& search,const std::string& replace);
}

#endif // STRINGFUNCS_H_INCLUDED
