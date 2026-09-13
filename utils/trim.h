#pragma once
#ifndef INIPARSER_UTILS_TRIM_H
#define INIPARSER_UTILS_TRIM_H

#include <string_view> // std::string_view

namespace iniparser::utils::string {

enum class TrimPolicy { Left, Right, Both };

std::string_view trim(const std::string_view sv,
                      const TrimPolicy policy = TrimPolicy::Both);

} // namespace iniparser::utils::string

#endif // INIPARSER_UTILS_TRIM_H