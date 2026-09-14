#include "iniparser.h"
#include "testkit.h"

void testBasicParsing() {
    TEST_CASE("Basic Parsing");
    const char *ini = R"ini(
key1 = value1
key2 = value2
[Section1]
key3 = value3
)ini";

    IniParser parser;
    bool ok = parser.parse(ini);

    ASSERT_TRUE(ok, "Parse should successed");
    ASSERT_EQ(parser.get("", "key1").value_or(""), "value1", "Top-level key1");
    ASSERT_EQ(parser.get("", "key2").value_or(""), "value2", "Top-level key2");
    ASSERT_EQ(parser.get("Section1", "key3").value_or(""), "value3",
              "Section1 key3");
}

void testComment() {
    TEST_CASE("Comment Handling");
    const char *ini = R"ini(
; semicolon comment
# hash comment
key1 = value1 ; inline comment
key2 = value2 # inline hash comment
key3 = "value3;with;semicolons" ; this is a comment
key4 = "value4#with#hash" ; comment
)ini";

    IniParser parser;
    bool ok = parser.parse(ini);
    ASSERT_TRUE(ok, "Parse should successed");
    ASSERT_EQ(parser.get("", "key1").value_or(""), "value1",
              "Value before inline semicolon comment");
    ASSERT_EQ(parser.get("", "key2").value_or(""), "value2",
              "Value before inline hash comment");
    ASSERT_EQ(parser.get("", "key3").value_or(""), "value3;with;semicolons",
              "Value with semicolons");
    ASSERT_EQ(parser.get("", "key4").value_or(""), "value4#with#hash",
              "Value with hash");
}

void testSections() {
    TEST_CASE("Section Handling");

    const char *ini = R"ini(
toplevel = top
[section1]
key1 = val1
[section2]
key2 = val2
[section3]
key3 = val3
)ini";

    IniParser parser;
    bool ok = parser.parse(ini);
    ASSERT_TRUE(ok, "Parse should successed");
    ASSERT_EQ(parser.get("", "toplevel").value_or(""), "top",
              "Top-level key toplevel");
    ASSERT_EQ(parser.get("section1", "key1").value_or(""), "val1",
              "Section1 key1");
    ASSERT_EQ(parser.get("section2", "key2").value_or(""), "val2",
              "Section2 key2");
    ASSERT_EQ(parser.get("section3", "key3").value_or(""), "val3",
              "Section3 key3");
}

int main() {
    testBasicParsing();
    testComment();
    testSections();
}