// integer_numbers.h
#ifndef INTEGER_NUMBERS_H
#define INTEGER_NUMBERS_H

#include "natural_number.h"

class IntegerNumber : public Number {
public:
    IntegerNumber(int64_t input_number) : Number(input_number) {}

public:
    std::unique_ptr<IntegerNumber> add(IntegerNumber& other) const;
    std::unique_ptr<IntegerNumber> subtract(IntegerNumber& other) const;
    std::unique_ptr<IntegerNumber> multiply(IntegerNumber& other) const;
    std::unique_ptr<NaturalNumber> get_absolute_value() const;
    std::unique_ptr<IntegerNumber> change_sign() const;
    int8_t is_number_positive() const;
    static std::unique_ptr<IntegerNumber> converting_natural_to_integer(NaturalNumber& other);
    std::unique_ptr<NaturalNumber> converting_positive_integer_to_natural() const;
    std::unique_ptr<IntegerNumber> calculating_quotient(IntegerNumber& other) const;
    std::unique_ptr<IntegerNumber> calculating_remainder_after_division(IntegerNumber& other) const;
};

#endif
