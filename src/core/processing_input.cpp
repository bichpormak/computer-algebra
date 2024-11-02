#include "processing_input.h"

std::vector<int8_t> split_number_into_digits(int64_t input_number) {

    std::vector<int8_t> digits;

    int64_t temp = abs(input_number);

    do {
        digits.push_back(temp % 10);
        temp /= 10;
    } while (temp != 0);

    std::reverse(digits.begin(), digits.end());

    return digits;

}


std::vector<int8_t> reverse_digits_in_vector(std::vector<int8_t> digits_of_number) {
    std::reverse(digits_of_number.begin(), digits_of_number.end());
    return digits_of_number;
}


bool is_positive_number(int64_t input_number) {
    return true ? input_number >= 0 : false;
}
