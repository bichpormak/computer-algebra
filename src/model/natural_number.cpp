#include "natural_number.h"

std::unique_ptr<Number> NaturalNumber::add(Number &other) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::subtract(Number &other) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::multiply(Number &other) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::divide(Number &other) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::get_absolute_value() const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::change_sign() const {

    return nullptr;
}

uint8_t NaturalNumber::compare(NaturalNumber &other) const {

    return 0;
}

bool NaturalNumber::is_zero() const {

    return false;
}

std::unique_ptr<Number> NaturalNumber::add_one() const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::multiply_by_digit(int64_t digit) const {

    return nullptr;
}
std::unique_ptr<Number> NaturalNumber::multiply_by_ten_in_power(int64_t power) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::subtract_with_multiply_digit(NaturalNumber& other, int64_t digit) const {

    return nullptr;
}
std::unique_ptr<Number> NaturalNumber::get_first_digit_after_division_number_on_ten_in_power(int64_t power) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::division_numbers_with_remainder(NaturalNumber& other) const {



    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::calculating_remainder_after_division(NaturalNumber& other) const {

    std::unique_ptr<Number> incomplete_quotient = division_numbers_with_remainder(other);

    return subtract_with_multiply_digit(other, incomplete_quotient->get_number());

}

std::unique_ptr<Number> NaturalNumber::calculate_gcd(NaturalNumber& other) const {

    auto firstNumber = *this;
    auto secondNumber = other;

    while (!secondNumber.is_zero()) {

        std::unique_ptr<Number> remainder_ptr = firstNumber.calculating_remainder_after_division(secondNumber);
        NaturalNumber* remainder = dynamic_cast<NaturalNumber*>(remainder_ptr.get());

        if (firstNumber.compare(secondNumber) == 2) {
            firstNumber = secondNumber;
            secondNumber = *remainder;
        } else if (firstNumber.compare(secondNumber) == 1) {
            secondNumber = firstNumber;
            firstNumber = *remainder;
        } else {
            break;
        }
    }

    return std::make_unique<NaturalNumber>(firstNumber);

}

std::unique_ptr<Number> NaturalNumber::calculate_lcm(NaturalNumber& other) const {

    return nullptr;
}