#include "processing_input.h"

std::vector<uint8_t> split_number_into_digits(int64_t input_number) {

    std::vector<uint8_t> digits;

    int64_t temp = abs(input_number);

    do {
        digits.push_back(temp % 10);
        temp /= 10;
    } while (temp != 0);

    std::reverse(digits.begin(), digits.end());

    return digits;

}


std::vector<uint8_t> reverse_digits_in_vector(std::vector<uint8_t> digits_of_number) {

    std::reverse(digits_of_number.begin(), digits_of_number.end());
    return digits_of_number;

}


SignNumber determining_sign_number(int64_t input_number) {

    if (input_number < 0) {
        return SignNumber::NEGATIVE;
    } else if (input_number == 0) {
        return SignNumber::ZERO;
    } else {
        return SignNumber::POSITIVE;
    }

}
int64_t gather_digits_into_number(std::vector<uint8_t> digits_of_number){
    int64_t result = 0;
    for (size_t i = 0; i < digits_of_number.size(); ++i){
        result += digits_of_number[i] * std::pow(10, i); 
    }
    return result;
}