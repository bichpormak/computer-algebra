#include "polynomial.h"
#include <stdexcept>


// Add two polynomials
std::unique_ptr<Polynomial> Polynomial::add(const Polynomial& other) const {
    auto result = std::make_unique<Polynomial>(coefficients_);
    for (const auto& [key, value] : other.coefficients_) {
        if (result->coefficients_.find(key) != result->coefficients_.end()) {
            result->coefficients_[key] = result->coefficients_[key] + value;
        } else {
            result->coefficients_[key] = value;
        }
    }
    result->normalize();
    return result;
}

// Subtract two polynomials
std::unique_ptr<Polynomial> Polynomial::subtract(const Polynomial& other) const {
    auto result = std::make_unique<Polynomial>(coefficients_);
    for (const auto& [key, value] : other.coefficients_) {
        if (result->coefficients_.find(key) != result->coefficients_.end()) {
            result->coefficients_[key] = result->coefficients_[key] - value;
        } else {
            // Assuming RationalNumber has a constructor that accepts an integer
            result->coefficients_[key] = RationalNumber(0) - value;
        }
    }
    result->normalize();
    return result;
}

// Multiply polynomial by a rational scalar
std::unique_ptr<Polynomial> Polynomial::multiply_by_rational(const RationalNumber& scalar) const {
    auto result = std::make_unique<Polynomial>();
    for (const auto& [key, value] : coefficients_) {
        RationalNumber new_coeff = value * scalar;
        // Assuming RationalNumber has operator== overloaded
        if (!(new_coeff == RationalNumber(0))) {
            result->coefficients_[key] = new_coeff;
        }
    }
    return result;
}

// Multiply polynomial by x^k
std::unique_ptr<Polynomial> Polynomial::multiply_by_x_power(int k) const {
    auto result = std::make_unique<Polynomial>();
    for (const auto& [key, value] : coefficients_) {
        result->coefficients_[key + k] = value;
    }
    return result;
}

// Multiply two polynomials
std::unique_ptr<Polynomial> Polynomial::multiply(const Polynomial& other) const {
    auto result = std::make_unique<Polynomial>();
    for (const auto& [key1, value1] : coefficients_) {
        for (const auto& [key2, value2] : other.coefficients_) {
            int new_key = key1 + key2;
            RationalNumber new_value = value1 * value2;
            if (result->coefficients_.find(new_key) != result->coefficients_.end()) {
                result->coefficients_[new_key] = result->coefficients_[new_key] + new_value;
            } else {
                result->coefficients_[new_key] = new_value;
            }
        }
    }
    result->normalize();
    return result;
}

// Get the leading coefficient
const RationalNumber& Polynomial::leading_coefficient() const {
    if (coefficients_.empty()) {
        throw std::runtime_error("Polynomial has no terms");
    }
    return coefficients_.rbegin()->second;
}

// Get the degree of the polynomial
int Polynomial::degree() const {
    if (coefficients_.empty()) {
        throw std::runtime_error("Polynomial has no terms");
    }
    return coefficients_.rbegin()->first;
}

// Normalize the polynomial by removing zero coefficients
void Polynomial::normalize() {
    for (auto it = coefficients_.begin(); it != coefficients_.end(); ) {
        // Assuming RationalNumber has operator== overloaded
        if (it->second == RationalNumber(0)) {
            it = coefficients_.erase(it);
        } else {
            ++it;
        }
    }
}

// Compute the derivative of the polynomial
std::unique_ptr<Polynomial> Polynomial::derivative() const {
    std::map<int, RationalNumber> derivative_coeffs;
    for (const auto& [degree, coeff] : coefficients_) {
        if (degree == 0) continue;
        // Assuming RationalNumber can be constructed from an integer
        RationalNumber degree_rational = RationalNumber(degree);
        RationalNumber new_coeff = coeff * degree_rational;
        derivative_coeffs[degree - 1] = new_coeff;
    }
    return std::make_unique<Polynomial>(derivative_coeffs);
}

// Divide this polynomial by another, returning the quotient and setting the remainder
std::unique_ptr<Polynomial> Polynomial::divide(const Polynomial& divisor, std::unique_ptr<Polynomial>& remainder) const {
    if (divisor.coefficients_.empty()) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    Polynomial dividend(*this);
    auto quotient = std::make_unique<Polynomial>();

    while (!dividend.coefficients_.empty() && dividend.degree() >= divisor.degree()) {
        int deg_diff = dividend.degree() - divisor.degree();
        // Assuming RationalNumber has operator/ overloaded
        RationalNumber coeff_ratio = dividend.leading_coefficient() / divisor.leading_coefficient();

        // Create a monomial: coeff_ratio * x^deg_diff
        std::map<int, RationalNumber> monomial_coeffs;
        monomial_coeffs[deg_diff] = coeff_ratio;
        Polynomial monomial(monomial_coeffs);

        // Add monomial to quotient
        if (quotient->coefficients_.find(deg_diff) != quotient->coefficients_.end()) {
            quotient->coefficients_[deg_diff] = quotient->coefficients_[deg_diff] + coeff_ratio;
        } else {
            quotient->coefficients_[deg_diff] = coeff_ratio;
        }

        // Subtract (divisor * monomial) from dividend
        auto product = divisor.multiply(monomial);
        dividend = *dividend.subtract(*product);
    }

    quotient->normalize();
    remainder = std::make_unique<Polynomial>(dividend);
    return quotient;
}

// Compute the remainder of division
std::unique_ptr<Polynomial> Polynomial::remainder(const Polynomial& divisor) const {
    std::unique_ptr<Polynomial> remainder;
    this->divide(divisor, remainder);
    return remainder;
}

// Compute the GCD of two polynomials
std::unique_ptr<Polynomial> Polynomial::gcd(const Polynomial& p1, const Polynomial& p2) {
    Polynomial a = p1;
    Polynomial b = p2;

    while (!b.coefficients_.empty()) {
        const auto r = *a.remainder(b);
        a = b;
        b = r;
    }

    a.normalize();
    return std::make_unique<Polynomial>(a);
}

// Simplify roots by dividing by GCD with derivative
std::unique_ptr<Polynomial> Polynomial::simplify_roots() const {
    if (coefficients_.empty()) {
        return std::make_unique<Polynomial>(*this);
    }

    auto derivative_poly = this->derivative();
    auto gcd_poly = Polynomial::gcd(*this, *derivative_poly);

    // Если НОД — константа, возвращаем исходный многочлен
    if (gcd_poly->degree() == 0) {
        return std::make_unique<Polynomial>(*this);
    }

    std::unique_ptr<Polynomial> remainder = nullptr;
    auto simplified_poly = this->divide(*gcd_poly, remainder);

    return simplified_poly;
}