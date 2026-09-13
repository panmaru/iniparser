#pragma once
#ifndef INIPARSER_PARSER_INIPARSER_H
#define INIPARSER_PARSER_INIPARSER_H

#include <optional>      // std::optional
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

class IniParser {
public:
    void clear();
    bool parse(const std::string_view &sv);
    std::optional<std::string> get(const std::string &section,
                                   const std::string &key);

private:
    using ini_section_t = std::unordered_map<std::string, std::string>;

    bool consumeLine(const std::string_view line, std::string &currentSection);
    bool consumeSection(const std::string_view line,
                        std::string &currentSection);
    bool consumeKeyValue(const std::string_view line,
                         std::string &currentSection);

    std::unordered_map<std::string, // section name
                       ini_section_t>
        m_data_;
};

#endif // INIPARSER_PARSER_INIPARSER_H