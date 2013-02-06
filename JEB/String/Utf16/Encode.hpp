#ifndef JEB_ENCODING_UTF16_ENCODE_HPP
#define JEB_ENCODING_UTF16_ENCODE_HPP

#include <cstdint>
#include <limits>
#include <string>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Utf16 {

template <typename OutIt, bool SwapBytes>
OutIt add(OutIt out, uint32_t codePoint);

template <typename OutIt>
OutIt add(OutIt out, uint32_t codePoint);

template <typename OutIt>
OutIt addLE(OutIt out, uint32_t codePoint);

template <typename OutIt>
OutIt addBE(OutIt out, uint32_t codePoint);

}}}

#include "Encode_Impl.hpp"

#endif
