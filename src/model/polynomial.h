#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <map>
#include <memory>
#include "rational_numbers.h"

class Polynomial {

private:
    std::map<int, RationalNumber> coefficients_;

public:
    Polynomial() = default;

    Polynomial(const Polynomial& other) : coefficients_(other.coefficients_) {}

    Polynomial(std::map<int, RationalNumber>&& coefficients)
            : coefficients_(std::move(coefficients)) {}

    Polynomial(const std::map<int, RationalNumber>& coeffs)
    : coefficients_(coeffs) {}


    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            coefficients_ = other.coefficients_;
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
