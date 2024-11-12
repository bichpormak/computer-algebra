#include <gtest/gtest.h>
#include "core/processing_input.h"


TEST(ProcessingInputTest, split_number_into_digits) {
    ASSERT_EQ(split_number_into_digits(10), (std::vector<uint8_t> {1, 0}));
    ASSERT_EQ(split_number_into_digits(-10), (std::vector<uint8_t> {1, 0}));
    ASSERT_EQ(split_number_into_digits(0), (std::vector<uint8_t> {0}));
}

TEST(ProcessingInputTest, determining_sign_number) {
    ASSERT_EQ(determining_sign_number(1), SignNumber::POSITIVE);
    ASSERT_EQ(determining_sign_number(0), SignNumber::ZERO);
    ASSERT_EQ(determining_sign_number(-1), SignNumber::NEGATIVE);
}

TEST(ProcessingInputTest, reverse_digits_in_vector) {
    ASSERT_EQ(reverse_digits_in_vector(std::vector<uint8_t> {3, 5}), (std::vector<uint8_t> {5, 3}));
    ASSERT_EQ(reverse_digits_in_vector(std::vector<uint8_t> {0}), (std::vector<uint8_t> {0}));
}