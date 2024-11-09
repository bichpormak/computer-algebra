#include "integer_numbers.h"


int8_t IntegerNumber::compare_integer(Number& other) const { // = Z2
    const std::vector<uint8_t>& digits1 = this->get_digits_of_number();
    const std::vector<uint8_t>& digits2 = other.get_digits_of_number();

    bool is_equal = (digits1.size() == digits2.size());
    for (size_t i = 0; is_equal && i < digits1.size(); ++i) {
        if (digits1[i] != digits2[i]) {
            is_equal = false;
        }
    }

    if (is_equal) {
        return 0;  
    }


    bool is_larger_this = (digits1.size() != digits2.size());
    if (!is_larger_this) {
        for (size_t i = 0; i < digits1.size(); ++i) {
            if (digits1[i] != digits2[i]) {
                is_larger_this = (digits1[i] != 0); 
                break;
            }
        }
    }

    const std::vector<uint8_t>& larger = is_larger_this ? digits1 : digits2;
    const std::vector<uint8_t>& smaller = is_larger_this ? digits2 : digits1;
    
    std::vector<uint8_t> result_digits;
    bool borrow = false;

    for (size_t i = 0; i < larger.size(); ++i) {
        int digit1 = (i < larger.size()) ? larger[i] : 0;
        int digit2 = (i < smaller.size()) ? smaller[i] : 0;

        if (borrow) {
            if (digit1 == 0) {
                digit1 = 9;
                borrow = true;
            } else {
                digit1 -= 1;
                borrow = false;
            }
        }

        int diff = digit1 - digit2;
        if (diff < 0) {
            diff += 10;
            borrow = true;
        }

        result_digits.push_back(static_cast<uint8_t>(diff));
    }

    while (result_digits.size() > 1 && result_digits.back() == 0) {
        result_digits.pop_back();
    }

    return is_larger_this ? 2 : 1;  
}

std::unique_ptr<Number> IntegerNumber::add(Number& other) const {
    auto* other_integer = dynamic_cast<IntegerNumber*>(&other);
    if (!other_integer) {
        throw std::invalid_argument("Incompatible number type for addition.");
    }

    int sign1 = this->is_number_positive();
    int sign2 = other_integer->is_number_positive();

    if (sign1 == 2 && sign2 == 2) {
        return this->add(other);
    }

    if (sign1 == 1 && sign2 == 1) {
        auto abs_result = this->get_absolute_value()->add(*other_integer->get_absolute_value());
        return abs_result->change_sign();
    }

    auto abs_this = dynamic_cast<IntegerNumber*>(this->get_absolute_value().get());
    auto abs_other = dynamic_cast<IntegerNumber*>(other_integer->get_absolute_value().get());
    
    if (!abs_this || !abs_other) {
        throw std::invalid_argument("Failed to obtain absolute values as IntegerNumber instances.");
    }

    int compare_result = abs_this->compare_integer(*abs_other);
    if (compare_result == 0) {
        return std::make_unique<IntegerNumber>(0);
    } else if (compare_result == 1) {
        if (sign1 == 2) {
            return abs_this->subtract(*abs_other);  
        } else {
            auto result = abs_this->subtract(*abs_other);
            return result->change_sign();  
        }
    } else {
        if (sign2 == 2) {
            return abs_other->subtract(*abs_this);  
        } else {
            auto result = abs_other->subtract(*abs_this);
            return result->change_sign();  
        }
    }
}

std::unique_ptr<Number> IntegerNumber::subtract(Number& other) const {
    auto negated_other = other.change_sign();
    return this->add(*negated_other);
}

std::unique_ptr<Number> IntegerNumber::multiply(Number& other) const {

    return nullptr;
}

std::unique_ptr<Number> IntegerNumber::divide(Number& other) const {

    return nullptr;
}

std::unique_ptr<Number> IntegerNumber::get_absolute_value() const {

    return nullptr;
}

std::unique_ptr<Number> IntegerNumber::change_sign() const {

    return nullptr;
}

int8_t IntegerNumber::is_number_positive() const {

    return 0;

}

std::unique_ptr<Number> IntegerNumber::converting_natural_to_integer() const {

    return nullptr;
}

std::unique_ptr<Number> IntegerNumber::converting_positive_integer_to_natural() const {

    return nullptr;
}

std::unique_ptr<Number> IntegerNumber::calculating_quotient() const {

    return nullptr;
}

std::unique_ptr<Number> IntegerNumber::calculating_remainder_after_division() const {

    return nullptr;
}
