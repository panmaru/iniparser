#pragma once
#ifndef INIPARSER_UTILS_SPLIT_H
#define INIPARSER_UTILS_SPLIT_H

#include <string> // std::string
#include <vector> // std::vector

namespace iniparser::utils::string {

std::vector<std::string> split(const std::string &str, const char delim);

} // namespace iniparser::utils::string

#endif // INIPARSER_UTILS_SPLIT_H