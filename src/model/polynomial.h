#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <memory>
#include <map>
#include "rational_numbers.h"  
#include "integer_numbers.h"   


struct CompareNaturalNumber {
    bool operator()(const std::unique_ptr<NaturalNumber>& lhs, const std::unique_ptr<NaturalNumber>& rhs) const {
        return lhs->Number::get_number() < rhs->Number::get_number();
    }
};

class Polynomial {
private:
     std::map<std::unique_ptr<NaturalNumber>, std::unique_ptr<RationalNumber>, CompareNaturalNumber> coefficients_;

public:
    Polynomial(const std::map<std::unique_ptr<NaturalNumber>, std::unique_ptr<RationalNumber>, CompareNaturalNumber> coefficients)
        : coefficients_(coefficients) {}

    Polynomial(const Polynomial& other) {
        for (const auto& [key, value] : other.coefficients_) {
            coefficients_[std::make_unique<NaturalNumber>(*key)] = std::make_unique<RationalNumber>(*value);
        }
    }
    
    Polynomial(Polynomial&& other) noexcept
        : coefficients_(std::move(other.coefficients_)) {}

    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            coefficients_.clear();
            for (const auto& [key, value] : other.coefficients_) {
                coefficients_[std::make_unique<NaturalNumber>(*key)] = std::make_unique<RationalNumber>(*value);
            }
        }
        return *this;
    }

    Polynomial& operator=(Polynomial&& other) noexcept {
        if (this != &other) {
            coefficients_ = std::move(other.coefficients_);
        }
        return *this;
    }

    std::unique_ptr<Polynomial> add(const Polynomial& other) const;
    std::unique_ptr<Polynomial> subtract(const Polynomial& other) const;
    std::unique_ptr<Polynomial> multiply_by_rational(const RationalNumber& scalar) const;
    std::unique_ptr<Polynomial> multiply_by_x_power(const NaturalNumber& other) const;
    const RationalNumber& leading_coefficient() const;
    int degree() const;
    void normalize();
    std::unique_ptr<Polynomial> multiply(const Polynomial& other) const;
    std::unique_ptr<Polynomial> divide(const Polynomial& divisor) const;
    std::unique_ptr<Polynomial> remainder(const Polynomial& divisor) const;
    static std::unique_ptr<Polynomial> gcd(const Polynomial& p1, const Polynomial& p2);
    std::unique_ptr<Polynomial> derivative() const;
    std::unique_ptr<Polynomial> simplify_roots() const;

};



#endif