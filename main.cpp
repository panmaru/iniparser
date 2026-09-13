#include "iniparser.h"
#include "testkit.h"

void testBasicParsing() {
    TEST_CASE("Basic parsing");
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

int main() { testBasicParsing(); }