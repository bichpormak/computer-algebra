#include "polynomial.h"

std::unique_ptr<Polynomial> Polynomial::add(const Polynomial& other) const {
    auto result = std::make_unique<Polynomial>();
    result->coefficients_ = coefficients_;

    for (const auto& [key, value] : other.coefficients_) {
        result->coefficients_[key] += value;
    }
    return result;
}

std::unique_ptr<Polynomial> Polynomial::subtract(const Polynomial& other) const {
    auto result = std::make_unique<Polynomial>();
    result->coefficients_ = coefficients_;

    for (const auto& [key, value] : other.coefficients_) {
        result->coefficients_[key] -= value;
    }

    return result;
}

std::unique_ptr<Polynomial> Polynomial::multiply_by_rational(const RationalNumber& scalar) const {
    auto result = std::make_unique<Polynomial>();
    for (const auto& [key, value] : coefficients_) {
        RationalNumber new_coefficient = value * scalar;
        if (new_coefficient != RationalNumber(0)) {
            result->coefficients_[key] = new_coefficient;
        }
    }
    return result;
}

std::unique_ptr<Polynomial> Polynomial::multiply_by_x_power(int k) const {
    auto result = std::make_unique<Polynomial>();
    for (const auto& [key, value] : coefficients_) {
        int new_key = key + k;
        result->coefficients_[new_key] = value;
    }
    return result;
}

std::unique_ptr<Polynomial> Polynomial::multiply(const Polynomial& other) const {
    auto result = std::make_unique<Polynomial>();
    for (const auto& [key1, value1] : coefficients_) {
        for (const auto& [key2, value2] : other.coefficients_) {
            int new_key = key1 + key2;
            RationalNumber new_value = value1 * value2;
            result->coefficients_[new_key] += new_value;
        }
    }
    return result;
}

std::unique_ptr<Polynomial> Polynomial::remainder(const Polynomial& divisor) const {
    std::unique_ptr<Polynomial> remainder;
    this->divide(divisor, remainder);
    return remainder;
}

std::unique_ptr<Polynomial> Polynomial::derivative() const {
    std::map<int, RationalNumber> derivative_coefficients;

    for (const auto& [degree, coefficient] : coefficients_) {
        if (degree == 0) {
            continue;
        }

        RationalNumber degree_rational(IntegerNumber(degree), NaturalNumber(1));

        RationalNumber new_coefficient = coefficient * degree_rational;

        int new_degree = degree - 1;

        derivative_coefficients[new_degree] = new_coefficient;
    }

    return std::make_unique<Polynomial>(std::move(derivative_coefficients));
}


std::unique_ptr<Polynomial> Polynomial::gcd(const Polynomial& p1, const Polynomial& p2) { //GCF_PP_P
    if (p1.coefficients_.empty() && p2.coefficients_.empty()) {
        throw std::invalid_argument("Both polynomials are zero; GCD is undefined.");
    }

    // Копии многочленов для работы
    std::unique_ptr<Polynomial> a = std::make_unique<Polynomial>(p1);
    std::unique_ptr<Polynomial> b = std::make_unique<Polynomial>(p2);

    if (a->coefficients_.empty()) return std::make_unique<Polynomial>(*b);
    if (b->coefficients_.empty()) return std::make_unique<Polynomial>(*a);

    while (!b->coefficients_.empty()) {
        std::unique_ptr<Polynomial> remainder = a->remainder(*b);
        a = std::move(b);
        b = std::move(remainder);
    }

    a->normalize();
    return a;
}

std::unique_ptr<Polynomial> Polynomial::simplify_roots() const { //NMR_P_P
    if (coefficients_.empty()) {
        // Нулевой многочлен возвращается как есть
        return std::make_unique<Polynomial>(*this);
    }

    // 1. Вычисляем производную многочлена
    std::unique_ptr<Polynomial> derivative_poly = this->derivative();

    // 2. Вычисляем НОД исходного многочлена и его производной
    std::unique_ptr<Polynomial> gcd_poly = Polynomial::gcd(*this, *derivative_poly);

    // 3. Если НОД = 1, возвращаем исходный многочлен.
    if (gcd_poly->coefficients_.size() == 1 && gcd_poly->degree() == 0) {
        return std::make_unique<Polynomial>(*this);
    }

    // 4. Создаем пустой указатель для остатка
    std::unique_ptr<Polynomial> remainder = nullptr;

    // 5. Делим исходный многочлен на НОД
    std::unique_ptr<Polynomial> simplified_poly = this->divide(*gcd_poly, remainder);

    // 6. Возвращаем результат
    return simplified_poly;
}
