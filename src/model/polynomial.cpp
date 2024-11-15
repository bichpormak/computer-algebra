#include "polynomial.h"

std::unique_ptr<Polynomial> multiply_by_rational(const RationalNumber& scalar) const {
    for (const auto& [key, value] : coefficients_) {
        auto new_coefficient = std::make_unique<RationalNumber>(*value * scalar);
        
        if (new_coefficient != 0) {
            new_coefficients[std::make_unique<NaturalNumber>(*key)] = std::move(new_coefficient);
        }
    }

    return std::make_unique<Polynomial>(new_coefficients);
    }


    std::unique_ptr<Polynomial> multiply_by_x_power(int k) const {

    for (const auto& [key, value] : coefficients_) {
        auto new_key = std::make_unique<NaturalNumber>(*key + k);
        new_coefficients[std::move(new_key)] = std::make_unique<RationalNumber>(*value);
    }

    return std::make_unique<Polynomial>(new_coefficients);
    }


    static std::unique_ptr<Polynomial> gcd(const Polynomial& p1, const Polynomial& p2){

    if (p1.coefficients_.empty() && p2.coefficients_.empty()) {
        return std::make_unique<Polynomial>();
    }

    if (p1.coefficients_.empty()) {
        return std::make_unique<Polynomial>(p2);
    }
    if (p2.coefficients_.empty()) {
        return std::make_unique<Polynomial>(p1);
    }


    std::unique_ptr<Polynomial> remainder = p1.remainder(p2);
    return gcd(p2, *remainder);
    }

