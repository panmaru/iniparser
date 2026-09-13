#include "split.h"
#include "trim.h"

#include <iostream> // std::cout

int main() {
    using namespace iniparser::utils::string;
    auto result = split("Hello=World!", '=');
    for (const auto &s : result) {
        std::cout << s << '\n';
    }
}