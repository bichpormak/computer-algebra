// integer_numbers.cpp
#include "integer_numbers.h"

int8_t IntegerNumber::is_number_positive() const {
    if (this->get_number() == 0) {
        return 0;
    }
    return (this->get_sign() == SignNumber::POSITIVE) ? 2 : 1;
}

std::unique_ptr<IntegerNumber> IntegerNumber::add(IntegerNumber& other) const {
    int8_t sign1 = this->is_number_positive();
    int8_t sign2 = other.is_number_positive();

    auto abs_this = this->get_absolute_value();       // Returns std::unique_ptr<NaturalNumber>
    auto abs_other = other.get_absolute_value();      // Returns std::unique_ptr<NaturalNumber>

    if (sign1 == sign2) {
        // Both have the same sign
        std::unique_ptr<NaturalNumber> abs_sum = abs_this->add(*abs_other);     // Add absolute values
        std::unique_ptr<IntegerNumber> result = converting_natural_to_integer(*abs_sum);
        if (sign1 == 1) {
            // Negative result
            return result->change_sign();
        } else {
            return result;
        }
    } else {
        // Different signs, perform subtraction
        uint8_t compare_result = abs_this->compare(*abs_other);
        if (compare_result == 0) {
            // Result is zero
            return std::make_unique<IntegerNumber>(0);
        } else if (compare_result == 2) {
            // abs_this > abs_other
            std::unique_ptr<NaturalNumber> abs_diff = abs_this->subtract(*abs_other);
            std::unique_ptr<IntegerNumber> result = converting_natural_to_integer(*abs_diff);
            if (sign1 == 1) {
                // Negative result
                return result->change_sign();
            } else {
                return result;
            }
        } else {
            // abs_other > abs_this
            std::unique_ptr<NaturalNumber> abs_diff = abs_other->subtract(*abs_this);
            std::unique_ptr<IntegerNumber> result = converting_natural_to_integer(*abs_diff);
            if (sign2 == 1) {
                // Negative result
                return result->change_sign();
            } else {
                return result;
            }
        }
    }
}

std::unique_ptr<IntegerNumber> IntegerNumber::subtract(IntegerNumber& other) const {
    std::unique_ptr<IntegerNumber> negated_other = other.change_sign();
    return this->add(*negated_other);
}

std::unique_ptr<IntegerNumber> IntegerNumber::multiply(IntegerNumber& other) const {
    auto abs_this = this->get_absolute_value();
    auto abs_other = other.get_absolute_value();

    std::unique_ptr<NaturalNumber> abs_result = abs_this->multiply(*abs_other);

    int8_t sign1 = this->is_number_positive();
    int8_t sign2 = other.is_number_positive();

    std::unique_ptr<IntegerNumber> result = converting_natural_to_integer(*abs_result);

    if ((sign1 == 1 && sign2 == 2) || (sign1 == 2 && sign2 == 1)) {
        // Negative result
        return result->change_sign();
    } else {
        // Positive result
        return result;
    }
}

std::unique_ptr<NaturalNumber> IntegerNumber::get_absolute_value() const {
    int64_t value = this->get_number();
    if (value < 0) {
        value = -value;
    }
    return std::make_unique<NaturalNumber>(value);
}

std::unique_ptr<IntegerNumber> IntegerNumber::change_sign() const {
    return std::make_unique<IntegerNumber>(-this->get_number());
}

std::unique_ptr<IntegerNumber> IntegerNumber::converting_natural_to_integer(NaturalNumber& other) const {
    return std::make_unique<IntegerNumber>(other.get_number());
}

std::unique_ptr<NaturalNumber> IntegerNumber::converting_positive_integer_to_natural() const {
    if (this->is_number_positive() == 2) {
        return std::make_unique<NaturalNumber>(this->get_number());
    } else {
        throw std::invalid_argument("Cannot convert negative integer to natural number!");
    }
}

std::unique_ptr<IntegerNumber> IntegerNumber::calculating_quotient(IntegerNumber& other) const {
    if (other.get_number() == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    int8_t sign1 = this->is_number_positive();
    int8_t sign2 = other.is_number_positive();

    // Determine the sign of the quotient
    bool negative = (sign1 != sign2);

    // Get absolute values
    std::unique_ptr<NaturalNumber> abs_this = this->get_absolute_value();
    std::unique_ptr<NaturalNumber> abs_other = other.get_absolute_value();

    // Perform division: abs_this / abs_other
    std::unique_ptr<NaturalNumber> quotient_natural = abs_this->division_numbers_with_remainder(*abs_other);

    // Convert quotient to IntegerNumber
    std::unique_ptr<IntegerNumber> quotient = converting_natural_to_integer(*quotient_natural);

    // Set the correct sign
    if (negative) {
        quotient = quotient->change_sign();
    }

    return quotient;
}

std::unique_ptr<IntegerNumber> IntegerNumber::calculating_remainder_after_division(IntegerNumber& other) const {
    if (other.is_number_positive() == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    std::unique_ptr<IntegerNumber> quotient = this->calculating_quotient(other);
    std::unique_ptr<IntegerNumber> product = quotient->multiply(other);
    std::unique_ptr<IntegerNumber> remainder = this->subtract(*product);

    return remainder;
}
