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


std::unique_ptr<IntegerNumber> IntegerNumber::subtract(IntegerNumber& other) const {
    return nullptr;
}

std::unique_ptr<IntegerNumber> IntegerNumber::multiply(IntegerNumber& other) const {
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

std::unique_ptr<IntegerNumber> IntegerNumber::get_absolute_value() const {

    return nullptr;
}

std::unique_ptr<IntegerNumber> IntegerNumber::change_sign() const {
    if(this->is_number_positive() == 2){
        return std::make_unique<IntegerNumber>(IntegerNumber(-(this->get_number())));
    }
    else{
        return std::make_unique<IntegerNumber>(IntegerNumber(this->get_number()));
    }
    return nullptr;
}

std::unique_ptr<IntegerNumber> IntegerNumber::converting_natural_to_integer() const {

    return nullptr;
}

std::unique_ptr<NaturalNumber> IntegerNumber::converting_positive_integer_to_natural() const {
    if (this->is_number_positive() == 2){
        return std::make_unique<NaturalNumber>(NaturalNumber(this->get_number()));
    }
    else{
        throw std::invalid_argument("Invalid number!\n");
    }
 
}

std::unique_ptr<IntegerNumber> IntegerNumber::calculating_quotient(IntegerNumber& other) const {
    if (other.is_number_positive() == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    int8_t quotient_sign = this->is_number_positive() + other.is_number_positive();
    std::unique_ptr<IntegerNumber> num1 = this->get_absolute_value();
    std::unique_ptr<IntegerNumber> num2 = other.get_absolute_value();

    std::unique_ptr<NaturalNumber> natural_num1 = num1->converting_positive_integer_to_natural();
    std::unique_ptr<NaturalNumber> natural_num2 = num2->converting_positive_integer_to_natural();

    std::unique_ptr<NaturalNumber> quotient = natural_num1->division_numbers_with_remainder(*natural_num2);

    if (quotient_sign == 4 || quotient_sign == 2){
        return std::make_unique<IntegerNumber>(IntegerNumber(quotient->get_number()));
    }
    else if (quotient_sign == 3){
        return std::make_unique<IntegerNumber>(IntegerNumber(quotient->get_number()).change_sign());
    }
    else{
        return std::make_unique<IntegerNumber>(0);
    }
}

std::unique_ptr<IntegerNumber> IntegerNumber::calculating_remainder_after_division(IntegerNumber& other) const {
    auto num1 = this->get_digits_of_number();
    auto num2 = other.get_digits_of_number();

    if (num1.size() < num2.size()){
        return std::make_unique<IntegerNumber>(IntegerNumber(this->get_number()));
    }
    auto quotient = this->calculating_quotient(other);
    
    auto product = quotient->multiply(other);

    auto remainder = this->subtract(*product);

    return std::make_unique<IntegerNumber>(*remainder);
}