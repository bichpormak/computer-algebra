#include "integer_numbers.h"


int8_t IntegerNumber::is_number_positive() const {
    if (this->get_number() == 0) {
        return 0;
    }
    return (this->get_sign() == SignNumber::POSITIVE) ? 2 : 1;
}

std::unique_ptr<IntegerNumber> IntegerNumber::add(NaturalNumber& other) const {


return nullptr;
}


std::unique_ptr<IntegerNumber> IntegerNumber::subtract(NaturalNumber& other) const {
    return nullptr;
}

std::unique_ptr<IntegerNumber> IntegerNumber::multiply(NaturalNumber& other) const {
    // auto* other_integer = dynamic_cast<IntegerNumber*>(&other);
    // if (!other_integer) {
    //     throw std::invalid_argument("Incompatible number type for multiplication.");
    // }
    //
    // auto abs_this = dynamic_cast<NaturalNumber*>(this->get_absolute_value().get());
    // auto abs_other = dynamic_cast<NaturalNumber*>(other_integer->get_absolute_value().get());
    //
    // auto abs_result = abs_this->multiply(*abs_other);
    //
    // int8_t sign1 = this->is_number_positive();
    // int8_t sign2 = other_integer->is_number_positive();
    //
    // if (sign1 == sign2) {
    //     return abs_result;
    // } else {
    //     return abs_result->change_sign();
    // }

    return nullptr;
}

std::unique_ptr<NaturalNumber> IntegerNumber::get_absolute_value() const {
    if(this->get_sign() == SignNumber::NEGATIVE){
        int64_t value = this->get_number()*(-1);
        return std::make_unique<NaturalNumber>(value);
    }
    return std::make_unique<NaturalNumber>(*this);
}

std::unique_ptr<IntegerNumber> IntegerNumber::change_sign() const {

    return nullptr;
}

std::unique_ptr<IntegerNumber> IntegerNumber::converting_natural_to_integer(NaturalNumber& other) const {
    return std::make_unique<IntegerNumber>(other.get_number());
}

std::unique_ptr<IntegerNumber> IntegerNumber::converting_positive_integer_to_natural() const {

    return nullptr;
}

std::unique_ptr<IntegerNumber> IntegerNumber::calculating_quotient() const {

    return nullptr;
}

std::unique_ptr<IntegerNumber> IntegerNumber::calculating_remainder_after_division() const {

    return nullptr;
}
