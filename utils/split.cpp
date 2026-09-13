#include "split.h"

#include <algorithm> // std::count

namespace iniparser::utils::string {

std::vector<std::string_view> split(const std::string_view sv,
                                    const char delim) {
    size_t lastPos = 0;

    std::vector<std::string_view> result;
    size_t delimCnt = std::count(sv.begin(), sv.end(), delim);
    result.reserve(delimCnt);

    size_t currDelimPos = sv.find(delim, lastPos);
    while (currDelimPos != std::string_view::npos) {
        result.emplace_back(sv.substr(lastPos, currDelimPos - lastPos));
        result.emplace_back(sv.substr(currDelimPos, 1));
        lastPos = currDelimPos + 1;
        currDelimPos = sv.find(delim, lastPos);
    }
    result.emplace_back(sv.substr(lastPos));

    return result;
}

} // namespace iniparser::utils::string