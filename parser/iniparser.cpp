#include "iniparser.h"

#include <cassert> // assert

#include "split.h"
#include "trim.h"

namespace {

bool isSection(std::string_view line) {
    if (line.empty()) {
        return false;
    }

    return line[0] == '[' && line.back() == ']';
}

bool isQuoted(std::string_view line) {
    using iniparser::utils::string::trim;

    line = trim(line);
    if (line.empty()) {
        return false;
    }

    if (line[0] == '"' && line.back() == '"') {
        return true;
    }

    if (line[0] == '\'' && line.back() == '\'') {
        return true;
    }

    return false;
}

std::string unescape(std::string_view line) {
    std::string result;
    result.reserve(line.size());

    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == '\\') {
            char nextChar = line[++i];
            switch (nextChar) {
            case 'n':
                result.push_back('\n');
                break;
            case 'r':
                result.push_back('\r');
                break;
            case 't':
                result.push_back('\t');
                break;
            case '\\':
                result.push_back('\\');
                break;
            case '"':
                result.push_back('"');
                break;
            case '\'':
                result.push_back('\'');
                break;
            default:
                result.push_back(nextChar);
                break;
            }
        } else {
            result.push_back(line[i]);
        }
    }
    return result;
}

} // namespace

void IniParser::clear() { m_data_.clear(); }

bool IniParser::parse(const std::string_view &sv) {
    using iniparser::utils::string::split;

    clear();
    std::string currentSection = "";
    m_data_.emplace(currentSection, ini_section_t{});

    auto lines = split(sv, '\n');
    for (auto line : lines) {
        bool ok = consumeLine(line, currentSection);
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

bool IniParser::has(const std::string &section, const std::string &key) {
    auto secItr = m_data_.find(section);
    if (secItr == m_data_.end()) {
        return false;
    }

    auto keyItr = secItr->second.find(key);
    if (keyItr == secItr->second.end()) {
        return false;
    }

    return true;
}

std::unordered_map<std::string, IniParser::ini_section_t> IniParser::data() {
    return m_data_;
}

bool IniParser::consumeLine(std::string_view line,
                            std::string &currentSection) {
    using iniparser::utils::string::trim;
    using iniparser::utils::string::trimComment;

    // Remove comments
    line = trimComment(line);

    // Remove whitespace
    line = trim(line);

    // Ignore empty lines
    if (line.empty()) {
        return true;
    }

    // Section
    if (isSection(line)) {
        return consumeSection(line, currentSection);
    }

    // Key-value
    return consumeKeyValue(line, currentSection);
}

bool IniParser::consumeSection(std::string_view line,
                               std::string &currentSection) {
    using iniparser::utils::string::trim;

    assert(line.size() > 2);

    currentSection = trim(line.substr(1, line.size() - 2));
    m_data_.emplace(currentSection, ini_section_t{});
    return true;
}

bool IniParser::consumeKeyValue(std::string_view line,
                                std::string &currentSection) {
    using iniparser::utils::string::splitKeyValue;
    using iniparser::utils::string::trimQuote;

    auto [key, value] = splitKeyValue(line);
    if (key.empty()) {
        return false;
    }

    if (isQuoted(value)) {
        value = trimQuote(value);
        std::string unescapedValue = unescape(value);
        m_data_.at(currentSection).emplace(key, unescapedValue);
    } else {
        m_data_.at(currentSection).emplace(key, value);
    }

    return true;
}