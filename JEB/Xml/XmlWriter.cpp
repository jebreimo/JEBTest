#include "XmlWriter.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include "JEB/String/String.hpp"
#include "JEB/String/StringPredicates.hpp"

#define PRECONDITION(cond, msg) \
    if (!(cond)) \
        throw std::runtime_error(msg)

using namespace std;

namespace JEB {

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
}

XmlWriter::Formatting DefaultFormatting = XmlWriter::None;

XmlWriter::XmlWriter()
    : m_Formatting(DefaultFormatting),
      m_FormattingState(AfterIndentation),
      m_LinePos(0),
      m_PrevStreamPos(0),
      m_Stream(&cout)
{
    m_States.push(Text);
    m_PrevStreamPos = (size_t)cout.tellp();
}

XmlWriter::XmlWriter(std::ostream* stream)
    : m_Formatting(DefaultFormatting),
      m_FormattingState(AfterIndentation),
      m_LinePos(0),
      m_PrevStreamPos(0),
      m_Stream(stream)
{
    m_States.push(Text);
    if (stream)
        m_PrevStreamPos = (size_t)stream->tellp();
}

XmlWriter::~XmlWriter()
{
}

bool XmlWriter::open(const std::string& filename)
{
    m_StreamPtr.reset(new std::ofstream(filename));
    m_Stream = m_StreamPtr.get();
    reset();
    return !m_Stream->fail();
}

void XmlWriter::close()
{
    m_StreamPtr.reset();
    m_Stream = &cout;
    reset();
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

void XmlWriter::beginAttribute(const string& name)
{
    PRECONDITION(m_Stream, "stream is NULL");
    tagContext();
    writeAttributeSeparator();
    write(name);
    *m_Stream << "=\"";
    m_FormattingState = AfterText;
    m_States.push(AttributeValue);
}

void XmlWriter::endAttribute()
{
    PRECONDITION(m_States.top() == AttributeValue, "endAttribute not preceded by beginAttribute");
    m_Stream->put('"');
    m_States.pop();
    m_FormattingState = AfterText;
}

void XmlWriter::attributeValue(const string& value)
{
    PRECONDITION(m_States.top() == AttributeValue, "attribute value without name");
    writeAttributeText(value);
}

void XmlWriter::attributeValue(const std::wstring& value)
{
    attributeValue(String::toUtf8(value, String::Encoding::Utf16));
}

void XmlWriter::attributeValue(int value)
{
    PRECONDITION(m_States.top() == AttributeValue, "attribute value without name");
    *m_Stream << value;
}

void XmlWriter::attributeValue(long long value)
{
    PRECONDITION(m_States.top() == AttributeValue, "attribute value without name");
    *m_Stream << value;
}

void XmlWriter::attributeValue(double value)
{
    PRECONDITION(m_States.top() == AttributeValue, "attribute value without name");
    *m_Stream << value;
}

void XmlWriter::attributeValue(double value, int precision)
{
    PRECONDITION(m_States.top() == AttributeValue, "attribute value without name");
    std::streamsize prev = m_Stream->precision(precision);
    *m_Stream << value;
    m_Stream->precision(prev);
}

void XmlWriter::attribute(const std::string& name, const std::string& value)
{
    beginAttribute(name);
    attributeValue(value);
    endAttribute();
}

void XmlWriter::attribute(const std::string& name, const std::wstring& value)
{
    attribute(name, String::toUtf8(value, String::Encoding::Utf16));
}

void XmlWriter::attribute(const std::string& name, int value)
{
    beginAttribute(name);
    attributeValue(value);
    endAttribute();
}

void XmlWriter::attribute(const std::string& name, long long value)
{
    beginAttribute(name);
    attributeValue(value);
    endAttribute();
}

void XmlWriter::attribute(const std::string& name, double value)
{
    beginAttribute(name);
    attributeValue(value);
    endAttribute();
}

void XmlWriter::attribute(const std::string& name, double value, int precision)
{
    beginAttribute(name);
    attributeValue(value, precision);
    endAttribute();
}

void XmlWriter::beginElement(const string& name)
{
    textContext();
    if (m_Formatting & IndentElements)
        ensureNewline();
    *m_Stream << '<';
    write(name);
    m_Context.push(name);
    m_FormattingState = FirstAttribute;
    m_States.push(ElementTag);
}

void XmlWriter::endElement()
{
    PRECONDITION(!m_Context.empty(), "end element without matching start element");
    tagContext();
    if (m_States.top() == ElementTag)
    {
      if (m_FormattingState != FirstAttribute)
          m_Indentation.pop();
      *m_Stream << "/>";
    }
    else if (m_States.top() != SpecialTag)
    {
        if ((m_Formatting & IndentElements) != 0)
            m_Indentation.pop();
        if (m_States.top() == Text &&
            oneOf(m_FormattingState, AfterEndTag, StartOfLine) &&
            (m_Formatting & IndentElements) != 0)
            ensureNewline();
        *m_Stream << "</";
        write(m_Context.top());
        *m_Stream << ">";
    }
    else
    {
        throw std::runtime_error("end element in a special tag");
    }

    m_Context.pop();
    m_FormattingState = AfterEndTag;
    m_States.pop();
}

void XmlWriter::element(const std::string& name, const std::string& charData)
{
    beginElement(name);
    characterData(charData);
    endElement();
}

void XmlWriter::element(const std::string& name, const std::wstring& charData)
{
    element(name, String::toUtf8(charData, String::Encoding::Utf16));
}

void XmlWriter::element(const std::string& name, int value)
{
    beginElement(name);
    characterData(value);
    endElement();
}

void XmlWriter::element(const std::string& name, long long value)
{
    beginElement(name);
    characterData(value);
    endElement();
}

void XmlWriter::element(const std::string& name, double value)
{
    beginElement(name);
    characterData(value);
    endElement();
}

void XmlWriter::element(const std::string& name, double value, int precision)
{
    beginElement(name);
    characterData(value, precision);
    endElement();
}

void XmlWriter::characterData(const string& charData)
{
    textContext();
    writeElementText(charData);
    m_FormattingState = AfterText;
}

void XmlWriter::characterData(const std::wstring& charData)
{
    characterData(String::toUtf8(charData, String::Encoding::Utf16));
}

void XmlWriter::characterData(int value)
{
    textContext();
    *m_Stream << value;
    m_FormattingState = AfterText;
}

void XmlWriter::characterData(long long value)
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

void XmlWriter::rawCharacterData(const string& rawData)
{
    textContext();
}

void XmlWriter::beginSpecialTag(const string& start, const string& end)
{
    PRECONDITION(m_Stream, "stream is NULL");
    textContext();
    if ((m_Formatting & IndentElements) != 0 &&
        oneOf(m_FormattingState, StartOfLine, AfterBraces, AfterEndTag))
        ensureNewline();
    write(start);
    m_Context.push(end);
    if (String::isAlphaNumeric(String::chr(start, -1)))
    {
        m_FormattingState = FirstAttribute;
    }
    else
    {
        m_FormattingState = AfterIndentation;
        m_Indentation.pushAlignment(static_cast<unsigned>(linePos()));
    }
    m_States.push(SpecialTag);
}

void XmlWriter::endTag()
{
    tagContext();
    PRECONDITION(m_States.top() == ElementTag || m_States.top() == SpecialTag,
                 "endTag called outside a tag");
    switch (m_States.top())
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
        *m_Stream << m_Context.top();
        m_Context.pop();
        m_States.pop();
        m_FormattingState = AfterEndTag;
        break;
    default:
        throw std::runtime_error("endTag called when not inside a tag");
    }
}

void XmlWriter::rawText(const std::string& text)
{
    if (text.empty())
        return;

    m_FormattingState = AfterText;
    size_t startOfLine = text.find_last_of('\n');
    if (startOfLine != std::string::npos)
    {
        std::string::const_iterator beg = text.begin() + startOfLine + 1;
        m_LinePos = String::distance(beg, text.end());
        if (beg == text.end())
            m_FormattingState = StartOfLine;
    }
    else
    {
        m_LinePos += (size_t)m_Stream->tellp() - m_PrevStreamPos +
                     String::length(text);
    }
    m_Stream->write(text.data(), text.size());
    m_PrevStreamPos = (size_t)m_Stream->tellp();
}

void XmlWriter::beginComment()
{
    beginSpecialTag("<!--", "-->");
}

void XmlWriter::endComment()
{
    endTag();
}

void XmlWriter::comment(const std::string& str)
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

void XmlWriter::cdata(const std::string& str)
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
    m_PrevStreamPos = (size_t)m_Stream->tellp();
}

int XmlWriter::formatting() const
{
    return m_Formatting;
}

void XmlWriter::setFormatting(int formatting)
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

std::ostream* XmlWriter::stream() const
{
    return m_Stream;
}

void XmlWriter::setStream(std::ostream* stream)
{
    m_Stream = stream;
}

void XmlWriter::reset()
{
    m_FormattingState = AfterIndentation;
    m_LinePos = 0;
    m_PrevStreamPos = (size_t)m_Stream->tellp();
    while (!m_States.empty())
        m_States.pop();
    m_States.push(Text);
}

void XmlWriter::tagContext()
{
    if (m_States.top() == AttributeValue)
        endAttribute();
}

void XmlWriter::textContext()
{
    tagContext();
    if (m_States.top() == ElementTag)
    {
        if (m_FormattingState != FirstAttribute)
            m_Indentation.pop();
        *m_Stream << '>';
        if ((m_Formatting & IndentElements) != 0)
            m_Indentation.pushIndent();
        m_States.top() = Text;
        m_FormattingState = AfterBraces;
    }
    else if (m_States.top() == SpecialTag &&
             m_FormattingState == FirstAttribute)
    {
        m_Indentation.pushAlignment(static_cast<unsigned>(linePos()));
    }
}

void XmlWriter::writeAttributeSeparator()
{
    if (m_FormattingState == FirstAttribute)
    {
        *m_Stream << " ";
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
        *m_Stream << " ";
    }
}

size_t XmlWriter::linePos() const
{
    return m_LinePos + (size_t)m_Stream->tellp() - m_PrevStreamPos;
}

void XmlWriter::ensureNewline()
{
    if (m_FormattingState == StartOfLine)
    {
        m_Indentation.write(*m_Stream);
        m_PrevStreamPos = (size_t)m_Stream->tellp();
    }
    else if (m_FormattingState != AfterIndentation)
    {
        *m_Stream << "\n" << m_Indentation;
        m_LinePos = 0;
        m_PrevStreamPos = (size_t)m_Stream->tellp();
    }
}

void XmlWriter::writeAttributeText(const string& s)
{
    size_t start = 0;
    size_t end = s.find_first_of("<>\"&");
    while (end != string::npos)
    {
        write(s.begin() + start, s.begin() + end);
        switch (s[end])
        {
        case '<': *m_Stream << "&lt;"; break;
        case '>': *m_Stream << "&gt;"; break;
        case '"': *m_Stream << "&quot;"; break;
        case '&': *m_Stream << "&amp;"; break;
        }
        start = end + 1;
        end = s.find_first_of("<>\"&", start);
    }
    write(s.begin() + start, s.end());
}

void XmlWriter::writeElementText(const std::string& s)
{
    size_t start = 0;
    size_t end = s.find_first_of("<>&");
    while (end != string::npos)
    {
        write(s.begin() + start, s.begin() + end);
        switch (s[end])
        {
        case '<': *m_Stream << "&lt;"; break;
        case '>': *m_Stream << "&gt;"; break;
        case '&': *m_Stream << "&amp;"; break;
        }
        start = end + 1;
        end = s.find_first_of("<>&", start);
    }
    write(s.begin() + start, s.end());
}

void XmlWriter::write(const std::string& s)
{
    m_LinePos += (size_t)m_Stream->tellp() - m_PrevStreamPos +
                 String::length(s);
    m_Stream->write(s.data(), s.size());
    m_PrevStreamPos = (size_t)m_Stream->tellp();
}

void XmlWriter::write(std::string::const_iterator beg,
                      std::string::const_iterator end)
{
    m_LinePos += (size_t)m_Stream->tellp() - m_PrevStreamPos +
                 String::distance(beg, end);
    m_Stream->write(&*beg, end - beg);
    m_PrevStreamPos = (size_t)m_Stream->tellp();
}

}
