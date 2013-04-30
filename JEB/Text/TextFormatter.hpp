//****************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//****************************************************************************
#ifndef JEB_TEXTFORMATTER_HPP
#define JEB_TEXTFORMATTER_HPP

#include <iosfwd>
#include <limits>
#include <memory>
#include <string>
#include "LineEndMode.hpp"

/** @file
  * @brief Defines the TextFormatter class.
  */

namespace JEB
{

namespace internal
{
class LineBuilder;
}
class TextTokenizer;

/** @brief Formats and writes a text as balanced lines.
  */
class TextFormatter
{
public:
    TextFormatter();
    TextFormatter(std::ostream* destination, const std::string* text);
    ~TextFormatter();

    std::ostream* destination() const;
    void setDestination(std::ostream* destination);

    bool endOfText() const;

    LineEndMode::Enum lineEndMode() const;
    void setLineEndMode(LineEndMode::Enum lineEndMode);

    size_t textWidth() const;
    void setTextWidth(size_t textWidth);

    const std::string* text() const;
    void setText(const std::string* text);

    size_t format(size_t maxLines = std::numeric_limits<size_t>::max());
    bool formatLine();

private:
    bool addWord();

    std::auto_ptr<internal::LineBuilder> m_LineBuilder;
    std::auto_ptr<TextTokenizer> m_Tokenizer;
    LineEndMode::Enum m_LineEndMode;
};

}

#endif
