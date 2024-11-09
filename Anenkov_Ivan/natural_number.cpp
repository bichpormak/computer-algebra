#include "natural_number.h"   

std::unique_ptr<Number> NaturalNumber::subtract_with_multiply_digit(NaturalNumber& other, int64_t digit) const {

    std::unique_ptr<Number> multiplied = other.multiply_by_digit(digit);

    std::unique_ptr<Number> result = this->subtract(*multiplied);

    return result;
}
