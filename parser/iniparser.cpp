#include "iniparser.h"

#include "split.h"
#include "trim.h"

void IniParser::clear() { m_data_.clear(); }

bool IniParser::parse(const std::string_view &sv) {
    using iniparser::utils::string::split;
    using iniparser::utils::string::trim;

    clear();
    std::string currentSection = "";
    m_data_.emplace(currentSection, ini_section_t{});

    auto lines = split(sv, '\n');
    for (auto line : lines) {
        auto trimmedLine = trim(line);
        bool ok = consumeLine(trimmedLine, currentSection);
        if (!ok) {
            clear();
            return false;
        }
    }

    return true;
}

std::optional<std::string> IniParser::get(const std::string &section,
                                          const std::string &key) {
    auto secItr = m_data_.find(section);
    if (secItr == m_data_.end()) {
        return std::nullopt;
    }

    auto keyItr = secItr->second.find(key);
    if (keyItr == secItr->second.end()) {
        return std::nullopt;
    }

    return keyItr->second;
}

bool IniParser::consumeLine(const std::string_view line,
                            std::string &currentSection) {
    using iniparser::utils::string::split;
    using iniparser::utils::string::trim;

    // Ignore empty lines
    if (line.empty()) {
        return true;
    }

    // Section
    if (line[0] == '[') {
        return consumeSection(line, currentSection);
    }

    // Key-value
    return consumeKeyValue(line, currentSection);
}

bool IniParser::consumeSection(const std::string_view line,
                               std::string &currentSection) {
    using iniparser::utils::string::split;
    using iniparser::utils::string::trim;

    size_t endPos = line.find(']', 1);
    if (endPos == std::string::npos) {
        return false;
    }

    currentSection = trim(line.substr(1, endPos - 1));
    m_data_.emplace(currentSection, ini_section_t{});
    return true;
}

bool IniParser::consumeKeyValue(const std::string_view line,
                                std::string &currentSection) {
    using iniparser::utils::string::split;
    using iniparser::utils::string::trim;

    auto splits = split(line, '=');
    if (splits.size() < 3) {
        return false;
    }

    auto key = trim(splits[0]);
    auto value = trim(splits[2]);
    if (key.empty() || value.empty()) {
        return false;
    }

    m_data_.at(currentSection).emplace(key, value);

    return true;
}