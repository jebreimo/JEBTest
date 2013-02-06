#include "CaseConverter.hpp"
#include "StandardLowerCase.hpp"
#include "StandardTitleCase.hpp"
#include "StandardUpperCase.hpp"

namespace JEB { namespace Unicode {

CaseConverter::CaseConverter(const CharMap& charMap)
    : m_CharMap(charMap)
{}

uint32_t CaseConverter::operator()(uint32_t ch) const
{
    return m_CharMap.get(ch);
}

CaseConverter lower(CharMap(CompactLowerCaseMappings, LowerCaseMappings));
CaseConverter title(CharMap(CompactTitleCaseMappings, TitleCaseMappings));
CaseConverter upper(CharMap(CompactUpperCaseMappings, UpperCaseMappings));

}}
