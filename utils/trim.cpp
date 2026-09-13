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
} // namespace iniparser::utils::string