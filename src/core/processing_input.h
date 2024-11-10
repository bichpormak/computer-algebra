#ifndef DIVIDING_NUMBER_INTO_DIGITS_H
#define DIVIDING_NUMBER_INTO_DIGITS_H

#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>

enum class SignNumber {
    POSITIVE,
    NEGATIVE,
    ZERO
};


std::vector<uint8_t> split_number_into_digits(int64_t input_number);
std::vector<uint8_t> reverse_digits_in_vector(std::vector<uint8_t> digits_of_number);
SignNumber determining_sign_number(int64_t input_number);
int64_t gather_digits_into_number(std::vector<uint8_t> digits_of_number);
#endif