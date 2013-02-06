//****************************************************************************
// Copyright © 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//****************************************************************************
#ifndef JEB_STRING_UTF8_ENCODE_HPP
#define JEB_STRING_UTF8_ENCODE_HPP

#include <cstdint>
#include <iterator>
#include <limits>
#include "JEB/JEBDefinitions.hpp"

/** @file
  * @brief Defines functions for working with UTF-8 encoded strings.
  */

namespace JEB { namespace String {
/** @brief Groups all functions for working with UTF-8-encoded strings.
  */
namespace Utf8 {

/** @brief The maximum length of an UTF-8-encoded code point.
  */
static const size_t MAX_ENCODED_LENGTH = 8;

/** @brief Adds @a codePoint encoded as UTF-8 to @a it.
 *
 *  @return the new iterator position.
 */
template <typename OutputIt>
OutputIt add(OutputIt it, uint32_t codePoint);

/** @brief Encodes a unicode code point as UTF-8.
  *
  * @note The function does not add a terminating 0 to @a buffer.
  *
  * @param buffer a buffer for the UTF-8 code point, it must be at least as
  *     long as the encoding (i.e. 7 bytes to be error proof).
  * @param chr the code point to be encoded
  * @param bufferSize the size of @a buffer
  * @return the length of the encoded code point, or 0 if @a bufferSize is
  *     too small.
  */
size_t encode(char* buffer, uint32_t chr, size_t bufferSize);

/** @brief Encodes a unicode code point as UTF-8.
 *  @return the length of the encoded code point.
 */
size_t encode(char (&buffer)[MAX_ENCODED_LENGTH], uint32_t chr);

size_t encodedLength(uint32_t c);

}}
}

#include "Encode_Impl.hpp"
#endif
