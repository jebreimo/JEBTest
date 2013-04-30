//****************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//****************************************************************************
#include "TextFormatter.hpp"

#include <algorithm>
#include <ostream>
#include "JEB/String/String.hpp"
#include "LineBuilder.hpp"
#include "TextTokenizer.hpp"

namespace JEB
{

TextFormatter::TextFormatter()
    : m_LineBuilder(new internal::LineBuilder),
      m_Tokenizer(new TextTokenizer)
{
}

TextFormatter::TextFormatter(std::ostream* destination, const std::string* text)
    : m_LineBuilder(new internal::LineBuilder(destination)),
      m_Tokenizer(new TextTokenizer(text))
{
}

TextFormatter::~TextFormatter()
{
}

std::ostream* TextFormatter::destination() const
{
    return m_LineBuilder->destination();
}

void TextFormatter::setDestination(std::ostream* destination)
{
    m_LineBuilder->setDestination(destination);
}

bool TextFormatter::endOfText() const
{
    return m_Tokenizer->endOfText();
}

LineEndMode::Enum TextFormatter::lineEndMode() const
{
    return m_LineBuilder->lineEndMode();
}

void TextFormatter::setLineEndMode(LineEndMode::Enum lineEndMode)
{
    m_LineBuilder->setLineEndMode(lineEndMode);
}

size_t TextFormatter::textWidth() const
{
    return m_LineBuilder->maxTextWidth();
}

void TextFormatter::setTextWidth(size_t textWidth)
{
    m_LineBuilder->setMaxTextWidth(textWidth);
}

const std::string* TextFormatter::text() const
{
    return m_Tokenizer->text();
}

void TextFormatter::setText(const std::string* text)
{
    m_Tokenizer->setText(text);
}

size_t TextFormatter::format(size_t maxLines)
{
    size_t lines = 0;
    while (lines < maxLines && m_Tokenizer->nextToken())
    {
        switch (m_Tokenizer->tokenType())
        {
        case TextTokenizer::Control:
            if (m_LineBuilder->addWhitespace(m_Tokenizer->token()) != 0)
            {
                m_LineBuilder->addNewline();
                lines++;
            }
            break;
        case TextTokenizer::Newline:
            m_LineBuilder->addNewline();
            lines++;
            break;
        case TextTokenizer::SoftHyphen:
            m_LineBuilder->addSoftHyphen();
            break;
        case TextTokenizer::Whitespace:
        {
            std::string token = m_Tokenizer->token();
            if (token == " ")
            {
                m_LineBuilder->addSpace();
            }
            else
            {
                if (m_LineBuilder->addWhitespace(token) != 0)
                {
                    m_LineBuilder->addNewline();
                    lines++;
                }
            }
            break;
        }
        case TextTokenizer::Word:
        {
            if (addWord())
                lines++;
            break;
        }
        case TextTokenizer::ZeroWidthSpace:
            m_LineBuilder->addZeroWidthSpace();
            break;
        default:
            break;
        }
    }
    return lines;
}

bool TextFormatter::formatLine()
{
    return format(1) == 1;
}

void replaceNonBreakingSpaces(std::string& s)
{
    s = String::replace(s, 0xA0, ' ');
}

bool TextFormatter::addWord()
{
    std::string token = m_Tokenizer->token();
    replaceNonBreakingSpaces(token);
    size_t overflow = m_LineBuilder->addWord(token, true);
    if (overflow == 0)
        return false;

    if (overflow == 1)
    {
        TextTokenizer current = *m_Tokenizer;
        if (!m_Tokenizer->nextToken() ||
            m_Tokenizer->tokenType() != TextTokenizer::SoftHyphen)
        {
            m_LineBuilder->addWord(token, false);
            m_LineBuilder->addNewline();
            m_Tokenizer->resetCurrentToken();
            return true;
        }
        *m_Tokenizer = current;
    }

    if (m_LineBuilder->empty())
    {
        size_t splitPos = String::numberOfCharacters(token) - overflow;
        m_Tokenizer->splitToken(splitPos);
        m_LineBuilder->addWord(m_Tokenizer->token(), true);
        m_LineBuilder->addSoftHyphen();
        m_LineBuilder->addNewline();
        return true;
    }
    else
    {
        m_LineBuilder->addNewline();
        m_Tokenizer->resetCurrentToken();
        return true;
    }
}

}
