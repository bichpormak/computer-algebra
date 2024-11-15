#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <map>
#include <memory>
#include "rational_numbers.h"
#include "natural_number.h"

class Polynomial {
private:
    std::map<std::unique_ptr<int>, std::unique_ptr<RationalNumber>> coefficients_;

public:
    Polynomial(const Polynomial& other) {
        for (const auto& [key, value] : other.coefficients_) {
            coefficients_[std::make_unique<int>(*key)] = std::make_unique<RationalNumber>(*value);
        }
    }

    Polynomial(std::map<std::unique_ptr<int>, std::unique_ptr<RationalNumber>>&& coefficients)
            : coefficients_(std::move(coefficients)) {}

    Polynomial& operator=(const Polynomial& other) {
        if (this == &other) return *this;

        coefficients_.clear();
        for (const auto& [key, value] : other.coefficients_) {
            coefficients_[std::make_unique<int>(*key)] = std::make_unique<RationalNumber>(*value);
        }
        return *this;
    }


    Polynomial& operator=(Polynomial&& other) noexcept {
        if (this == &other) return *this;

        coefficients_ = std::move(other.coefficients_);
        return *this;
    }

    std::unique_ptr<Polynomial> add(const Polynomial& other) const;
    std::unique_ptr<Polynomial> subtract(const Polynomial& other) const;
    std::unique_ptr<Polynomial> multiply_by_rational(const RationalNumber& scalar) const;
    std::unique_ptr<Polynomial> multiply_by_x_power(int k) const;
    const RationalNumber& leading_coefficient() const;
    int degree() const;
    void normalize();
    std::unique_ptr<Polynomial> multiply(const Polynomial& other) const;
    std::unique_ptr<Polynomial> divide(const Polynomial& divisor, std::unique_ptr<Polynomial>& remainder) const;
    std::unique_ptr<Polynomial> remainder(const Polynomial& divisor) const;
    static std::unique_ptr<Polynomial> gcd(const Polynomial& p1, const Polynomial& p2);
    std::unique_ptr<Polynomial> derivative() const;
    std::unique_ptr<Polynomial> simplify_roots() const;
};

#endif
