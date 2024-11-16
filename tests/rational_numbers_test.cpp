#include <gtest/gtest.h>
#include "../src/model/rational_numbers.h"

class RationalNumberTest : public ::testing::Test {
protected:
    std::unique_ptr<RationalNumber> rational_one_half_;
    std::unique_ptr<RationalNumber> rational_one_third_;
    std::unique_ptr<RationalNumber> rational_two_;
    std::unique_ptr<RationalNumber> rational_zero_;

    void SetUp() override {
        rational_one_half_ = std::make_unique<RationalNumber>(IntegerNumber(1), NaturalNumber(2));
        rational_one_third_ = std::make_unique<RationalNumber>(IntegerNumber(1), NaturalNumber(3));
        rational_zero_ = std::make_unique<RationalNumber>(IntegerNumber(0), NaturalNumber(1));
        rational_two_ = std::make_unique<RationalNumber>(IntegerNumber(2), NaturalNumber(1));
    }

    void TearDown() override {
    }
};

TEST_F(RationalNumberTest, add) {
    auto result = rational_one_half_->add(*rational_one_third_);
    RationalNumber expected(IntegerNumber(5), NaturalNumber(6));
    EXPECT_EQ(result->get_integer()->get_number(), expected.get_integer()->get_number());
    EXPECT_EQ(result->get_natural()->get_number(), expected.get_natural()->get_number());
}

TEST_F(RationalNumberTest, subtract) {
    auto result = rational_one_half_->subtract(*rational_one_third_);
    RationalNumber expected(IntegerNumber(1), NaturalNumber(6));
    EXPECT_EQ(result->get_integer()->get_number(), expected.get_integer()->get_number());
    EXPECT_EQ(result->get_natural()->get_number(), expected.get_natural()->get_number());
}

TEST_F(RationalNumberTest, multiply) {
    auto result = rational_one_half_->multiply(*rational_one_third_);
    RationalNumber expected(IntegerNumber(1), NaturalNumber(6));
    EXPECT_EQ(result->get_integer()->get_number(), expected.get_integer()->get_number());
    EXPECT_EQ(result->get_natural()->get_number(), expected.get_natural()->get_number());
}

TEST_F(RationalNumberTest, divide) {
    auto result = rational_one_half_->divide(*rational_one_third_);
    RationalNumber expected(IntegerNumber(3), NaturalNumber(2));
    EXPECT_EQ(result->get_integer()->get_number(), expected.get_integer()->get_number());
    EXPECT_EQ(result->get_natural()->get_number(), expected.get_natural()->get_number());

    EXPECT_THROW(rational_one_half_->divide(*rational_zero_), std::invalid_argument);
}

TEST_F(RationalNumberTest, convert_integer_to_fraction) {
    IntegerNumber integer_five(5);
    auto result = rational_zero_->convert_integer_to_fraction(integer_five);
    EXPECT_EQ(result->get_integer()->get_number(), 5);
    EXPECT_EQ(result->get_natural()->get_number(), 1);
}

TEST_F(RationalNumberTest, convert_reduced_fraction_to_integer) {
    auto result = rational_two_->convert_reduced_fraction_to_integer();
    EXPECT_EQ(result->get_number(), 2);

    EXPECT_THROW(rational_one_half_->convert_reduced_fraction_to_integer(), std::invalid_argument);
}

TEST_F(RationalNumberTest, reduce_fraction) {
    RationalNumber fraction(IntegerNumber(2), NaturalNumber(4));
    auto result = fraction.reduce_fraction();
    EXPECT_EQ(result->get_integer()->get_number(), 1);
    EXPECT_EQ(result->get_natural()->get_number(), 2);
}

TEST_F(RationalNumberTest, is_integer) {
    EXPECT_TRUE(rational_two_->is_integer());

    EXPECT_FALSE(rational_one_half_->is_integer());

    EXPECT_TRUE(rational_zero_->is_integer());
}
