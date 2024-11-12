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

    uint8_t compare(NaturalNumber& other) const;
    bool is_zero() const;

    std::unique_ptr<NaturalNumber> add(NaturalNumber& other) const;
    std::unique_ptr<NaturalNumber> subtract(NaturalNumber& other) const;
    std::unique_ptr<NaturalNumber> multiply(NaturalNumber& other) const;
    std::unique_ptr<NaturalNumber> add_one() const;
    std::unique_ptr<NaturalNumber> multiply_by_digit(int64_t digit) const;
    std::unique_ptr<NaturalNumber> multiply_by_ten_in_power(int64_t power) const;
    std::unique_ptr<NaturalNumber> subtract_with_multiply_digit(NaturalNumber& other, int64_t digit) const;
    std::unique_ptr<NaturalNumber> get_first_digit_after_division_number_on_ten_in_power(int64_t digit) const;
    std::unique_ptr<NaturalNumber> division_numbers_with_remainder(NaturalNumber& other) const;
    std::unique_ptr<NaturalNumber> calculating_remainder_after_division(NaturalNumber& other) const;
    std::unique_ptr<NaturalNumber> calculate_gcd(NaturalNumber& other) const;
    std::unique_ptr<NaturalNumber> calculate_lcm(NaturalNumber& other);
};


#endif