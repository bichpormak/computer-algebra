#ifndef INTEGER_NUMBERS_H
#define INTEGER_NUMBERS_H

#include "number.h"
#include "natural_numbers.h"


class IntegerNumber : public Number {
public:
    IntegerNumber(int64_t input_number) : Number(input_number) {}

public:
    std::unique_ptr<Number> add(Number& other) const override;
    std::unique_ptr<Number> subtract(Number& other) const override;
    std::unique_ptr<Number> multiply(Number& other) const override;
    std::unique_ptr<Number> divide(Number& other) const override;
    std::unique_ptr<Number> get_absolute_value(Number& other) const override;
    std::unique_ptr<Number> change_sign() const override;

    int8_t IntegerNumber::compare_integer(Number& other) const;
    int8_t is_number_positive() const;
    std::unique_ptr<Number> converting_natural_to_integer(Number& other) const;
    std::unique_ptr<Number> converting_positive_integer_to_natural() const;
    std::unique_ptr<Number> calculating_quotient() const;
    std::unique_ptr<Number> calculating_remainder_after_division() const;

};



#endif
