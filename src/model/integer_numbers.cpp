#include "integer_numbers.h"

std::unique_ptr<Number> IntegerNumber::add(Number& other) const {

    return nullptr;
}

std::unique_ptr<Number> IntegerNumber::subtract(Number& other) const {

    int64_t result = this->get_number() - other.get_number();

    return std::make_unique<IntegerNumber>(result);
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
    if (get_number() > 0) {
        return 2;

    } else if (get_number() == 0) {
        return 0; 

    } else {
        return 1; 
    }
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
