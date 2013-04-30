#include "LineBuilder.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include "JEB/String/String.hpp"

namespace JEB
{
namespace internal
{

enum LineBuilderState
{
    StartOfLine,
    StartOfWord,
    SoftHyphenState,
    SpaceState
};

static const size_t DefaultTextWidth = 79;

LineBuilder::LineBuilder()
    : m_Destination(&std::cout),
      m_LineEndMode(LineEndMode::Newline),
      m_TextWidth(0),
      m_MaxTextWidth(DefaultTextWidth),
      m_State(StartOfLine)
{
}

LineBuilder::LineBuilder(std::ostream* destination)
    : m_Destination(destination),
      m_LineEndMode(LineEndMode::Newline),
      m_TextWidth(0),
      m_MaxTextWidth(DefaultTextWidth),
      m_State(StartOfLine)
{
}

std::ostream* LineBuilder::destination() const
{
    return m_Destination;
}

void LineBuilder::setDestination(std::ostream* destination)
{
    m_Destination = destination;
}

bool LineBuilder::empty() const
{
    return m_State == StartOfLine;
}

LineEndMode::Enum LineBuilder::lineEndMode() const
{
    return m_LineEndMode;
}

void LineBuilder::setLineEndMode(LineEndMode::Enum lineEndMode)
{
    m_LineEndMode = lineEndMode;
}

size_t LineBuilder::maxTextWidth() const
{
    return m_MaxTextWidth;
}

void LineBuilder::setMaxTextWidth(size_t maxTextWidth)
{
    assert(maxTextWidth >= 3);
    m_MaxTextWidth = maxTextWidth;
}

void LineBuilder::addNewline()
{
    if (m_State == SoftHyphenState)
        m_Destination->put('-');

    switch (m_LineEndMode)
    {
    case LineEndMode::Newline:
        m_Destination->put('\n');
        break;
    case LineEndMode::Fill:
        while (m_TextWidth++ <= m_MaxTextWidth)
            m_Destination->put(' ');
        break;
    default:
        break;
    }

    m_TextWidth = 0;
    m_State = StartOfLine;
}

void LineBuilder::addSoftHyphen()
{
    m_State = SoftHyphenState;
}

void LineBuilder::addSpace()
{
    if (m_State != StartOfLine)
        m_State = SpaceState;
}

size_t LineBuilder::addWhitespace(const std::string& whitespace)
{
    size_t length = String::numberOfCharacters(whitespace);
    if (length > m_MaxTextWidth)
        return length - m_MaxTextWidth;
    *m_Destination << whitespace;
    m_State = StartOfWord;
    m_TextWidth += length;
    return 0;
}

size_t LineBuilder::addWord(const std::string& word, bool leaveSpaceForHyphen)
{
    size_t length = String::numberOfCharacters(word);
    if (m_State == SpaceState)
        length++;
    size_t minimumLength = length;
    if (leaveSpaceForHyphen)
        minimumLength++;

    if (m_TextWidth + minimumLength > m_MaxTextWidth)
        return m_TextWidth + minimumLength - m_MaxTextWidth;

    if (m_State == SpaceState)
        *m_Destination << ' ';
    *m_Destination << word;
    m_TextWidth += length;
    m_State = StartOfWord;

    return 0;
}

void LineBuilder::addZeroWidthSpace()
{
    m_State = StartOfWord;
}

}
}
