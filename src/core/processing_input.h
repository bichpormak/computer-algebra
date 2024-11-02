#ifndef DIVIDING_NUMBER_INTO_DIGITS_H
#define DIVIDING_NUMBER_INTO_DIGITS_H

#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>

std::vector<int8_t> split_number_into_digits(int64_t input_number);
std::vector<int8_t> reverse_digits_in_vector(std::vector<int8_t> digits_of_number);
bool is_positive_number(int64_t input_number);

#endif