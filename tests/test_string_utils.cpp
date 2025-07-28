#include <gtest/gtest.h>

#include "utils/string_utils.hpp"

using namespace cpp_template::utils;

class StringUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Trim tests
TEST_F(StringUtilsTest, TrimEmptyString) {
    EXPECT_EQ(trim(""), "");
    EXPECT_EQ(trim("   "), "");
    EXPECT_EQ(trim("\t\n\r "), "");
}

TEST_F(StringUtilsTest, TrimNoWhitespace) {
    EXPECT_EQ(trim("hello"), "hello");
    EXPECT_EQ(trim("world"), "world");
}

TEST_F(StringUtilsTest, TrimLeadingWhitespace) {
    EXPECT_EQ(trim("  hello"), "hello");
    EXPECT_EQ(trim("\t\nworld"), "world");
}

TEST_F(StringUtilsTest, TrimTrailingWhitespace) {
    EXPECT_EQ(trim("hello  "), "hello");
    EXPECT_EQ(trim("world\t\n"), "world");
}

TEST_F(StringUtilsTest, TrimBothEnds) {
    EXPECT_EQ(trim("  hello  "), "hello");
    EXPECT_EQ(trim("\t\n world \r\n"), "world");
}

TEST_F(StringUtilsTest, TrimPreservesInternalWhitespace) {
    EXPECT_EQ(trim("  hello world  "), "hello world");
    EXPECT_EQ(trim("\thello\tworld\n"), "hello\tworld");
}

// Left trim tests
TEST_F(StringUtilsTest, LTrimFunction) {
    EXPECT_EQ(ltrim(""), "");
    EXPECT_EQ(ltrim("hello"), "hello");
    EXPECT_EQ(ltrim("  hello"), "hello");
    EXPECT_EQ(ltrim("  hello  "), "hello  ");
}

// Right trim tests
TEST_F(StringUtilsTest, RTrimFunction) {
    EXPECT_EQ(rtrim(""), "");
    EXPECT_EQ(rtrim("hello"), "hello");
    EXPECT_EQ(rtrim("hello  "), "hello");
    EXPECT_EQ(rtrim("  hello  "), "  hello");
}

// Case conversion tests
TEST_F(StringUtilsTest, ToUpperCase) {
    EXPECT_EQ(to_upper(""), "");
    EXPECT_EQ(to_upper("hello"), "HELLO");
    EXPECT_EQ(to_upper("Hello World"), "HELLO WORLD");
    EXPECT_EQ(to_upper("123abc!@#"), "123ABC!@#");
    EXPECT_EQ(to_upper("ALREADY_UPPER"), "ALREADY_UPPER");
}

TEST_F(StringUtilsTest, ToLowerCase) {
    EXPECT_EQ(to_lower(""), "");
    EXPECT_EQ(to_lower("HELLO"), "hello");
    EXPECT_EQ(to_lower("Hello World"), "hello world");
    EXPECT_EQ(to_lower("123ABC!@#"), "123abc!@#");
    EXPECT_EQ(to_lower("already_lower"), "already_lower");
}

// Split tests
TEST_F(StringUtilsTest, SplitEmptyString) {
    auto result = split("", ',');
    EXPECT_TRUE(result.empty());
}

TEST_F(StringUtilsTest, SplitNoDelimiter) {
    auto result = split("hello", ',');
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "hello");
}

TEST_F(StringUtilsTest, SplitSingleDelimiter) {
    auto result = split("hello,world", ',');
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
}

TEST_F(StringUtilsTest, SplitMultipleDelimiters) {
    auto result = split("a,b,c,d", ',');
    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
    EXPECT_EQ(result[3], "d");
}

TEST_F(StringUtilsTest, SplitConsecutiveDelimiters) {
    auto result = split("a,,b", ',');
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
}

TEST_F(StringUtilsTest, SplitLeadingTrailingDelimiters) {
    auto result = split(",hello,world,", ',');
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
}

// Join tests
TEST_F(StringUtilsTest, JoinEmptyVector) {
    std::vector<std::string> empty;
    EXPECT_EQ(join(empty, ","), "");
}

TEST_F(StringUtilsTest, JoinSingleElement) {
    std::vector<std::string> single = {"hello"};
    EXPECT_EQ(join(single, ","), "hello");
}

TEST_F(StringUtilsTest, JoinMultipleElements) {
    std::vector<std::string> multiple = {"apple", "banana", "cherry"};
    EXPECT_EQ(join(multiple, ","), "apple,banana,cherry");
    EXPECT_EQ(join(multiple, " | "), "apple | banana | cherry");
}

// Starts with tests
TEST_F(StringUtilsTest, StartsWithTests) {
    EXPECT_TRUE(starts_with("hello world", "hello"));
    EXPECT_TRUE(starts_with("hello", "hello"));
    EXPECT_TRUE(starts_with("hello", ""));
    EXPECT_FALSE(starts_with("hello", "world"));
    EXPECT_FALSE(starts_with("hi", "hello"));
    EXPECT_FALSE(starts_with("", "hello"));
}

// Ends with tests
TEST_F(StringUtilsTest, EndsWithTests) {
    EXPECT_TRUE(ends_with("hello world", "world"));
    EXPECT_TRUE(ends_with("world", "world"));
    EXPECT_TRUE(ends_with("world", ""));
    EXPECT_FALSE(ends_with("world", "hello"));
    EXPECT_FALSE(ends_with("hi", "world"));
    EXPECT_FALSE(ends_with("", "world"));
}

// Replace all tests
TEST_F(StringUtilsTest, ReplaceAllNoOccurrences) {
    EXPECT_EQ(replace_all("hello world", "xyz", "abc"), "hello world");
}

TEST_F(StringUtilsTest, ReplaceAllSingleOccurrence) {
    EXPECT_EQ(replace_all("hello world", "world", "universe"), "hello universe");
}

TEST_F(StringUtilsTest, ReplaceAllMultipleOccurrences) {
    EXPECT_EQ(replace_all("hello hello hello", "hello", "hi"), "hi hi hi");
}

TEST_F(StringUtilsTest, ReplaceAllEmptyString) {
    EXPECT_EQ(replace_all("hello", "", "x"), "hello");
}

TEST_F(StringUtilsTest, ReplaceAllWithEmpty) {
    EXPECT_EQ(replace_all("hello world", "world", ""), "hello ");
}

TEST_F(StringUtilsTest, ReplaceAllOverlapping) {
    EXPECT_EQ(replace_all("aaa", "aa", "b"), "ba");
}