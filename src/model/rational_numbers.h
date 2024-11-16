#ifndef RATIONAL_NUMBERS_H
#define RATIONAL_NUMBERS_H

#include "integer_numbers.h"
#include "natural_number.h"


class RationalNumber {

private:
    IntegerNumber numerator_integer_number_;
    NaturalNumber denominator_natural_number_;

public:
    RationalNumber() : numerator_integer_number_(0), denominator_natural_number_(1) {}

    RationalNumber(IntegerNumber numerator, NaturalNumber denominator)
        :
        numerator_integer_number_(numerator),
        denominator_natural_number_(denominator) {}

    RationalNumber(int value)
        : numerator_integer_number_(IntegerNumber(value)), denominator_natural_number_(NaturalNumber(1)) {}


    RationalNumber operator+(const RationalNumber& other) const;
    RationalNumber operator-(const RationalNumber& other) const;
    RationalNumber operator*(const RationalNumber& other) const;
    RationalNumber operator/(const RationalNumber& other) const;

    RationalNumber& operator+=(const RationalNumber& other);
    RationalNumber& operator-=(const RationalNumber& other);
    RationalNumber& operator*=(const RationalNumber& other);
    RationalNumber& operator/=(const RationalNumber& other);

    bool operator==(const RationalNumber& other) const;
    bool operator!=(const RationalNumber& other) const;


    std::unique_ptr<RationalNumber> add(RationalNumber& other) const;
    std::unique_ptr<RationalNumber> subtract(RationalNumber& other) const;
    std::unique_ptr<RationalNumber> multiply(RationalNumber& other) const;
    std::unique_ptr<RationalNumber> divide(RationalNumber& other) const;
    std::unique_ptr<RationalNumber> convert_integer_to_fraction(IntegerNumber& other) const;
    std::unique_ptr<IntegerNumber> convert_reduced_fraction_to_integer() const;
    std::unique_ptr<RationalNumber> reduce_fraction() const;
    bool is_integer() const;

public:
    std::unique_ptr<IntegerNumber> get_integer() { return std::make_unique<IntegerNumber>(numerator_integer_number_); };
    std::unique_ptr<NaturalNumber> get_natural() { return std::make_unique<NaturalNumber>(denominator_natural_number_); };

    const IntegerNumber& get_numerator() const { return numerator_integer_number_; }
    const NaturalNumber& get_denominator() const { return denominator_natural_number_; }
};



#endif