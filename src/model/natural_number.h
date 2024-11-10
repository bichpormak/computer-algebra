#ifndef NATURAL_NUMBER_H
#define NATURAL_NUMBER_H

#include <stdexcept>

#include "number.h"

class NaturalNumber : public Number {
public:
    NaturalNumber(int64_t input_number) : Number(input_number) {
        if (get_sign() != SignNumber::POSITIVE) {
            throw std::invalid_argument("Natural number must be positive");
        }
    }

public:
    std::unique_ptr<Number> add(Number& other) const override;
    std::unique_ptr<Number> subtract(Number& other) const override;
    std::unique_ptr<Number> multiply(Number& other) const override;
    std::unique_ptr<Number> divide(Number& other) const override;
    std::unique_ptr<Number> get_absolute_value() const override;
    std::unique_ptr<Number> change_sign() const override;

    uint8_t compare(NaturalNumber& other) const;
    bool is_zero() const;
    std::unique_ptr<Number> add_one() const;
    std::unique_ptr<Number> multiply_by_digit(int64_t digit) const;
    std::unique_ptr<Number> multiply_by_ten_in_power(int64_t power) const;
    std::unique_ptr<Number> subtract_with_multiply_digit(NaturalNumber& other, int64_t digit) const;
    std::unique_ptr<Number> get_first_digit_after_division_number_on_ten_in_power(int64_t digit) const;
    std::unique_ptr<Number> division_numbers_with_remainder(NaturalNumber& other) const;
    std::unique_ptr<Number> calculating_remainder_after_division(NaturalNumber& other) const;
    std::unique_ptr<Number> calculate_gcd(NaturalNumber& other) const;
    std::unique_ptr<Number> calculate_lcm(NaturalNumber& other);
};


#endif