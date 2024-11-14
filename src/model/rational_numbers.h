#ifndef RATIONAL_NUMBERS_H
#define RATIONAL_NUMBERS_H

#include "integer_numbers.h"
#include "natural_number.h"


class RationalNumber {

private:
    IntegerNumber numerator_integer_number_;
    NaturalNumber denominator_natural_number_;

public:
    RationalNumber(IntegerNumber numerator, NaturalNumber denominator)
        :
        numerator_integer_number_(numerator),
        denominator_natural_number_(denominator) {}

    std::unique_ptr<RationalNumber> add(RationalNumber& other) const;
    std::unique_ptr<RationalNumber> subtract(RationalNumber& other) const;
    std::unique_ptr<RationalNumber> multiply(RationalNumber& other) const;
    std::unique_ptr<RationalNumber> divide(RationalNumber& other) const;
    std::unique_ptr<RationalNumber> convert_integer_to_fraction(IntegerNumber& other) const;
    std::unique_ptr<IntegerNumber> convert_reduced_fraction_to_integer() const;
    std::unique_ptr<RationalNumber> reduce_fraction() const;
    bool is_integer() const;
};



#endif