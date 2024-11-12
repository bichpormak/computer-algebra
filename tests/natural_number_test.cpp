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
        num_large_ = std::make_unique<NaturalNumber>(10000000000);
        num_zero_ = std::make_unique<NaturalNumber>(1);
        num_three_ = std::make_unique<NaturalNumber>(3);
    }

    void TearDown() override {

    }
};

TEST_F(NaturalNumberTest, is_zero) {
    EXPECT_FALSE(num_small_->is_zero());
    EXPECT_FALSE(num_large_->is_zero());
    EXPECT_TRUE(num_zero_->is_zero());
}

TEST_F(NaturalNumberTest, compare) {
    EXPECT_EQ(num_small_->compare(*num_large_), 1);
    EXPECT_EQ(num_large_->compare(*num_small_), 2);
    EXPECT_EQ(num_small_->compare(*num_small_), 0);
    EXPECT_EQ(num_zero_->compare(*num_zero_), 0);
    EXPECT_EQ(num_zero_->compare(*num_small_), 1);
    EXPECT_EQ(num_small_->compare(*num_zero_), 2);
}

TEST_F(NaturalNumberTest, add_one) {
    auto result = num_large_->add_one();
    auto* natural_result = dynamic_cast<NaturalNumber*>(result.get());
    ASSERT_NE(natural_result, nullptr);
    EXPECT_EQ(natural_result->get_digits_of_number(), (std::vector<uint8_t>{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}));
}

TEST_F(NaturalNumberTest, multiply_by_digit) {
    auto result = num_large_->multiply_by_digit(3);
    auto* natResult = dynamic_cast<NaturalNumber*>(result.get());
    ASSERT_NE(natResult, nullptr);
    EXPECT_EQ(natResult->get_digits_of_number(), (std::vector<uint8_t>{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
}

TEST_F(NaturalNumberTest, add) {
    auto sum = num_small_->add(*num_large_);
    auto* natSum = dynamic_cast<NaturalNumber*>(sum.get());
    ASSERT_NE(natSum, nullptr);
    EXPECT_EQ(natSum->get_digits_of_number(), (std::vector<uint8_t>{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5}));
}

TEST_F(NaturalNumberTest, subtract) {
    auto diff = num_large_->subtract(*num_three_);
    auto* natDiff = dynamic_cast<NaturalNumber*>(diff.get());
    ASSERT_NE(natDiff, nullptr);
    EXPECT_EQ(natDiff->get_digits_of_number(), (std::vector<uint8_t>{9, 9, 9, 9, 9, 9, 9, 9, 9, 7}));
}

TEST_F(NaturalNumberTest, multiply) {
    auto product = num_small_->multiply(*num_large_);
    auto* natProduct = dynamic_cast<NaturalNumber*>(product.get());
    ASSERT_NE(natProduct, nullptr);
    EXPECT_EQ(natProduct->get_digits_of_number(), (std::vector<uint8_t>{5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
}

TEST_F(NaturalNumberTest, calculate_gcd) {
    auto gcd = num_small_->calculate_gcd(*num_large_);
    auto* natGcd = dynamic_cast<NaturalNumber*>(gcd.get());
    ASSERT_NE(natGcd, nullptr);
    EXPECT_EQ(natGcd->get_number(), 5);
}

TEST_F(NaturalNumberTest, calculate_lcm) {
    auto lcm = num_small_->calculate_lcm(*num_large_);
    auto* natLcm = dynamic_cast<NaturalNumber*>(lcm.get());
    ASSERT_NE(natLcm, nullptr);
    EXPECT_EQ(natLcm->get_number(), 10000000000);
}

TEST_F(NaturalNumberTest, multiply_by_ten_in_power) {
    auto result = num_small_->multiply_by_ten_in_power(2);
    auto* natResult = dynamic_cast<NaturalNumber*>(result.get());
    ASSERT_NE(natResult, nullptr);
    EXPECT_EQ(natResult->get_digits_of_number(), (std::vector<uint8_t>{5, 0, 0}));
}

TEST_F(NaturalNumberTest, get_first_digit_after_division_on_ten_in_power) {
    auto result = num_large_->get_first_digit_after_division_number_on_ten_in_power(1);
    auto* natResult = dynamic_cast<NaturalNumber*>(result.get());
    ASSERT_NE(natResult, nullptr);
    EXPECT_EQ(natResult->get_digits_of_number(), std::vector<uint8_t>{1});
}


TEST_F(NaturalNumberTest, subtract_with_multiply_digit) {
    auto result = num_large_->subtract_with_multiply_digit(*num_small_, 2);
    auto* natResult = dynamic_cast<NaturalNumber*>(result.get());
    ASSERT_NE(natResult, nullptr);
    EXPECT_EQ(natResult->get_digits_of_number(), (std::vector<uint8_t>{9, 9, 9, 9, 9, 9, 9, 9, 9, 0}));
}

TEST_F(NaturalNumberTest, division_numbers_with_remainder) {
    auto quotient = num_large_->division_numbers_with_remainder(*num_three_);
    auto remainder = num_large_->calculating_remainder_after_division(*num_three_);

    auto* natQuotient = dynamic_cast<NaturalNumber*>(quotient.get());
    ASSERT_NE(natQuotient, nullptr);
    EXPECT_EQ(natQuotient->get_digits_of_number(), (std::vector<uint8_t>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3}));

    auto* natRemainder = dynamic_cast<NaturalNumber*>(remainder.get());
    ASSERT_NE(natRemainder, nullptr);
    EXPECT_EQ(natRemainder->get_digits_of_number(), std::vector<uint8_t>{1});
}

TEST_F(NaturalNumberTest, calculating_remainder_after_division) {
    auto remainder = num_large_->calculating_remainder_after_division(*num_small_);
    auto* natRemainder = dynamic_cast<NaturalNumber*>(remainder.get());
    ASSERT_NE(natRemainder, nullptr);
    EXPECT_TRUE(natRemainder->is_zero());

    auto remainder_non_zero = num_large_->calculating_remainder_after_division(*num_three_);
    auto* natRemainderNonZero = dynamic_cast<NaturalNumber*>(remainder_non_zero.get());
    ASSERT_NE(natRemainderNonZero, nullptr);
    EXPECT_EQ(natRemainderNonZero->get_digits_of_number(), std::vector<uint8_t>{1});
}
