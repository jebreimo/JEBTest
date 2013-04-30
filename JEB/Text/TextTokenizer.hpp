//****************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//****************************************************************************
#ifndef JEB_TEXTTOKENIZER_HPP
#define JEB_TEXTTOKENIZER_HPP

#include <cstdint>
#include <string>
#include "JEB/JEBDefinitions.hpp"

/** @file
  * @brief Defines the TextTokenizer class.
  */

namespace JEB
{

/** @brief Divides a text into tokens and iterate over them.
  *
  * Used by TextFormatter.
  *
  * To simplify text fomatting, the character '&' receives special treatment:
  *     @arg &<space> non-breaking space (0xA0)
  *     @arg &-       soft-hyphen (0xAD)
  *     @arg &_       zero-width space (0x200B)
  *     @arg &&       literal &
  *     @arg &<char>  & in front of any other character ignores the '&' and
  *         only @a char is printed.
  */
class TextTokenizer
{
public:
    enum TokenType
    {
        Undefined,
        Control,
        Newline,
        SoftHyphen,
        Whitespace,
        Word,
        ZeroWidthSpace
    };

    TextTokenizer();
    TextTokenizer(const std::string* text);

    bool endOfText() const;

    const std::string* text() const;
    void setText(const std::string* text);

    TokenType tokenType() const;

    bool nextToken();

    void resetCurrentToken();

    /** @brief Split the current token at character @a index.
      *
      * The string returned by the next call to token() will be all
      * characters before @a index in the current token, nextToken() will
      * then make the remainder (i.e. the token starting at @a index) become
      * the current token.
      *
      * @note Unicode code points that are "combining marks" are not
      *     considered separate characters and don't have any index of
      *     their own; instead they part of the preceding code point that
      *     isn't a combining mark.
      *
      * @return @a true unless index is greater than or equal to the number
      *     of characters in the current token.
      */
    bool splitToken(size_t index);

    /** @brief Returns the current token.
      */
    const std::string& token() const;
private:
    void endOfWhitespace();
    void endOfWord();
    uint32_t nextCharacter();
    uint32_t peekNextCharacter() const;

    const std::string* m_Text;
    std::string::const_iterator m_It;
    TokenType m_TokenType;
    std::string m_Token;
    std::string::const_iterator m_NextToken;
};

}

#endif
