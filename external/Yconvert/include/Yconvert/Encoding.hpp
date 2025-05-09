//****************************************************************************
// Copyright © 2020 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2020-06-01.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <iosfwd>
#include <string>
#include "Endian.hpp"
#include "YconvertDefinitions.hpp"

namespace Yconvert
{
    enum class Encoding
    {
        UNKNOWN = 0,
        UTF_8,
        UTF_16_LE,
        UTF_16_BE,
        UTF_32_LE,
        UTF_32_BE,
        ASCII,
        UTF_16_NATIVE = IS_LITTLE_ENDIAN ? UTF_16_LE : UTF_16_BE,
        UTF_32_NATIVE = IS_LITTLE_ENDIAN ? UTF_32_LE : UTF_32_BE,
        WSTRING_NATIVE = sizeof(wchar_t) == 2 ? UTF_16_NATIVE : UTF_32_NATIVE,
    #ifdef YCONVERT_ISO_CODE_PAGES
        ISO_8859_1 = 128,
        ISO_8859_2,
        ISO_8859_3,
        ISO_8859_4,
        ISO_8859_5,
        ISO_8859_6,
        ISO_8859_7,
        ISO_8859_8,
        ISO_8859_9,
        ISO_8859_10,
        ISO_8859_11,
        ISO_8859_13,
        ISO_8859_14,
        ISO_8859_15,
        ISO_8859_16,
    #endif
    #ifdef YCONVERT_MAC_CODE_PAGES
        MAC_CYRILLIC = 256,
        MAC_GREEK,
        MAC_ICELAND,
        MAC_LATIN2,
        MAC_ROMAN,
        MAC_TURKISH,
    #endif
    #ifdef YCONVERT_DOS_CODE_PAGES
        DOS_CP437 = 512,
        DOS_CP737,
        DOS_CP775,
        DOS_CP850,
        DOS_CP852,
        DOS_CP855,
        DOS_CP857,
        DOS_CP860,
        DOS_CP861,
        DOS_CP862,
        DOS_CP863,
        DOS_CP864,
        DOS_CP865,
        DOS_CP866,
        DOS_CP869,
        DOS_CP874,
    #endif
    #ifdef YCONVERT_WIN_CODE_PAGES
        WIN_CP1250 = 1024,
        WIN_CP1251,
        WIN_CP1252,
        WIN_CP1253,
        WIN_CP1254,
        WIN_CP1255,
        WIN_CP1256,
        WIN_CP1257,
        WIN_CP1258,
    #endif
    };

    struct EncodingInfo
    {
        Encoding encoding;
        std::string_view name = {};
        std::string_view byte_order_mark = {};
        size_t unit_size = 0;
        size_t max_units = 0;
        Endianness endianness = Endianness::UNKNOWN;
    };

    /**
     * @brief Return the @a EncdingInfo instance for @a encoding.
     */
    [[nodiscard]]
    YCONVERT_API const EncodingInfo& get_info(Encoding encoding);

    /**
     * @brief Returns the EncodingInfos for the encodings supported by
     *  Yconvert.
     *
     * The first element of the pair is a pointer to the first
     * EncodingInfo, the second element is the number of encodings.
     */
    [[nodiscard]]
    YCONVERT_API std::pair<const EncodingInfo*, size_t> get_all_encodings();

    /**
     * @brief Returns the @a Encoding that corresponds to @a name.
     */
    YCONVERT_API Encoding encoding_from_name(std::string name);

    /**
     * @brief Checks the list of known byte-order marks and returns the one
     *  that matches the start of @a bom.
     */
    [[nodiscard]]
    YCONVERT_API Encoding determine_encoding_from_byte_order_mark(
        const char* str, size_t len);


    /**
     * @brief Analyzes the contents of @a str and returns what it believes is
     *  most likely to @a str's encoding.
     */
    [[nodiscard]]
    YCONVERT_API Encoding determine_encoding_from_first_character(
        const char* str, size_t len);

    /**
     * @brief Returns the encoding used in @a stream and the offset the
     *  first character following the byte-order mark.
     *
     * The function first tries to determine the encoding based on
     * @a buffer's byte-order mark. If there isn't one, the contents of the
     * buffer is analyzed instead.
     */
    [[nodiscard]]
    YCONVERT_API std::pair<Encoding, size_t> determine_encoding(
        const char* buffer, size_t length);

    /**
     * @brief Returns the encoding used in @a stream.
     *
     * Will look for a byte-order mark (bom) at the start of a stream. If one
     * is found it returns the corresponding encoding and leaves the stream at
     * the first byte after the bom. If one isn't found, it will read
     * @a maxScanLength number of bytes, do some basic analysis and try to
     * guess the encoding, and then reposition the stream back to its
     * original position.
     *
     * @throw YconvertException if it was not possible to to set the position
     *  indicator of @a stream with std::ios::seekg. std::cin, for instance,
     *  does not necessarily support seekg.
     */
    YCONVERT_API Encoding determine_encoding(std::istream& stream);

    /**
     * @brief Returns the number of valid code points in @a buffer.
     * @param buffer an encoded string
     * @param length the length of the buffer
     * @param encoding the string's encoding
     * @return first is the number of valid code points, second is the number of
     *  bytes that were read.
     *
     *  If the number of bytes that were read is less than @a length, it means
     *  that the buffer contains invalid code points.
     */
    [[nodiscard]]
    YCONVERT_API std::pair<size_t, size_t>
    count_valid_codepoints(const void* buffer, size_t length,
                           Encoding encoding);

    /**
     * @brief Checks if a string contains only valid code points in a given encoding.
     * @param buffer an encoded string
     * @param length the length of the buffer
     * @param encoding the string's encoding
     * @return true if the buffer contains only valid code points.
     */
    [[nodiscard]]
    YCONVERT_API bool check_encoding(const void* buffer, size_t length,
                                     Encoding encoding);
}
