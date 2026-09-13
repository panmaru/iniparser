#include "trim.h"

#include <iostream> // std::cout

int main() {
    std::cout << iniparser::utils::string::trim(
                     " \t Hello World  \n",
                     iniparser::utils::string::TrimPolicy::Left)
              << std::endl;
}