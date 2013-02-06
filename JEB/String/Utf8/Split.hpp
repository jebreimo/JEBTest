//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#ifndef JEB_STRING_SPLIT_HPP
#define JEB_STRING_SPLIT_HPP

#include <cstdint>
#include <limits>
#include <string>
#include <vector>
#include "JEB/String/StringFlags.hpp"

/** @file
  * @brief Defines functions for splitting strings
  */

namespace JEB { namespace String { namespace Utf8 {

template <typename StringCollection>
void split(StringCollection& dst,
           const std::string& str,
           size_t maxSplits = 0,
           SplitFlags::Flags flags = SplitFlags::IgnoreEmpty);

template <typename StringCollection>
void split(StringCollection& dst,
           const std::string& str,
           const std::string& sep,
           size_t maxSplits = 0,
           SplitFlags::Flags flags = SplitFlags::Defaults);

template <typename StringCollection, typename Finder>
void splitWithFinder(StringCollection& dst,
                     const std::string& str,
                     Finder finder,
                     size_t maxSplits = 0,
                     bool ignoreEmpty = false);

template <typename StringCollection, typename FwdIt, typename Finder>
void splitWithFinder(StringCollection& dst,
                     FwdIt begin, FwdIt end,
                     Finder finder,
                     size_t maxSplits = 0,
                     bool ignoreEmpty = false);

template <typename Finder>
std::pair<std::string, std::string> splitPairWithFinder(
        const std::string& str,
        Finder finder);

template <typename FwdIt, typename Finder>
std::pair<std::string, std::string> splitPairWithFinder(
        FwdIt begin, FwdIt end,
        Finder finder);

}}}

#include "Split_Impl.hpp"

#endif
