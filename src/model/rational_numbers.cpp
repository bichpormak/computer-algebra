#include "rational_numbers.h"

std::unique_ptr<RationalNumber> RationalNumber::add(RationalNumber &other) const {

    return nullptr;
}

std::unique_ptr<RationalNumber> RationalNumber::subtract(RationalNumber &other) const {

    return nullptr;
}

std::unique_ptr<RationalNumber> RationalNumber::multiply(RationalNumber &other) const {

    return nullptr;
}

std::unique_ptr<RationalNumber> RationalNumber::divide(RationalNumber& other) const {

    return nullptr;
}

std::unique_ptr<RationalNumber> RationalNumber::convert_integer_to_fraction() const {

    return nullptr;
}

std::unique_ptr<IntegerNumber> RationalNumber::convert_reduced_fraction_to_integer() const {
    return std::make_unique<IntegerNumber>(this->numerator_integer_number_);
}

std::unique_ptr<RationalNumber> RationalNumber::reduce_fraction() const {
    return nullptr;
}

bool RationalNumber::is_integer() const {
    auto reduced_fraction = this->reduce_fraction();
    if (reduced_fraction->denominator_natural_number_.get_number() == 1){
        return true;
    }
    else{
        return false;
    }
}
