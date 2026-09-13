#pragma once
#ifndef INIPARSER_UTILS_SPLIT_H
#define INIPARSER_UTILS_SPLIT_H

#include <string_view> // std::string_view
#include <vector>      // std::vector

namespace iniparser::utils::string {

std::vector<std::string_view> split(const std::string_view sv,
                                    const char delim);

} // namespace iniparser::utils::string

#endif // INIPARSER_UTILS_SPLIT_H