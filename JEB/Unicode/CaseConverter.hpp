#ifndef JEB_STRING_UNICODE_CASECONVERTER_HPP
#define JEB_STRING_UNICODE_CASECONVERTER_HPP

#include <functional>
#include "CharMap.hpp"

namespace JEB { namespace Unicode {

class CaseConverter : public std::unary_function<uint32_t, uint32_t>
{
public:
  CaseConverter(const CharMap& charMap);
  uint32_t operator()(uint32_t ch) const;
private:
  CharMap m_CharMap;
};

extern CaseConverter lower;
extern CaseConverter title;
extern CaseConverter upper;

}}

#endif
