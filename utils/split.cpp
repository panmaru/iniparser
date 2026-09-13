#include "split.h"

namespace iniparser::utils::string {

std::vector<std::string> split(const std::string &str, const char delim) {
    size_t lastPos = 0;

    std::vector<std::string> result;
    size_t currDelimPos = str.find(delim, lastPos);
    while (currDelimPos != std::string::npos) {
        result.emplace_back(str.substr(lastPos, currDelimPos - lastPos));
        result.emplace_back(1, delim);
        lastPos = currDelimPos + 1;
        currDelimPos = str.find(delim, lastPos);
    }
    result.emplace_back(str.substr(lastPos));

    return result;
}

} // namespace iniparser::utils::string