// integer_numbers.cpp
#include "integer_numbers.h"

int8_t IntegerNumber::is_number_positive() const { // POZ_Z_D Аненков Иван
    if (this->get_number() == 0) {
        return 0;
    }
    return (this->get_sign() == SignNumber::POSITIVE) ? 2 : 1;
}

std::unique_ptr<IntegerNumber> IntegerNumber::add(IntegerNumber& other) const { // ADD_ZZ_Z Аненков Иван
    int8_t sign1 = this->is_number_positive();
    int8_t sign2 = other.is_number_positive();

    auto abs_this = this->get_absolute_value();       // Returns std::unique_ptr<NaturalNumber>
    auto abs_other = other.get_absolute_value();      // Returns std::unique_ptr<NaturalNumber>

    if (sign1 == sign2) {
        auto abs_sum = abs_this->add(*abs_other);     // Add absolute values
        auto result = converting_natural_to_integer(*abs_sum);
        if (sign1 == 1) {
            // Negative result
            return result->change_sign();
        } else {
            return result;
        }
    } else {
        uint8_t compare_result = abs_this->compare(*abs_other);
        if (compare_result == 0) {
            // Result is zero
            return std::make_unique<IntegerNumber>(0);
        } else if (compare_result == 2) {
            // abs_this > abs_other
            auto abs_diff = abs_this->subtract(*abs_other);
            auto result = converting_natural_to_integer(*abs_diff);
            if (sign1 == 1) {
                // Negative result
                return result->change_sign();
            } else {
                return result;
            }
        } else {
            // abs_other > abs_this
            auto abs_diff = abs_other->subtract(*abs_this);
            auto result = converting_natural_to_integer(*abs_diff);
            if (sign2 == 1) {
                // Negative result
                return result->change_sign();
            } else {
                return result;
            }
        }
    }
}

std::unique_ptr<IntegerNumber> IntegerNumber::subtract(IntegerNumber& other) const { // SUB_ZZ_Z Аненков Иван
    auto negated_other = other.change_sign();
    return this->add(*negated_other);
}

std::unique_ptr<IntegerNumber> IntegerNumber::multiply(IntegerNumber& other) const { // MUL_ZZ_Z Аненков Иван
    auto abs_this = this->get_absolute_value();
    auto abs_other = other.get_absolute_value();

    auto abs_result = abs_this->multiply(*abs_other);

    int8_t sign1 = this->is_number_positive();
    int8_t sign2 = other.is_number_positive();

    auto result = converting_natural_to_integer(*abs_result);

    if ((sign1 == 1 && sign2 == 2) || (sign1 == 2 && sign2 == 1)) {
        // Negative result
        return result->change_sign();
    } else {
        return result;
    }
}

std::unique_ptr<NaturalNumber> IntegerNumber::get_absolute_value() const { // ABS_Z_Z Черныш Максим
    int64_t value = this->get_number();
    if (value < 0) {
        value = -value;
    }
    return std::make_unique<NaturalNumber>(value);
}

std::unique_ptr<IntegerNumber> IntegerNumber::change_sign() const { // MUL_ZM_Z Беляев Максим 
    return std::make_unique<IntegerNumber>(-this->get_number());
}

std::unique_ptr<IntegerNumber> IntegerNumber::converting_natural_to_integer(NaturalNumber& other) { // TRANS_N_Z Черныш Максим
    return std::make_unique<IntegerNumber>(other.get_number());
}

std::unique_ptr<NaturalNumber> IntegerNumber::converting_positive_integer_to_natural() const { // TRANS_Z_N Земерова Светлана
    if (this->is_number_positive() == 2) {
        return std::make_unique<NaturalNumber>(this->get_number());
    } else {
        throw std::invalid_argument("Cannot convert negative integer to natural number!");
    }
}

std::unique_ptr<IntegerNumber> IntegerNumber::calculating_quotient(IntegerNumber& other) const { // DIV_ZZ_Z Лысиков Михаил
    if (other.is_number_positive() == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    int8_t sign1 = this->is_number_positive();
    int8_t sign2 = other.is_number_positive();

    auto abs_this = this->get_absolute_value();
    auto abs_other = other.get_absolute_value();

    auto quotient = abs_this->division_numbers_with_remainder(*abs_other);

    auto result = converting_natural_to_integer(*quotient);

    if ((sign1 == 1 && sign2 == 2) || (sign1 == 2 && sign2 == 1)) {
        // Negative result
        return result->change_sign();
    } else {
        return result;
    }
}

std::unique_ptr<IntegerNumber> IntegerNumber::calculating_remainder_after_division(IntegerNumber& other) const { // MOD_ZZ_Z Земерова Светлана
    if (other.is_number_positive() == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    auto quotient = this->calculating_quotient(other);
    auto product = quotient->multiply(other);
    auto remainder = this->subtract(*product);

    return remainder;
}
