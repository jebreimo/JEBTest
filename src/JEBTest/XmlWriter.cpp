//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-16.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "XmlWriter.hpp"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Ystring/Algorithms.hpp"
#include "Ystring/CodepointPredicates.hpp"

#define PRECONDITION(cond, msg) \
    if (!(cond)) \
        throw std::logic_error(msg)

namespace JEBTest
{
    using namespace std;

    namespace
    {
        template <typename T>
        bool oneOf(T value, T cand1, T cand2)
        {
            return value == cand1 || value == cand2;
        }

        template <typename T>
        bool oneOf(T value, T cand1, T cand2, T cand3)
        {
            return oneOf(value, cand1, cand2) || value == cand3;
        }

        bool isBadAttributeTextCharacter(char c)
        {
            return static_cast<unsigned char>(c) < 32 ||
                   c == '<' || c == '>' || c == '"' || c == '&';
        }

        bool isBadElementTextCharacter(char c)
        {
            return (static_cast<unsigned char>(c) < 32 && c != '\t' && c != '\n' &&
                    c != '\r') ||
                   c == '<' || c == '>' || c == '&';
        }

        void writeControlChar(std::ostream& os, char c)
        {
            assert(static_cast<unsigned char>(c) < 32);
            if (static_cast<unsigned char>(c) < 10)
            {
                char buf[5] = "&#_;";
                buf[2] = static_cast<char>('0' + c);
                os.write(buf, 4);
            }
            else
            {
                char buf[6] = "&#__;";
                buf[2] = static_cast<char>('0' + (c / 10));
                buf[3] = static_cast<char>('0' + (c % 10));
                os.write(buf, 5);
            }
        }
    }

    XmlWriter::Formatting DefaultFormatting = XmlWriter::None;

    XmlWriter::XmlWriter()
        : m_Formatting(DefaultFormatting),
          m_FormattingState(AfterIndentation),
          m_LinePos(0),
          m_PrevStreamPos(0),
          m_Stream(&cout)
    {
        m_States.push_back(Text);
        m_PrevStreamPos = static_cast<size_t>(cout.tellp());
    }

    XmlWriter::XmlWriter(std::ostream& stream)
        : m_Formatting(DefaultFormatting),
          m_FormattingState(AfterIndentation),
          m_LinePos(0),
          m_PrevStreamPos(0),
          m_Stream(&stream)
    {
        m_States.push_back(Text);
        if (stream)
            m_PrevStreamPos = static_cast<size_t>(stream.tellp());
    }

    XmlWriter::XmlWriter(XmlWriter&& rhs) noexcept
        : m_Context(std::move(rhs.m_Context)),
          m_Formatting(rhs.m_Formatting),
          m_FormattingState(rhs.m_FormattingState),
          m_Indentation(std::move(rhs.m_Indentation)),
          m_LinePos(rhs.m_LinePos),
          m_PrevStreamPos(rhs.m_PrevStreamPos),
          m_States(std::move(rhs.m_States)),
          m_Stream(rhs.m_Stream)
    {
        rhs.m_Stream = nullptr;
    }

    XmlWriter::~XmlWriter() = default;

    XmlWriter& XmlWriter::operator=(XmlWriter&& rhs) noexcept
    {
        m_Formatting = rhs.m_Formatting;
        m_FormattingState = rhs.m_FormattingState;
        m_LinePos = rhs.m_LinePos;
        m_PrevStreamPos = rhs.m_PrevStreamPos;
        m_Indentation = std::move(rhs.m_Indentation);

        m_Stream = rhs.m_Stream;
        rhs.m_Stream = nullptr;

        m_States = std::move(rhs.m_States);
        m_Context = std::move(rhs.m_Context);

        return *this;
    }

    void XmlWriter::xmlDeclaration(bool standalone,
                                   const std::string& version)
    {
        beginSpecialTag("<?xml", "?>");
        attribute("version", version);
        attribute("encoding", "utf-8");
        attribute("standalone", standalone ? "yes" : "no");
        endTag();
    }

    void XmlWriter::beginAttribute(std::string_view name)
    {
        PRECONDITION(m_Stream, "stream is nullptr");
        tagContext();
        writeAttributeSeparator();
        write(name);
        m_Stream->write("=\"", 2);
        m_FormattingState = AfterText;
        m_States.push_back(AttributeValue);
    }

    void XmlWriter::endAttribute()
    {
        PRECONDITION(m_States.back() == AttributeValue,
                     "endAttribute not preceded by beginAttribute");
        m_Stream->put('"');
        m_States.pop_back();
        m_FormattingState = AfterText;
    }

    void XmlWriter::attributeValue(std::string_view value)
    {
        PRECONDITION(m_States.back() == AttributeValue,
                     "attribute value without name");
        writeAttributeText(value);
    }

    void XmlWriter::attributeValue(int32_t value)
    {
        PRECONDITION(m_States.back() == AttributeValue,
                     "attribute value without name");
        *m_Stream << value;
    }

    void XmlWriter::attributeValue(int64_t value)
    {
        PRECONDITION(m_States.back() == AttributeValue,
                     "attribute value without name");
        *m_Stream << value;
    }

    void XmlWriter::attributeValue(double value)
    {
        PRECONDITION(m_States.back() == AttributeValue,
                     "attribute value without name");
        *m_Stream << value;
    }

    void XmlWriter::attributeValue(double value, int precision)
    {
        PRECONDITION(m_States.back() == AttributeValue,
                     "attribute value without name");
        std::streamsize prev = m_Stream->precision(precision);
        *m_Stream << value;
        m_Stream->precision(prev);
    }

    void XmlWriter::attribute(std::string_view name,
                              std::string_view value)
    {
        beginAttribute(name);
        attributeValue(value);
        endAttribute();
    }

    void XmlWriter::attribute(std::string_view name, int32_t value)
    {
        beginAttribute(name);
        attributeValue(value);
        endAttribute();
    }

    void XmlWriter::attribute(std::string_view name, int64_t value)
    {
        beginAttribute(name);
        attributeValue(value);
        endAttribute();
    }

    void XmlWriter::attribute(std::string_view name, double value)
    {
        beginAttribute(name);
        attributeValue(value);
        endAttribute();
    }

    void XmlWriter::attribute(std::string_view name,
                              double value, int precision)
    {
        beginAttribute(name);
        attributeValue(value, precision);
        endAttribute();
    }

    void XmlWriter::beginElement(std::string name)
    {
        textContext();
        if (m_Formatting & IndentElements)
            ensureNewline();
        *m_Stream << '<';
        write(name);
        m_Context.push_back(std::move(name));
        m_FormattingState = FirstAttribute;
        m_States.push_back(ElementTag);
    }

    void XmlWriter::endElement()
    {
        PRECONDITION(!m_Context.empty(),
                     "end element without matching start element");
        tagContext();
        if (m_States.back() == ElementTag)
        {
            if (m_FormattingState != FirstAttribute)
                m_Indentation.pop();
            m_Stream->write("/>", 2);
        }
        else if (m_States.back() != SpecialTag)
        {
            if ((m_Formatting & IndentElements) != 0)
                m_Indentation.pop();
            if (m_States.back() == Text &&
                oneOf(m_FormattingState, AfterEndTag, StartOfLine) &&
                (m_Formatting & IndentElements) != 0)
                ensureNewline();
            m_Stream->write("</", 2);
            write(m_Context.back());
            *m_Stream << '>';
        }
        else
        {
            throw std::runtime_error("end element in a special tag");
        }

        m_Context.pop_back();
        m_FormattingState = AfterEndTag;
        m_States.pop_back();
    }

    void XmlWriter::element(std::string name,
                            std::string_view charData)
    {
        beginElement(std::move(name));
        characterData(charData);
        endElement();
    }

    void XmlWriter::element(std::string name, int32_t value)
    {
        beginElement(std::move(name));
        characterData(value);
        endElement();
    }

    void XmlWriter::element(std::string name, int64_t value)
    {
        beginElement(std::move(name));
        characterData(value);
        endElement();
    }

    void XmlWriter::element(std::string name, double value)
    {
        beginElement(std::move(name));
        characterData(value);
        endElement();
    }

    void XmlWriter::element(std::string name,
                            double value, int precision)
    {
        beginElement(std::move(name));
        characterData(value, precision);
        endElement();
    }

    void XmlWriter::characterData(std::string_view charData)
    {
        textContext();
        writeElementText(charData);
        m_FormattingState = AfterText;
    }

    void XmlWriter::characterData(int32_t value)
    {
        textContext();
        *m_Stream << value;
        m_FormattingState = AfterText;
    }

    void XmlWriter::characterData(int64_t value)
    {
        textContext();
        *m_Stream << value;
        m_FormattingState = AfterText;
    }

    void XmlWriter::characterData(double value)
    {
        textContext();
        *m_Stream << value;
        m_FormattingState = AfterText;
    }

    void XmlWriter::characterData(double value, int precision)
    {
        textContext();
        std::streamsize prev = m_Stream->precision(precision);
        *m_Stream << value;
        m_Stream->precision(prev);
        m_FormattingState = AfterText;
    }

    void XmlWriter::rawCharacterData(std::string_view rawData)
    {
        textContext();
    }

    void XmlWriter::beginSpecialTag(std::string_view start, std::string end)
    {
        PRECONDITION(m_Stream, "stream is nullptr");
        textContext();
        if ((m_Formatting & IndentElements) != 0 &&
            oneOf(m_FormattingState, StartOfLine, AfterBraces, AfterEndTag))
            ensureNewline();
        write(start);
        m_Context.push_back(std::move(end));

        if (ystring::is_alpha_numeric(ystring::get_codepoint(start, -1).second))
        {
            m_FormattingState = FirstAttribute;
        }
        else
        {
            m_FormattingState = AfterIndentation;
            m_Indentation.pushAlignment(static_cast<unsigned>(linePos()));
        }
        m_States.push_back(SpecialTag);
    }

    void XmlWriter::endTag()
    {
        tagContext();
        PRECONDITION(m_States.back() == ElementTag ||
                     m_States.back() == SpecialTag,
                     "endTag called outside a tag");
        switch (m_States.back())
        {
        case ElementTag:
            textContext();
            break;
        case SpecialTag:
            if (m_FormattingState != FirstAttribute)
                m_Indentation.pop();
            if (m_FormattingState == StartOfLine)
                ensureNewline();
            else if (m_FormattingState == AfterText)
                m_Stream->put(' ');
            *m_Stream << m_Context.back();
            m_Context.pop_back();
            m_States.pop_back();
            m_FormattingState = AfterEndTag;
            break;
        default:
            throw std::runtime_error("endTag called when not inside a tag");
        }
    }

    void XmlWriter::rawText(std::string_view text)
    {
        if (text.empty())
            return;

        m_FormattingState = AfterText;
        size_t startOfLine = text.find_last_of('\n');
        if (startOfLine != std::string::npos)
        {
            auto lastLine = text.substr(startOfLine + 1);
            m_LinePos = ystring::count_chars(lastLine);
            if (lastLine.empty())
                m_FormattingState = StartOfLine;
        }
        else
        {
            m_LinePos += static_cast<size_t>(m_Stream->tellp()) - m_PrevStreamPos +
                ystring::count_chars(text);
        }
        m_Stream->write(text.data(), static_cast<std::streamsize>(text.size()));
        m_PrevStreamPos = static_cast<size_t>(m_Stream->tellp());
    }

    void XmlWriter::beginComment()
    {
        beginSpecialTag("<!--", "-->");
    }

    void XmlWriter::endComment()
    {
        endTag();
    }

    void XmlWriter::comment(std::string_view str)
    {
        beginComment();
        rawText(str);
        endComment();
    }

    void XmlWriter::beginCData()
    {
        beginSpecialTag("<![CDATA[", "]]>");
    }

    void XmlWriter::endCData()
    {
        endTag();
    }

    void XmlWriter::cdata(std::string_view str)
    {
        beginCData();
        rawText(str);
        endCData();
    }

    void XmlWriter::indentLine()
    {
        if (m_FormattingState == StartOfLine)
        {
            m_Indentation.write(*m_Stream);
            m_FormattingState = AfterIndentation;
        }
    }

    void XmlWriter::newline(bool indent)
    {
        if (m_FormattingState == FirstAttribute)
            m_Indentation.pushIndent();
        m_Stream->put('\n');
        m_FormattingState = StartOfLine;
        if (indent)
            indentLine();
        m_LinePos = 0;
        m_PrevStreamPos = static_cast<size_t>(m_Stream->tellp());
    }

    unsigned XmlWriter::formatting() const
    {
        return m_Formatting;
    }

    void XmlWriter::setFormatting(unsigned formatting)
    {
        m_Formatting = formatting;
    }

    const string& XmlWriter::indentation() const
    {
        return m_Indentation.indentationString();
    }

    void XmlWriter::setIndentation(const string& indentation)
    {
        m_Indentation.setIndentationString(indentation);
    }

    bool XmlWriter::hasStream() const
    {
        return m_Stream != nullptr;
    }

    std::ostream& XmlWriter::stream() const
    {
        if (!m_Stream)
            throw std::runtime_error(
                "Attempt to access stream member before it's been assigned.");
        return *m_Stream;
    }

    void XmlWriter::setStream(std::ostream& stream)
    {
        m_Stream = &stream;
    }

    void XmlWriter::reset()
    {
        m_FormattingState = AfterIndentation;
        m_LinePos = 0;
        m_PrevStreamPos = static_cast<size_t>(m_Stream->tellp());
        m_States.clear();
        m_Context.clear();
        m_States.push_back(Text);
    }

    void XmlWriter::tagContext()
    {
        if (m_States.back() == AttributeValue)
            endAttribute();
    }

    void XmlWriter::textContext()
    {
        tagContext();
        if (m_States.back() == ElementTag)
        {
            if (m_FormattingState != FirstAttribute)
                m_Indentation.pop();
            *m_Stream << '>';
            if ((m_Formatting & IndentElements) != 0)
                m_Indentation.pushIndent();
            m_States.back() = Text;
            m_FormattingState = AfterBraces;
        }
        else if (m_States.back() == SpecialTag &&
                 m_FormattingState == FirstAttribute)
        {
            m_Indentation.pushAlignment(static_cast<unsigned>(linePos()));
        }
    }

    void XmlWriter::writeAttributeSeparator()
    {
        if (m_FormattingState == FirstAttribute)
        {
            *m_Stream << ' ';
            m_Indentation.pushAlignment(static_cast<unsigned>(linePos()));
        }
        else if (m_FormattingState == AfterBraces)
        {
            m_Indentation.pushAlignment(static_cast<unsigned>(linePos()));
        }
        else if ((m_Formatting & AlignTagText) != 0)
        {
            ensureNewline();
        }
        else
        {
            *m_Stream << ' ';
        }
    }

    size_t XmlWriter::linePos() const
    {
        return m_LinePos + static_cast<size_t>(m_Stream->tellp()) - m_PrevStreamPos;
    }

    void XmlWriter::ensureNewline()
    {
        if (m_FormattingState == StartOfLine)
        {
            m_Indentation.write(*m_Stream);
            m_PrevStreamPos = static_cast<size_t>(m_Stream->tellp());
        }
        else if (m_FormattingState != AfterIndentation)
        {
            *m_Stream << '\n' << m_Indentation;
            m_LinePos = 0;
            m_PrevStreamPos = static_cast<size_t>(m_Stream->tellp());
        }
    }

    void XmlWriter::writeAttributeText(string_view s)
    {
        auto last = find_if(begin(s), end(s), isBadAttributeTextCharacter);
        while (last != end(s))
        {
            auto pos = std::distance(begin(s), last);
            write(s.substr(0, pos));
            if (static_cast<unsigned char>(*last) < 32)
            {
                writeControlChar(*m_Stream, *last);
            }
            else
            {
                switch (*last)
                {
                case '<': m_Stream->write("&lt;", 4);
                    break;
                case '>': m_Stream->write("&gt;", 4);
                    break;
                case '"': m_Stream->write("&quot;", 6);
                    break;
                case '&': m_Stream->write("&amp;", 5);
                    break;
                }
            }
            s = s.substr(pos + 1);
            last = find_if(begin(s), end(s), isBadAttributeTextCharacter);
        }
        write(s);
    }

    void XmlWriter::writeElementText(std::string_view s)
    {
        auto last = find_if(begin(s), end(s), isBadElementTextCharacter);
        while (last != end(s))
        {
            auto pos = std::distance(begin(s), last);
            write(s.substr(0, pos));
            if (static_cast<unsigned char>(*last) < 32)
            {
                writeControlChar(*m_Stream, *last);
            }
            else
            {
                switch (*last)
                {
                case '<': m_Stream->write("&lt;", 4);
                    break;
                case '>': m_Stream->write("&gt;", 4);
                    break;
                case '&': m_Stream->write("&amp;", 5);
                    break;
                }
            }
            s = s.substr(pos + 1);
            last = find_if(begin(s), end(s), isBadAttributeTextCharacter);
        }
        write(s);
    }

    void XmlWriter::write(std::string_view s)
    {
        m_LinePos += static_cast<size_t>(m_Stream->tellp())
            - m_PrevStreamPos
            + ystring::count_chars(s);
        m_Stream->write(s.data(), s.size());
        m_PrevStreamPos = static_cast<size_t>(m_Stream->tellp());
    }
}
