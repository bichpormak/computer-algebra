#include "integer_numbers.h"


int8_t IntegerNumber::is_number_positive() const {
    if (this->get_number() == 0) {
        return 0;  
    }
    return (this->get_sign() == SignNumber::POSITIVE) ? 2 : 1;
}

std::unique_ptr<Number> IntegerNumber::add(Number& other) const {

    auto* other_integer = dynamic_cast<IntegerNumber*>(&other);
    if (!other_integer) {
        throw std::invalid_argument("Incompatible number type for addition.");
    }

    int8_t sign1 = this->is_number_positive();
    int8_t sign2 = other_integer->is_number_positive();

    if (sign1 == sign2) {
        auto abs_sum = this->get_absolute_value()->add(*other_integer->get_absolute_value());
        return (sign1 == 1) ? std::move(abs_sum->change_sign()) : std::move(abs_sum);  
    }


    auto abs_this = dynamic_cast<NaturalNumber*>(this->get_absolute_value().get());
    auto abs_other = dynamic_cast<NaturalNumber*>(other_integer->get_absolute_value().get());

    int compare_result = abs_this->compare(*abs_other);
    
    std::unique_ptr<Number> result;
    if (compare_result == 0) {
        result = std::make_unique<IntegerNumber>(0);
    } else if (compare_result > 0) {
        result = abs_this->subtract(*abs_other); 
        if (sign1 == 1) result = std::move(result->change_sign()); 
    } else {
        result = abs_other->subtract(*abs_this); 
        if (sign2 == 1) result = std::move(result->change_sign()); 
    }

    return std::move(result);
}


std::unique_ptr<Number> IntegerNumber::subtract(Number& other) const {
    auto negated_other = other.change_sign();
    return this->add(*negated_other);
}

std::unique_ptr<Number> IntegerNumber::multiply(Number& other) const {
    auto* other_integer = dynamic_cast<IntegerNumber*>(&other);
    if (!other_integer) {
        throw std::invalid_argument("Incompatible number type for multiplication.");
    }

    auto abs_this = dynamic_cast<NaturalNumber*>(this->get_absolute_value().get());
    auto abs_other = dynamic_cast<NaturalNumber*>(other_integer->get_absolute_value().get());

    auto abs_result = abs_this->multiply(*abs_other);  

    int8_t sign1 = this->is_number_positive();
    int8_t sign2 = other_integer->is_number_positive();

    if (sign1 == sign2) {
        return std::move(abs_result);
    } else {
        return std::move(abs_result->change_sign());
    }
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
