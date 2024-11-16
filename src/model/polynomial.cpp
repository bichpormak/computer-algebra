#include "polynomial.h"
#include <stdexcept>
#include <sstream>
#include <regex>

std::string Polynomial::toString() const {
    if (coefficients_.empty()) {
        return "0";
    }

    std::ostringstream oss;
    bool first = true;

    // Итерация от наивысшей степени к наименьшей
    for(auto it = coefficients_.rbegin(); it != coefficients_.rend(); ++it) {
        int degree = it->first;
        const RationalNumber &coeff = it->second;

        // Получаем числитель и знаменатель
        int num = coeff.get_numerator().get_number();
        int den = coeff.get_denominator().get_number();

        if (num == 0) continue;

        // Обработка знака
        if (num > 0 && !first) {
            oss << "+";
        }

        // Обработка коэффициента
        bool coeffIsOne = (num == 1) && (den == 1);
        bool coeffIsMinusOne = (num == -1) && (den == 1);

        if (degree == 0 || !(coeffIsOne || coeffIsMinusOne)) {
            // Если это дробь
            if (den != 1) {
                oss << num << "/" << den;
            } else {
                oss << num;
            }
        } else if (coeffIsMinusOne) {
            oss << "-";
        }

        // Обработка переменной и степени
        if (degree > 0) {
            oss << "x";
            if (degree > 1) {
                oss << "^" << degree;
            }
        }

        first = false;
    }

    return oss.str();
}

// Реализация статического метода fromString
std::unique_ptr<Polynomial> Polynomial::fromString(const std::string &input) {
    std::map<int, RationalNumber> coefficients;

    // Регулярное выражение для разбивки многочлена на термы
    std::regex termRegex(R"(([+-]?[^-+]+))");
    std::sregex_iterator termsBegin(input.begin(), input.end(), termRegex);
    std::sregex_iterator termsEnd;

    for (std::sregex_iterator i = termsBegin; i != termsEnd; ++i) {
        std::smatch match = *i;
        std::string term = match[1].str();

        // Регулярное выражение для анализа отдельного терма
        std::regex singleTermRegex(R"(([+-]?(\d+/\d+|\d*)?)x(?:\^(\d+))?|([+-]?\d+))");
        std::smatch termMatch;

        if (std::regex_match(term, termMatch, singleTermRegex)) {
            RationalNumber coeff;
            int degree = 0;

            if (termMatch[1].matched) { // Термин с x
                std::string coeffStr = termMatch[1].str();

                // Если коэффициент не указан, то подразумевается 1 или -1
                if (coeffStr.empty() || coeffStr == "+" || coeffStr == "-") {
                    coeff = RationalNumber{IntegerNumber(coeffStr == "-" ? -1 : 1), NaturalNumber(1)};
                } else {
                    // Парсинг коэффициента (рационального числа)
                    std::regex fractionRegex(R"(([+-]?\d+)/(\d+))");
                    std::smatch fracMatch;

                    if (std::regex_match(coeffStr, fracMatch, fractionRegex)) {
                        int numerator = std::stoi(fracMatch[1].str());
                        int denominator = std::stoi(fracMatch[2].str());
                        if (denominator == 0) {
                            throw std::invalid_argument("Denominator cannot be zero.");
                        }
                        coeff = RationalNumber{IntegerNumber(numerator), NaturalNumber(denominator)};
                    } else { // Целое число
                        int numerator = std::stoi(coeffStr);
                        coeff = RationalNumber{IntegerNumber(numerator), NaturalNumber(1)};
                    }
                }

                if (termMatch[3].matched) { // Есть степень
                    degree = std::stoi(termMatch[3].str());
                } else {
                    degree = 1; // Если степень не указана, подразумевается x^1
                }
            } else if (termMatch[4].matched) { // Постоянный член
                std::string constStr = termMatch[4].str();

                // Парсинг коэффициента (рационального числа)
                std::regex fractionRegex(R"(([+-]?\d+)/(\d+))");
                std::smatch fracMatch;

                if (std::regex_match(constStr, fracMatch, fractionRegex)) {
                    int numerator = std::stoi(fracMatch[1].str());
                    int denominator = std::stoi(fracMatch[2].str());
                    if (denominator == 0) {
                        throw std::invalid_argument("Denominator cannot be zero.");
                    }
                    coeff = RationalNumber{IntegerNumber(numerator), NaturalNumber(denominator)};
                } else { // Целое число
                    int numerator = std::stoi(constStr);
                    coeff = RationalNumber{IntegerNumber(numerator), NaturalNumber(1)};
                }
                degree = 0;
            }

            // Добавляем или обновляем коэффициент для данной степени
            if (coefficients.find(degree) != coefficients.end()) {
                coefficients[degree] = coefficients[degree] + coeff;
            } else {
                coefficients[degree] = coeff;
            }
        } else {
            throw std::invalid_argument("Invalid term format: " + term);
        }
    }

    return std::make_unique<Polynomial>(coefficients);
}
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
        throw std::invalid_argument("Division by zero polynomial is not allowed.");
    }

    Polynomial dividend(*this);
    auto quotient = std::make_unique<Polynomial>();

    while (!dividend.coefficients_.empty() && dividend.degree() >= divisor.degree()) {
        int deg_diff = dividend.degree() - divisor.degree();

        const RationalNumber& dividend_leading = dividend.leading_coefficient();
        const RationalNumber& divisor_leading = divisor.leading_coefficient();

        // Деление коэффициентов
        RationalNumber coeff_ratio;
        try {
            coeff_ratio = dividend_leading / divisor_leading;
        } catch (const std::exception& e) {
            throw std::runtime_error("Failed to divide coefficients: " + std::string(e.what()));
        }

        // Создание монома: coeff_ratio * x^deg_diff
        std::map<int, RationalNumber> monomial_coeffs;
        monomial_coeffs[deg_diff] = coeff_ratio;
        Polynomial monomial(monomial_coeffs);

        // Добавление монома к частному
        if (quotient->coefficients_.find(deg_diff) != quotient->coefficients_.end()) {
            quotient->coefficients_[deg_diff] = quotient->coefficients_[deg_diff] + coeff_ratio;
        } else {
            quotient->coefficients_[deg_diff] = coeff_ratio;
        }

        // Вычитание (divisor * monomial) из делимого
        auto product = divisor.multiply(monomial);
        dividend = *dividend.subtract(*product);

        // Защита от бесконечного цикла из-за ошибок в нормализации
        dividend.normalize();
    }

    quotient->normalize();
    remainder = std::make_unique<Polynomial>(dividend);
    remainder->normalize();

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