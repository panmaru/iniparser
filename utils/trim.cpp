#include "trim.h"

#include <cctype> // std::isspace

namespace iniparser::utils::string {

std::string_view trim(const std::string_view sv, const TrimPolicy policy) {
    std::size_t begin = 0;
    std::size_t end = sv.size();

    if (policy == TrimPolicy::Both || policy == TrimPolicy::Left) {
        while (begin < end && std::isspace(sv[begin])) {
            ++begin;
        }
    }
    if (policy == TrimPolicy::Both || policy == TrimPolicy::Right) {
        while (end > begin && std::isspace(sv[end - 1])) {
            --end;
        }
    }

    return sv.substr(begin, end - begin);
}

std::string_view trimComment(std::string_view line) {
    auto getCommentPos = [](std::string_view line) {
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
    };

    size_t commentPos = getCommentPos(line);
    if (commentPos != std::string_view::npos) {
        line = line.substr(0, commentPos);
    }

    return trim(line);
}

std::string_view trimQuote(std::string_view line) {
    line = trim(line);

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

} // namespace iniparser::utils::string