#include "split.h"

#include <algorithm> // std::count

#include "trim.h"

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
        lastPos = currDelimPos + 1;
        currDelimPos = sv.find(delim, lastPos);
    }
    result.emplace_back(sv.substr(lastPos));

    return result;
}

std::pair<std::string_view, std::string_view>
splitKeyValue(std::string_view line) {
    using iniparser::utils::string::trim;

    size_t equalPos = line.find('=');
    if (equalPos == std::string_view::npos) {
        return {};
    }

    auto key = trim(line.substr(0, equalPos));
    auto value = trim(line.substr(equalPos + 1));
    return {key, value};
}

} // namespace iniparser::utils::string