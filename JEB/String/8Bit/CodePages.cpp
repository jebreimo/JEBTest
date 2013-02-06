#include "CodePages.hpp"

namespace JEB { namespace CodePages {

unsigned codepointCp1252(char c)
{
    static unsigned specialChars[] = {
        0x20AC,   0x81, 0x201A, 0x0192,
        0x201E, 0x2026, 0x2020, 0x2021,
        0x20C6, 0x2030, 0x0160, 0x2039,
        0x0152,   0x8D, 0x017D,   0x8F,
          0x90, 0x2018, 0x2019, 0x201C,
        0x201D, 0x2022, 0x2013, 0x2014,
        0x02DC, 0x2122, 0x0161, 0x203A,
        0x0153,   0x9D, 0x017E, 0x0178
    };
    unsigned char uc = (unsigned char)c;
    if (uc < 0x80 || 0xA0 <= uc)
        return (unsigned char)uc;
    else
        return specialChars[uc - 0x80];
}

struct CodePointChar
{
    unsigned codepoint;
    char character;
};

template <size_t N>
static bool findCharacter(CodePointChar (&mapping)[N],
                          unsigned codepoint,
                          char& c)
{
    size_t beg = 0, end = N;
    while (beg < end)
    {
        size_t mid = (beg + end) / 2;
        if (mapping[mid].codepoint < codepoint)
            beg = mid + 1;
        else
            end = mid;
    }
    if (beg == N || mapping[beg].codepoint != codepoint)
        return false;

    c = mapping[beg].character;
    return true;
}

char characterCp1252(unsigned codepoint, bool* found)
{
    static CodePointChar mapping[] = {
          0x81, '\x81',   0x8D, '\x8D',
          0x8F, '\x8F',   0x90, '\x90',
          0x9D, '\x9D', 0x0152, '\x8C',
        0x0153, '\x9C', 0x0160, '\x8A',
        0x0161, '\x9A', 0x0178, '\x9F',
        0x017D, '\x8E', 0x017E, '\x9E',
        0x0192, '\x83', 0x02DC, '\x98',
        0x2013, '\x96', 0x2014, '\x97',
        0x2018, '\x91', 0x2019, '\x92',
        0x201A, '\x82', 0x201C, '\x93',
        0x201D, '\x94', 0x201E, '\x84',
        0x2020, '\x86', 0x2021, '\x87',
        0x2022, '\x95', 0x2026, '\x85',
        0x2030, '\x89', 0x2039, '\x8B',
        0x203A, '\x9B', 0x20AC, '\x80',
        0x20C6, '\x88', 0x2122, '\x99'
    };
    if (found)
        *found = true;
    if (codepoint < 0x80 || (0xA0 <= codepoint && codepoint <= 0xFF))
    {
        return (char)codepoint;
    }
    else
    {
        char c;
        if (findCharacter(mapping, codepoint, c))
            return c;
    }
    if (found)
        *found = false;

    return '\0';
}


}}
