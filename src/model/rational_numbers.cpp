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

std::unique_ptr<RationalNumber> RationalNumber::convert_reduced_fraction_to_integer() const {

    return nullptr;
}

std::unique_ptr<RationalNumber> RationalNumber::reduce_fraction() const {
    std::unique_ptr<NaturalNumber> num1 = numerator_integer_number_.get_absolute_value();
    NaturalNumber num2 = denominator_natural_number_;
    std::unique_ptr<NaturalNumber> gcd = num1->calculate_gcd(num2);
    std::unique_ptr<NaturalNumber> numerator = num1->division_numbers_with_remainder(*gcd);
    std::unique_ptr<NaturalNumber> denominator = num2.division_numbers_with_remainder(*gcd);
    return std::make_unique<RationalNumber>(*numerator, *denominator);
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