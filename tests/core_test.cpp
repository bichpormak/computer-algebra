#include "core/processing_input.h"
#include <gtest/gtest.h>

TEST(processing_input_cases, split_number_into_digits) {
    ASSERT_EQ(split_number_into_digits(10), (std::vector<int8_t> {1, 0}));
    ASSERT_EQ(split_number_into_digits(-10), (std::vector<int8_t> {1, 0}));
    ASSERT_EQ(split_number_into_digits(0), (std::vector<int8_t> {0}));
}

TEST(processing_input_cases, is_positive_number) {
    ASSERT_TRUE(is_positive_number(1));
    ASSERT_TRUE(is_positive_number(0));
    ASSERT_FALSE(is_positive_number(-1));
}

TEST(processing_input_cases, reverse_digits_in_vector) {
    ASSERT_EQ(reverse_digits_in_vector(std::vector<int8_t> {3, 5}), (std::vector<int8_t> {5, 3}));
    ASSERT_EQ(reverse_digits_in_vector(std::vector<int8_t> {0}), (std::vector<int8_t> {0}));
}