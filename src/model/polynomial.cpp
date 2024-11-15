#include "polynomial.h"
#include "natural_number.h"
#include "integer_numbers.h"

#include <numeric>

std::unique_ptr<Polynomial> Polynomial::derivative() const { //DER_P_P
    std::map<std::unique_ptr<int>, std::unique_ptr<RationalNumber>> derivative_coefficients;

    for (const auto& [degree_ptr, coefficient_ptr] : coefficients_) {
        int degree = *degree_ptr;

        // Производная от константы
        if (degree == 0) {
            continue;
        }

        RationalNumber degree_rational(IntegerNumber(degree), NaturalNumber(1));

        // Умножаем коэффициент на RationalNumber, представляющий степень
        auto new_coefficient = coefficient_ptr->multiply(degree_rational);

        auto new_degree = std::make_unique<int>(degree - 1);

        derivative_coefficients[std::move(new_degree)] = std::move(new_coefficient);
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
