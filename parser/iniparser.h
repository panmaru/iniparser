#pragma once
#ifndef INIPARSER_PARSER_INIPARSER_H
#define INIPARSER_PARSER_INIPARSER_H

#include <optional>      // std::optional
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

class IniParser {
public:
    using ini_section_t = std::unordered_map<std::string, std::string>;

    void clear();
    bool parse(const std::string_view &sv);
    std::optional<std::string> get(const std::string &section,
                                   const std::string &key);
    std::unordered_map<std::string, ini_section_t> data();

private:
    bool consumeLine(std::string_view line, std::string &currentSection);
    bool consumeSection(std::string_view line, std::string &currentSection);
    bool consumeKeyValue(std::string_view line, std::string &currentSection);

    std::unordered_map<std::string, // section name
                       ini_section_t>
        m_data_;
};

#endif // INIPARSER_PARSER_INIPARSER_H