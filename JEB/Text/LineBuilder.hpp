#ifndef LINEBUILDER_HPP
#define LINEBUILDER_HPP

#include <iosfwd>
#include <string>
#include "LineEndMode.hpp"

/** @file
  * @brief Defines the LineBuilder class.
  */

namespace JEB
{
namespace internal
{

/** @brief Used by TextFormatter to format text with balanced lines.
  */
class LineBuilder
{
public:
    LineBuilder();
    LineBuilder(std::ostream* destination);

    std::ostream* destination() const;
    void setDestination(std::ostream* destination);

    bool empty() const;

    LineEndMode::Enum lineEndMode() const;
    void setLineEndMode(LineEndMode::Enum lineEndMode);

    size_t maxTextWidth() const;
    /** @brief Set the maximum line length.
      *
      * The length can not be less than 2 (a single letter plus a hyphen),
      * and newline characters are assumed to have no length.
      */
    void setMaxTextWidth(size_t maxTextWidth);

    void addNewline();
    void addSoftHyphen();
    void addSpace();
    size_t addWhitespace(const std::string& whitespace);
    size_t addWord(const std::string& word, bool leaveSpaceForHyphen);
    void addZeroWidthSpace();
private:
    std::ostream* m_Destination;
    LineEndMode::Enum m_LineEndMode;
    size_t m_TextWidth;
    size_t m_MaxTextWidth;
    int m_State;
};

}
}

#endif // LINEBUILDER_HPP
