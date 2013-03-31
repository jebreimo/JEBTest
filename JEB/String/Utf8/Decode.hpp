//****************************************************************************
// Copyright © 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//****************************************************************************
#ifndef JEB_STRING_UTF8_DECODE_HPP
#define JEB_STRING_UTF8_DECODE_HPP

#include <cstdint>
#include <iterator>
#include <limits>
#include "JEB/JEBDefinitions.hpp"
#include "JEB/String/StringFlags.hpp"

/** @file
  * @brief Defines functions for working with UTF-8 encoded strings.
  */

namespace JEB { namespace String { namespace Utf8 {

template <typename FwdIt>
bool isValid(FwdIt begin, FwdIt end);

/** @brief Assigns the code point starting at @a it to @a codePoint.
  *
  * @note The function returns false both when it has reached the end of the
  *     string and when it has encountered an invalid byte. The caller must
  *     compare @a it with @a end to determine why the result is false.
  *
  * @param codePoint is assigned the code point starting at @a it.
  * @param it        start of the code point. Has been advanced to the start
  *     of the next code point upon return, or one byte past the first
  *     invalid byte in the current code point.
  * @param end       the end of the string.
  * @return @arg @a true a code point was successfully decoded
  *         @arg @a false reached the end of the string if @a it == @a end
  *                       otherwise the current code point isn't valid UTF-8.
  */
template <typename FwdIt>
int nextCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

/** @brief Assigns the code point ending at @a it to @a codePoint.
  */
template <typename FwdIt>
int prevCodePoint(uint32_t& codePoint, FwdIt& it, FwdIt begin);

}}
}

#include "Decode_Impl.hpp"
#endif
