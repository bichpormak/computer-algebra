#include <gtest/gtest.h>
#include "../src/model/natural_number.h"

class NaturalNumberTest : public ::testing::Test {
protected:
    std::unique_ptr<NaturalNumber> num_small_;
    std::unique_ptr<NaturalNumber> num_large_;
    std::unique_ptr<NaturalNumber> num_zero_;
    std::unique_ptr<NaturalNumber> num_three_;

    void SetUp() override {
        num_small_ = std::make_unique<NaturalNumber>(5);
        num_large_ = std::make_unique<NaturalNumber>(123456789);
        num_zero_ = std::make_unique<NaturalNumber>(0);
        num_three_ = std::make_unique<NaturalNumber>(3);

    }

    void TearDown() override {
    }
};

TEST_F(NaturalNumberTest, is_zero) {
    EXPECT_FALSE(num_large_->is_zero());
    EXPECT_TRUE(num_zero_->is_zero());
}

TEST_F(NaturalNumberTest, add) {
    auto result = num_small_->add(*num_large_);
    auto expected = std::make_unique<NaturalNumber>(123456794);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());

    result = num_large_->add(*num_zero_);
    EXPECT_EQ(result->get_digits_of_number(), num_large_->get_digits_of_number());
}

TEST_F(NaturalNumberTest, subtract) {
    auto result_zero = num_small_->subtract(*num_small_);
    EXPECT_TRUE(result_zero->is_zero());

    auto result = num_large_->subtract(*num_small_);
    auto expected = std::make_unique<NaturalNumber>(123456784);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());

    EXPECT_THROW(num_small_->subtract(*num_large_), std::invalid_argument);
}

TEST_F(NaturalNumberTest, multiply) {
    auto result = num_small_->multiply(*num_large_);
    auto expected = std::make_unique<NaturalNumber>(617283945);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());

    result = num_large_->multiply(*num_zero_);
    EXPECT_TRUE(result->is_zero());
}

TEST_F(NaturalNumberTest, compare) {
    EXPECT_EQ(num_small_->compare(*num_large_), 1); // num_small_ < num_large_
    EXPECT_EQ(num_large_->compare(*num_small_), 2); // num_large_ > num_small_
    EXPECT_EQ(num_small_->compare(*num_small_), 0); // num_small_ == num_small_
}

TEST_F(NaturalNumberTest, add_one) {
    auto result = num_small_->add_one();
    auto expected = std::make_unique<NaturalNumber>(6);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());
}

TEST_F(NaturalNumberTest, multiply_by_digit) {
    auto result = num_large_->multiply_by_digit(9);
    auto expected = std::make_unique<NaturalNumber>(1111111101);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());

    result = num_large_->multiply_by_digit(0);
    EXPECT_TRUE(result->is_zero());

    EXPECT_THROW(num_large_->multiply_by_digit(-1), std::invalid_argument);
    EXPECT_THROW(num_large_->multiply_by_digit(10), std::invalid_argument);
}

TEST_F(NaturalNumberTest, multiply_by_ten_in_power) {
    auto result = num_small_->multiply_by_ten_in_power(3);
    auto expected = std::make_unique<NaturalNumber>(5000);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());

    result = num_small_->multiply_by_ten_in_power(0);
    EXPECT_EQ(result->get_digits_of_number(), num_small_->get_digits_of_number());

    EXPECT_THROW(num_small_->multiply_by_ten_in_power(-1), std::invalid_argument);
}

TEST_F(NaturalNumberTest, subtract_with_multiply_digit) {
    auto result = num_large_->subtract_with_multiply_digit(*num_small_, 2);
    auto expected = std::make_unique<NaturalNumber>(123456779);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());

    result = num_large_->subtract_with_multiply_digit(*num_small_, 0);
    EXPECT_EQ(result->get_digits_of_number(), num_large_->get_digits_of_number());

    EXPECT_THROW(num_large_->subtract_with_multiply_digit(*num_small_, -1), std::invalid_argument);
    EXPECT_THROW(num_large_->subtract_with_multiply_digit(*num_small_, 10), std::invalid_argument);
}

TEST_F(NaturalNumberTest, get_first_digit_after_division_number_on_ten_in_power) {
    auto result = num_large_->get_first_digit_after_division_number_on_ten_in_power(*num_small_, 0);
    auto expected = std::make_unique<NaturalNumber>(2); // 123456789 / 5 ≈ 2
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());

    EXPECT_THROW(num_large_->get_first_digit_after_division_number_on_ten_in_power(*num_small_, -1), std::invalid_argument);

    EXPECT_THROW(num_large_->get_first_digit_after_division_number_on_ten_in_power(*num_zero_, 0), std::invalid_argument);
}

TEST_F(NaturalNumberTest, division_numbers_with_remainder) {
    auto result = num_large_->division_numbers_with_remainder(*num_small_);
    auto expected = std::make_unique<NaturalNumber>(24691357);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());

    EXPECT_THROW(num_large_->division_numbers_with_remainder(*num_zero_), std::invalid_argument);

    result = num_small_->division_numbers_with_remainder(*num_large_);
    expected = std::make_unique<NaturalNumber>(0);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());
}

TEST_F(NaturalNumberTest, calculating_remainder_after_division) {
    auto result = num_large_->calculating_remainder_after_division(*num_small_);
    auto expected = std::make_unique<NaturalNumber>(4);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());

    EXPECT_THROW(num_large_->calculating_remainder_after_division(*num_zero_), std::invalid_argument);

    result = num_small_->calculating_remainder_after_division(*num_large_);
    EXPECT_EQ(result->get_digits_of_number(), num_small_->get_digits_of_number());
}

TEST_F(NaturalNumberTest, calculate_gcd) {
    auto result = num_small_->calculate_gcd(*num_large_);
    auto expected = std::make_unique<NaturalNumber>(1);
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());
}

TEST_F(NaturalNumberTest, calculate_lcm) {
    auto num15 = std::make_unique<NaturalNumber>(15);
    auto result = num_small_->calculate_lcm(*num15);
    auto expected = std::make_unique<NaturalNumber>(15); // НОК(5, 15) = 15
    EXPECT_EQ(result->get_digits_of_number(), expected->get_digits_of_number());
}
