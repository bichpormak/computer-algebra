#ifndef INTEGER_NUMBERS_H
#define INTEGER_NUMBERS_H

#include "natural_number.h"


class IntegerNumber : public Number {
public:
    IntegerNumber(int64_t input_number) : Number(input_number) {}

public:
    std::unique_ptr<IntegerNumber> add(NaturalNumber& other) const;
    std::unique_ptr<IntegerNumber> subtract(NaturalNumber& other) const;
    std::unique_ptr<IntegerNumber> multiply(NaturalNumber& other) const;
    std::unique_ptr<NaturalNumber> get_absolute_value() const;
    std::unique_ptr<IntegerNumber> change_sign() const;
    int8_t is_number_positive() const;
    std::unique_ptr<IntegerNumber> converting_natural_to_integer(NaturalNumber& other) const;
    std::unique_ptr<IntegerNumber> converting_positive_integer_to_natural() const;
    std::unique_ptr<IntegerNumber> calculating_quotient() const;
    std::unique_ptr<IntegerNumber> calculating_remainder_after_division() const;

};



#endif
