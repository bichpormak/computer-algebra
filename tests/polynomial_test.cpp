#include <gtest/gtest.h>
#include "../src/model/polynomial.h"

class PolynomialTest : public ::testing::Test {
protected:
    std::unique_ptr<Polynomial> poly1_;
    std::unique_ptr<Polynomial> poly2_;
    std::unique_ptr<Polynomial> poly_zero_;
    RationalNumber rational_two_;

    void SetUp() override {
        // Инициализируем многочлены
        // poly1 = 2x^2 + 3x + 1
        poly1_ = std::make_unique<Polynomial>(std::map<int, RationalNumber>{
            {2, RationalNumber(IntegerNumber(2), NaturalNumber(1))},
            {1, RationalNumber(IntegerNumber(3), NaturalNumber(1))},
            {0, RationalNumber(IntegerNumber(1), NaturalNumber(1))}
        });

        // poly2 = x^2 - x + 4
        poly2_ = std::make_unique<Polynomial>(std::map<int, RationalNumber>{
            {2, RationalNumber(IntegerNumber(1), NaturalNumber(1))},
            {1, RationalNumber(IntegerNumber(-1), NaturalNumber(1))},
            {0, RationalNumber(IntegerNumber(4), NaturalNumber(1))}
        });

        // Нулевой многочлен
        poly_zero_ = std::make_unique<Polynomial>();

        // Рациональное число 2
        rational_two_ = RationalNumber(IntegerNumber(2), NaturalNumber(1));
    }

    void TearDown() override {
        // Освобождаем ресурсы, если необходимо
    }

    // Помощник для проверки равенства многочленов
    bool polynomials_are_equal(const Polynomial& poly1, const Polynomial& poly2) {
        auto diff = poly1.subtract(poly2);
        return is_zero_polynomial(*diff);
    }

    // Проверка на нулевой многочлен
    bool is_zero_polynomial(const Polynomial& poly) {
        try {
            poly.degree();
            return false;
        } catch (const std::runtime_error&) {
            return true;
        }
    }
};

TEST_F(PolynomialTest, Add) {
    // Ожидаемый результат: 3x^2 + 2x + 5
    auto result = poly1_->add(*poly2_);
    Polynomial expected(std::map<int, RationalNumber>{
        {2, RationalNumber(IntegerNumber(3), NaturalNumber(1))},
        {1, RationalNumber(IntegerNumber(2), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(5), NaturalNumber(1))}
    });
    EXPECT_TRUE(polynomials_are_equal(*result, expected));
}

TEST_F(PolynomialTest, Subtract) {
    // Ожидаемый результат: x^2 + 4x - 3
    auto result = poly1_->subtract(*poly2_);
    Polynomial expected(std::map<int, RationalNumber>{
        {2, RationalNumber(IntegerNumber(1), NaturalNumber(1))},
        {1, RationalNumber(IntegerNumber(4), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(-3), NaturalNumber(1))}
    });
    EXPECT_TRUE(polynomials_are_equal(*result, expected));
}

TEST_F(PolynomialTest, MultiplyByRational) {
    // Ожидаемый результат: 4x^2 + 6x + 2
    auto result = poly1_->multiply_by_rational(rational_two_);
    Polynomial expected(std::map<int, RationalNumber>{
        {2, RationalNumber(IntegerNumber(4), NaturalNumber(1))},
        {1, RationalNumber(IntegerNumber(6), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(2), NaturalNumber(1))}
    });
    EXPECT_TRUE(polynomials_are_equal(*result, expected));
}

TEST_F(PolynomialTest, MultiplyByXPower) {
    // Ожидаемый результат: 2x^3 + 3x^2 + x
    auto result = poly1_->multiply_by_x_power(1);
    Polynomial expected(std::map<int, RationalNumber>{
        {3, RationalNumber(IntegerNumber(2), NaturalNumber(1))},
        {2, RationalNumber(IntegerNumber(3), NaturalNumber(1))},
        {1, RationalNumber(IntegerNumber(1), NaturalNumber(1))}
    });
    EXPECT_TRUE(polynomials_are_equal(*result, expected));
}

TEST_F(PolynomialTest, MultiplyPolynomials) {
    // Ожидаемый результат: 2x^4 + x^3 + 6x^2 + 11x + 4
    auto result = poly1_->multiply(*poly2_);
    Polynomial expected(std::map<int, RationalNumber>{
        {4, RationalNumber(IntegerNumber(2), NaturalNumber(1))},
        {3, RationalNumber(IntegerNumber(1), NaturalNumber(1))},
        {2, RationalNumber(IntegerNumber(6), NaturalNumber(1))},
        {1, RationalNumber(IntegerNumber(11), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(4), NaturalNumber(1))}
    });
    EXPECT_TRUE(polynomials_are_equal(*result, expected));
}

TEST_F(PolynomialTest, Derivative) {
    // Ожидаемый результат: 4x + 3
    auto result = poly1_->derivative();
    Polynomial expected(std::map<int, RationalNumber>{
        {1, RationalNumber(IntegerNumber(4), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(3), NaturalNumber(1))}
    });
    EXPECT_TRUE(polynomials_are_equal(*result, expected));
}

TEST_F(PolynomialTest, Divide) {
    // Делим x^2 - 1 на x - 1, ожидаемое частное: x + 1, остаток: 0
    Polynomial dividend(std::map<int, RationalNumber>{
        {2, RationalNumber(IntegerNumber(1), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(-1), NaturalNumber(1))}
    });
    Polynomial divisor(std::map<int, RationalNumber>{
        {1, RationalNumber(IntegerNumber(1), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(-1), NaturalNumber(1))}
    });
    std::unique_ptr<Polynomial> remainder;
    auto quotient = dividend.divide(divisor, remainder);
    Polynomial expected_quotient(std::map<int, RationalNumber>{
        {1, RationalNumber(IntegerNumber(1), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(1), NaturalNumber(1))}
    });
    EXPECT_TRUE(polynomials_are_equal(*quotient, expected_quotient));
    EXPECT_TRUE(is_zero_polynomial(*remainder));
}

TEST_F(PolynomialTest, GCD_SimpleCase) {
    Polynomial p1({{1, RationalNumber(1)}});
    Polynomial p2({{0, RationalNumber(1)}});
    auto gcd = Polynomial::gcd(p1, p2);
    Polynomial expected({{0, RationalNumber(1)}});
    EXPECT_TRUE(polynomials_are_equal(*gcd, expected));
}

TEST_F(PolynomialTest, SimplifyRoots) {
    // Упрощаем корни многочлена x^4 - 1
    Polynomial p(std::map<int, RationalNumber>{
        {4, RationalNumber(IntegerNumber(1), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(-1), NaturalNumber(1))}
    });
    auto simplified = p.simplify_roots();
    // Проверяем, что после упрощения многочлен делится на исходный без остатка
    std::unique_ptr<Polynomial> remainder;
    p.divide(*simplified, remainder);
    EXPECT_TRUE(is_zero_polynomial(*remainder));
}

TEST_F(PolynomialTest, LeadingCoefficient) {
    EXPECT_NO_THROW({
        const RationalNumber& lc = poly1_->leading_coefficient();
        EXPECT_EQ(lc.get_numerator().get_number(), 2);
        EXPECT_EQ(lc.get_denominator().get_number(), 1);
    });
}

TEST_F(PolynomialTest, Degree) {
    // Проверяем степень poly1
    EXPECT_NO_THROW({
        int deg = poly1_->degree();
        EXPECT_EQ(deg, 2);
    });
}

TEST_F(PolynomialTest, Normalize) {
    // Проверяем нормализацию многочлена с нулевыми коэффициентами
    Polynomial p(std::map<int, RationalNumber>{
        {3, RationalNumber(IntegerNumber(0), NaturalNumber(1))},
        {2, RationalNumber(IntegerNumber(0), NaturalNumber(1))},
        {1, RationalNumber(IntegerNumber(5), NaturalNumber(1))},
        {0, RationalNumber(IntegerNumber(0), NaturalNumber(1))}
    });
    p.normalize();
    Polynomial expected(std::map<int, RationalNumber>{
        {1, RationalNumber(IntegerNumber(5), NaturalNumber(1))}
    });
    EXPECT_TRUE(polynomials_are_equal(p, expected));
}

TEST_F(PolynomialTest, ExceptionOnEmptyPolynomial) {
    // Проверяем выброс исключения при обращении к пустому многочлену
    EXPECT_THROW(poly_zero_->leading_coefficient(), std::runtime_error);
    EXPECT_THROW(poly_zero_->degree(), std::runtime_error);
}

TEST_F(PolynomialTest, DivideByZeroPolynomial) {
    // Проверяем выброс исключения при делении на нулевой многочлен
    std::unique_ptr<Polynomial> remainder;
    EXPECT_THROW(poly1_->divide(*poly_zero_, remainder), std::invalid_argument);
}