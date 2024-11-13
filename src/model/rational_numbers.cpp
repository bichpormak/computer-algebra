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
    auto reduced_fraction = this;

    if (reduced_fraction->denominator_natural_number_.get_number() == 1) {
        return std::make_unique<RationalNumber>(
            reduced_fraction->numerator_integer_number_,
            NaturalNumber(1)
        );
    } else {
        return nullptr;
    }
}

std::unique_ptr<RationalNumber> RationalNumber::reduce_fraction() const {

    return nullptr;
}

bool RationalNumber::is_reduced() const {

    return false;
}
