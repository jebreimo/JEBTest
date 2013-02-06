#include <algorithm>

namespace JEB { namespace String { namespace Utf8 {

template <typename OutputIt>
OutputIt add(OutputIt it, uint32_t c)
{
    size_t length = encodedLength(c);
    if (length == 1)
    {
        *it++ = (char)c;
    }
    else
    {
        size_t shift = (length - 1) * 6;
        *it = (char)((0xFF << (8 - length)) | (c >> shift));
        for (size_t i = 1; i < length; i++)
        {
            shift -= 6;
            *it = (char)(0x80 | ((c >> shift) & 0x3F));
        }
    }
    return it;
}

}}}
