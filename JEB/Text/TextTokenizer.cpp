//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//***************************************************************************
#include "TextTokenizer.hpp"

#include "JEB/String/StringPredicates.hpp"
#include "JEB/String/String.hpp"
#include "JEB/String/Utf8/EscapedString.hpp"

namespace JEB
{

using namespace JEB::String;

TextTokenizer::TextTokenizer()
    : m_TokenType(Undefined)
{
    m_NextToken = m_Token.end();
}

TextTokenizer::TextTokenizer(const std::string* text)
{
    setText(text);
}

bool TextTokenizer::endOfText() const
{
    return m_It == m_Text->end();
}

const std::string* TextTokenizer::text() const
{
    return m_Text;
}

void TextTokenizer::setText(const std::string* text)
{
    m_Text = text;
    m_It = text->begin();
    m_Token.clear();
    m_NextToken = m_Token.end();
    m_TokenType = Undefined;
}

TextTokenizer::TokenType TextTokenizer::tokenType() const
{
    return m_TokenType;
}

uint32_t getCharacter(const std::pair<uint32_t, bool>& value)
{
    if (value.second)
    {
        if (value.first == '_')
            return Unicode::ZeroWidthSpace;
        else if (value.first == ' ')
            return Unicode::NoBreakSpace;
        else if (value.first == '-')
            return Unicode::SoftHyphen;
    }
    return value.first;
}

uint32_t TextTokenizer::nextCharacter()
{
    uint32_t ch = getCharacter(Utf8::unescapeNext(m_It, m_Text->end(), '&'));
    String::appendInPlace(m_Token, ch);
    return ch;
}

uint32_t TextTokenizer::peekNextCharacter() const
{
    std::string::const_iterator it = m_It;
    uint32_t ch = getCharacter(Utf8::unescapeNext(it, m_Text->end(), '&'));
    return ch;
}

void TextTokenizer::endOfWhitespace()
{
    while (!endOfText())
    {
        uint32_t ch = peekNextCharacter();
        if (!isWhitespace(ch) || isNewline(ch) || ch == Unicode::NoBreakSpace)
            break;
        nextCharacter();
    }
}

void TextTokenizer::endOfWord()
{
    while (!endOfText())
    {
        uint32_t ch = peekNextCharacter();
        if (ch == Unicode::SoftHyphen ||
            (isWhitespace(ch) &&
             ch != Unicode::NoBreakSpace))
            break;
        nextCharacter();
    }
}

bool TextTokenizer::nextToken()
{
    if (m_NextToken != m_Token.end())
    {
        if (m_NextToken != m_Token.begin())
            m_Token.assign(m_NextToken, m_Token.cend());
        m_NextToken = m_Token.end();
        return true;
    }

    m_Token.clear();

    if (endOfText())
        return false;

    uint32_t ch = nextCharacter();

    if (isNewline(ch))
    {
        if (ch == '\r' && !endOfText() && peekNextCharacter() == '\n')
            nextCharacter();
        m_TokenType = TextTokenizer::Newline;
    }
    else if (ch == Unicode::SoftHyphen)
    {
        m_TokenType = TextTokenizer::SoftHyphen;
    }
    else if (ch == Unicode::ZeroWidthSpace)
    {
        m_TokenType = TextTokenizer::ZeroWidthSpace;
    }
    else if (isWhitespace(ch) && ch != Unicode::NoBreakSpace)
    {
        endOfWhitespace();
        m_TokenType = TextTokenizer::Whitespace;
    }
    else if (isCharClass(Unicode::CharClass::Control, ch))
    {
        m_TokenType = TextTokenizer::Control;
    }
    else
    {
        endOfWord();
        m_TokenType = TextTokenizer::Word;
    }

    m_NextToken = m_Token.end();
    return true;
}

void TextTokenizer::resetCurrentToken()
{
    m_NextToken = m_Token.begin();
}

bool TextTokenizer::splitToken(size_t index)
{
    m_NextToken = chrRange(m_Token, (long)index).second;
    return m_NextToken != m_Token.end();
}

const std::string& TextTokenizer::token() const
{
    return m_Token;
}

}
