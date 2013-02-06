#ifndef JEB_ENCODING_CODEPAGES_HPP
#define JEB_ENCODING_CODEPAGES_HPP

#include <cstddef>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace CodePages {

unsigned codepointCp1252(char c);

/** Returns the character in CP1252 that correspond to @a codepoint.
 *
 *  @param found if non-NULL it's assigned true if CP1252 has a character
 *          that correspond to @a codepoint and false if not.
 *  @return the corresponding character if found or 0 if the character isn't
 *          found (it also returns 0 if @a codepoint is 0).
 */
char characterCp1252(unsigned codepoint, bool* found = NULL);

}}

#endif
