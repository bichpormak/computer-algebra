#include "rational_numbers.h"

std::unique_ptr<RationalNumber> RationalNumber::add(RationalNumber &other) const {

    return nullptr;
}

std::unique_ptr<RationalNumber> RationalNumber::subtract(RationalNumber &other) const {

    return nullptr;
}

std::unique_ptr<RationalNumber> RationalNumber::multiply(RationalNumber &other) const {
    auto numerator1 = this->numerator_integer_number_;
    auto numenator2 = other.numerator_integer_number_;

    IntegerNumber denominator1(this->denominator_natural_number_.get_number());
    IntegerNumber denominator2(other.denominator_natural_number_.get_number());
    
    auto result_numerator = numerator1.multiply(numenator2);

    auto result_denominator = denominator1.multiply(denominator2);

    return std::make_unique<RationalNumber>(RationalNumber(result_numerator->get_number(), result_denominator->get_number()));
}

std::unique_ptr<RationalNumber> RationalNumber::divide(RationalNumber& other) const {
    if (other.numerator_integer_number_.get_number() == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    auto numerator1 = this->numerator_integer_number_;
    auto numenator2 = other.numerator_integer_number_;

    IntegerNumber denominator1(this->denominator_natural_number_.get_number());
    IntegerNumber denominator2(other.denominator_natural_number_.get_number());
    
    auto result_numerator = numerator1.multiply(denominator2); // a/b / c/d = a*d / b*c

    auto result_denominator = denominator2.multiply(numenator2);

    return std::make_unique<RationalNumber>(RationalNumber(result_numerator->get_number(), result_denominator->get_number()));
}

std::unique_ptr<RationalNumber> RationalNumber::convert_integer_to_fraction(IntegerNumber& other) const {
    
    return std::make_unique<RationalNumber>(RationalNumber(other, NaturalNumber(1)));
}

std::unique_ptr<IntegerNumber> RationalNumber::convert_reduced_fraction_to_integer() const {
    if (this->is_integer()){
        return std::make_unique<IntegerNumber>(this->numerator_integer_number_);
    }
    else{
        throw std::invalid_argument("Fraction can't be converted!");
    }
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