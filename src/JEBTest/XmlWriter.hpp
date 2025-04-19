//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-16.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include "Indentation.hpp"

/** @file Defines the class XmlWriter.
  */

namespace JEBTest
{
    /** @brief XmlWriter writes UTF-8 encoded formatted XML to an instance
      *  of std::ostream.
      */
    class XmlWriter
    {
    public:
        enum Formatting
        {
            None = 0,
            IndentElements = 1,
            AlignTagText = 2,
        };

        /** @brief Construct an XmlWriter that writes to std::cout.
          */
        XmlWriter();

        /** @brief Construct an XmlWriter that writes to @a stream.
          *
          *  @a stream should remain valid during the entire life-time of the
          *  constructed instance, unless setStream is used to select
          *  a different stream.
          */
        explicit XmlWriter(std::ostream& stream);

        XmlWriter(XmlWriter&& rhs) noexcept;

        ~XmlWriter();

        XmlWriter& operator=(XmlWriter&& rhs) noexcept;

        /** @brief Write the XML declaration tag.
          *
          *  The encoding is always utf-8.
          *  @param standalone the standalone attribute.
          *  @param version the version attribute.
          */
        void xmlDeclaration(bool standalone = true,
                            const std::string& version = "1.0");

        void beginAttribute(std::string_view name);
        void endAttribute();

        void attributeValue(std::string_view value);
        void attributeValue(int32_t value);
        void attributeValue(int64_t value);
        void attributeValue(double value);
        void attributeValue(double value, int precision);

        void attribute(std::string_view name, std::string_view value);
        void attribute(std::string_view name, int32_t value);
        void attribute(std::string_view name, int64_t value);
        void attribute(std::string_view name, double value);
        void attribute(std::string_view name, double value, int precision);

        void beginElement(std::string name);
        void endElement();

        void element(std::string name, std::string_view charData);
        void element(std::string name, int32_t value);
        void element(std::string name, int64_t value);
        void element(std::string name, double value);
        void element(std::string name, double value, int precision);

        void endTag();

        void characterData(std::string_view charData);
        void characterData(int32_t value);
        void characterData(int64_t value);
        void characterData(double value);
        void characterData(double value, int precision);

        void rawCharacterData(std::string_view rawData);

        void beginSpecialTag(std::string_view start,
                             std::string end);

        void rawText(std::string_view text);

        void beginComment();
        void endComment();
        void comment(std::string_view str);

        void beginCData();
        void endCData();
        void cdata(std::string_view str);

        void indentLine();
        void newline(bool indent = true);

        [[nodiscard]] unsigned formatting() const;
        void setFormatting(unsigned formatting);

        [[nodiscard]] const std::string& indentation() const;
        void setIndentation(const std::string& indentation);

        [[nodiscard]] bool hasStream() const;
        [[nodiscard]] std::ostream& stream() const;
        void setStream(std::ostream& stream);
    private:
        void reset();
        void tagContext();
        void textContext();
        [[nodiscard]] size_t linePos() const;
        void ensureNewline();
        void writeAttributeSeparator();
        void writeAttributeText(std::string_view s);
        void writeElementText(std::string_view s);
        void write(std::string_view s);

        enum State
        {
            AttributeValue,
            ElementTag,
            SpecialTag,
            Text
        };

        enum FormattingState
        {
            StartOfLine,
            AfterIndentation,
            AfterBraces,
            AfterEndTag,
            FirstAttribute,
            AfterText
        };

        std::vector<std::string> m_Context;
        unsigned m_Formatting;
        FormattingState m_FormattingState;
        Indentation m_Indentation;
        size_t m_LinePos;
        size_t m_PrevStreamPos;
        std::vector<State> m_States;
        std::ostream* m_Stream;
    };
}
