#include "iniparser.h"

#include "split.h"
#include "trim.h"

namespace {

size_t getCommentPos(const std::string_view line) {
    bool inDoubleQuote = false;
    bool inSingleQuote = false;
    size_t commentPos = std::string_view::npos;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '"' && !inSingleQuote) {
            bool escaped = i > 0 && line[i - 1] == '\\';
            if (!escaped) {
                inDoubleQuote = !inDoubleQuote;
            }
        } else if (line[i] == '\'' && !inDoubleQuote) {
            bool escaped = i > 0 && line[i - 1] == '\\';
            if (!escaped) {
                inSingleQuote = !inSingleQuote;
            }
        } else if (line[i] == ';' || line[i] == '#') {
            if (!inDoubleQuote && !inSingleQuote) {
                commentPos = i;
                break;
            }
        }
    }
    return commentPos;
}

std::string_view trimComment(std::string_view line) {
    size_t commentPos = getCommentPos(line);
    if (commentPos != std::string_view::npos) {
        return line.substr(0, commentPos);
    }
    return line;
}

std::string_view trimQuote(std::string_view line) {
    if (line.empty()) {
        return line;
    }

    if (line[0] == '"' && line.back() == '"') {
        return line.substr(1, line.size() - 2);
    }

    if (line[0] == '\'' && line.back() == '\'') {
        return line.substr(1, line.size() - 2);
    }

    return line;
}

bool isComment(std::string_view line) {
    if (line.empty()) {
        return false;
    }

    return line[0] == ';' || line[0] == '#';
}

bool isSection(std::string_view line) {
    if (line.empty()) {
        return false;
    }

    return line[0] == '[';
}

} // namespace

void IniParser::clear() { m_data_.clear(); }

bool IniParser::parse(const std::string_view &sv) {
    using iniparser::utils::string::split;
    using iniparser::utils::string::trim;

    clear();
    std::string currentSection = "";
    m_data_.emplace(currentSection, ini_section_t{});

    auto lines = split(sv, '\n');
    for (auto line : lines) {
        auto trimmedLine = trimComment(trim(line));
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

bool IniParser::consumeLine(std::string_view line,
                            std::string &currentSection) {
    using iniparser::utils::string::split;
    using iniparser::utils::string::trim;

    // Ignore empty lines
    if (line.empty()) {
        return true;
    }

    // Ignore comments
    if (isComment(line)) {
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

bool IniParser::consumeKeyValue(std::string_view line,
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

    value = trimQuote(value);

    m_data_.at(currentSection).emplace(key, value);

    return true;
}