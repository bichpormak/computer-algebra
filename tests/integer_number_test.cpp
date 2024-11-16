#include <gtest/gtest.h>
#include "../src/model/integer_numbers.h"

class IntegerNumberTest : public ::testing::Test {
protected:
    std::unique_ptr<IntegerNumber> num_pos_small_;
    std::unique_ptr<IntegerNumber> num_neg_small_;
    std::unique_ptr<IntegerNumber> num_pos_large_;
    std::unique_ptr<IntegerNumber> num_neg_large_;
    std::unique_ptr<IntegerNumber> num_zero_;


    void SetUp() override {
        num_pos_small_ = std::make_unique<IntegerNumber>(5);
        num_neg_small_ = std::make_unique<IntegerNumber>(-5);
        num_pos_large_ = std::make_unique<IntegerNumber>(123456789);
        num_neg_large_ = std::make_unique<IntegerNumber>(-123456789);
        num_zero_ = std::make_unique<IntegerNumber>(0);
    }

    void TearDown() override {
    }
};

TEST_F(IntegerNumberTest, is_number_positive) {
    EXPECT_EQ(num_pos_small_->is_number_positive(), 2);
    EXPECT_EQ(num_neg_small_->is_number_positive(), 1);
    EXPECT_EQ(num_zero_->is_number_positive(), 0);
}

TEST_F(IntegerNumberTest, add) {
    auto result = num_pos_small_->add(*num_pos_large_);
    EXPECT_EQ(result->get_number(), 123456794);

    result = num_neg_small_->add(*num_neg_large_);
    EXPECT_EQ(result->get_number(), -123456794);
}

TEST_F(IntegerNumberTest, subtract) {
    auto result = num_neg_small_->subtract(*num_pos_small_);
    EXPECT_EQ(result->get_number(), -10);

    result = num_neg_small_->subtract(*num_zero_);
    EXPECT_EQ(result->get_number(), -5);
}

TEST_F(IntegerNumberTest, multiply) {
    auto result = num_neg_small_->multiply(*num_neg_large_);
    EXPECT_EQ(result->get_number(), 617283945);

    result = num_pos_large_->multiply(*num_zero_);
    EXPECT_EQ(result->get_number(), 0);
}

TEST_F(IntegerNumberTest, get_absolute_value) {
    auto abs_value = num_pos_small_->get_absolute_value();
    EXPECT_EQ(abs_value->get_number(), 5);

    abs_value = num_neg_large_->get_absolute_value();
    EXPECT_EQ(abs_value->get_number(), 123456789);

    abs_value = num_zero_->get_absolute_value();
    EXPECT_EQ(abs_value->get_number(), 0);
}

TEST_F(IntegerNumberTest, change_sign) {
    auto result = num_pos_small_->change_sign();
    EXPECT_EQ(result->get_number(), -5);

    result = num_neg_large_->change_sign();
    EXPECT_EQ(result->get_number(), 123456789);

    result = num_zero_->change_sign();
    EXPECT_EQ(result->get_number(), 0);
}

TEST_F(IntegerNumberTest, converting_natural_to_integer) {
    auto natural_num = std::make_unique<NaturalNumber>(123);
    auto integer_num = num_zero_->converting_natural_to_integer(*natural_num);
    EXPECT_EQ(integer_num->get_number(), 123);
}

TEST_F(IntegerNumberTest, converting_positive_integer_to_natural) {
    auto natural_num = num_pos_large_->converting_positive_integer_to_natural();
    EXPECT_EQ(natural_num->get_number(), 123456789);

    EXPECT_THROW(num_neg_small_->converting_positive_integer_to_natural(), std::invalid_argument);
}

TEST_F(IntegerNumberTest, calculating_quotient) {
    auto result = num_pos_large_->calculating_quotient(*num_pos_small_);
    EXPECT_EQ(result->get_number(), 24691357);

    EXPECT_THROW(num_pos_small_->calculating_quotient(*num_zero_), std::invalid_argument);
}

TEST_F(IntegerNumberTest, calculating_remainder_after_division) {
    auto result = num_pos_large_->calculating_remainder_after_division(*num_pos_small_);
    EXPECT_EQ(result->get_number(), 4);

    EXPECT_THROW(num_pos_small_->calculating_remainder_after_division(*num_zero_), std::invalid_argument);
}
