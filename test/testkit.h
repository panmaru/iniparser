#pragma once
#ifndef INIPARSER_TEST_TESTKIT_H
#define INIPARSER_TEST_TESTKIT_H

#include <iostream> // std::cout, std::endl

namespace iniparser::testkit {

inline int testsPassed = 0;
inline int testsFailed = 0;

} // namespace iniparser::testkit

#define TEST_CASE(name) std::cout << "=== " << (name) << " ===" << std::endl

#define ASSERT_EQ(actual, expected, message)                                   \
    do {                                                                       \
        auto &&actual_ = (actual);                                             \
        auto &&expected_ = (expected);                                         \
        if (actual_ == expected_) {                                            \
            ++iniparser::testkit::testsPassed;                                 \
            std::cout << "PASSED: " << (message) << std::endl;                 \
        } else {                                                               \
            ++iniparser::testkit::testsFailed;                                 \
            std::cout << "FAILED: " << (message)                               \
                      << "\n  Expected: " << expected_                         \
                      << "\n  Actual: " << actual_ << std::endl;               \
        }                                                                      \
    } while (0)

#define ASSERT_TRUE(condition, message)                                        \
    do {                                                                       \
        if ((condition)) {                                                     \
            ++iniparser::testkit::testsPassed;                                 \
            std::cout << "PASSED: " << (message) << std::endl;                 \
        } else {                                                               \
            ++iniparser::testkit::testsFailed;                                 \
            std::cout << "FAILED: " << (message) << " (condition failed)"      \
                      << std::endl;                                            \
        }                                                                      \
    } while (0)

#define ASSERT_FALSE(condition, message)                                       \
    do {                                                                       \
        if (!(condition)) {                                                    \
            ++iniparser::testkit::testsPassed;                                 \
            std::cout << "PASSED: " << (message) << std::endl;                 \
        } else {                                                               \
            ++iniparser::testkit::testsFailed;                                 \
            std::cout << "FAILED: " << (message) << " (expected false)"        \
                      << std::endl;                                            \
        }                                                                      \
    } while (0)

#endif // INIPARSER_TEST_TESTKIT_H