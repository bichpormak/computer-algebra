#include "rational_numbers.h"

#include "rational_numbers.h"

// Оператор сложения
RationalNumber RationalNumber::operator+(const RationalNumber& other) const {
    // Создаем копии числителей и знаменателей
    IntegerNumber numerator1 = numerator_integer_number_;
    IntegerNumber numerator2 = other.numerator_integer_number_;
    NaturalNumber denominator1 = denominator_natural_number_;
    NaturalNumber denominator2 = other.denominator_natural_number_;

    // Вычисляем новый числитель: (a * d) + (b * c)
    IntegerNumber denom2_as_int(denominator2.get_number());
    auto temp1 = numerator1.multiply(denom2_as_int);
    IntegerNumber denom1_as_int(denominator1.get_number());
    auto temp2 = numerator2.multiply(denom1_as_int);
    auto new_numerator = temp1->add(*temp2);

    // Вычисляем новый знаменатель: b * d
    auto new_denominator = denominator1.multiply(denominator2);

    return RationalNumber(*new_numerator, new_denominator->get_number());
}


// Оператор вычитания
RationalNumber RationalNumber::operator-(const RationalNumber& other) const {
    IntegerNumber numerator1 = numerator_integer_number_;
    IntegerNumber numerator2 = other.numerator_integer_number_;
    NaturalNumber denominator1 = denominator_natural_number_;
    NaturalNumber denominator2 = other.denominator_natural_number_;

    IntegerNumber denom2_as_int(denominator2.get_number());
    auto temp1 = numerator1.multiply(denom2_as_int);
    IntegerNumber denom1_as_int(denominator1.get_number());
    auto temp2 = numerator2.multiply(denom1_as_int);
    auto new_numerator = temp1->subtract(*temp2);

    auto new_denominator = denominator1.multiply(denominator2);

    return RationalNumber(*new_numerator, new_denominator->get_number());
}

// Оператор умножения
RationalNumber RationalNumber::operator*(const RationalNumber& other) const {
    IntegerNumber numerator1 = numerator_integer_number_;
    IntegerNumber numerator2 = other.numerator_integer_number_;
    NaturalNumber denominator1 = denominator_natural_number_;
    NaturalNumber denominator2 = other.denominator_natural_number_;

    auto new_numerator = numerator1.multiply(numerator2);
    auto new_denominator = denominator1.multiply(denominator2);

    return RationalNumber(new_numerator->get_number(), new_denominator->get_number());
}

// Оператор деления
RationalNumber RationalNumber::operator/(const RationalNumber& other) const {
    // 1. Проверяем деление на ноль
    if (other.numerator_integer_number_.get_number() == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    // 2. Определяем, будут ли знаки числителя одинаковыми
    bool same_sign = (this->numerator_integer_number_.get_sign() == other.numerator_integer_number_.get_sign());

    // 3. Вычисляем новый числитель: this.numerator * other.denominator
    // Создаём временную переменную для передачи по неконстантной ссылке
    IntegerNumber temp_other_denominator(other.denominator_natural_number_.get_number());
    std::unique_ptr<IntegerNumber> new_numerator_ptr = this->numerator_integer_number_.multiply(temp_other_denominator);

    // 4. Если знаки не совпадают, меняем знак нового числителя
    if (!same_sign) {
        std::unique_ptr<IntegerNumber> neg_numerator_ptr = new_numerator_ptr->change_sign();
        new_numerator_ptr = std::move(neg_numerator_ptr);
    }

    // 5. Вычисляем новый знаменатель: this.denominator * abs(other.numerator)
    std::unique_ptr<NaturalNumber> abs_other_numerator_ptr = other.numerator_integer_number_.get_absolute_value();
    NaturalNumber abs_other_numerator = *abs_other_numerator_ptr; // Правильный тип
    std::unique_ptr<NaturalNumber> new_denominator_ptr = this->denominator_natural_number_.multiply(abs_other_numerator);

    // 6. Создаём и возвращаем новый объект RationalNumber
    return RationalNumber(new_numerator_ptr->get_number(), new_denominator_ptr->get_number());
}


// Оператор сравнения
bool RationalNumber::operator==(const RationalNumber& other) const {
    auto reduced_this = this->reduce_fraction();
    auto reduced_other = other.reduce_fraction();

    return (reduced_this->numerator_integer_number_.get_number() == reduced_other->numerator_integer_number_.get_number()) &&
           (reduced_this->denominator_natural_number_.get_number() == reduced_other->denominator_natural_number_.get_number());
}


std::unique_ptr<RationalNumber> RationalNumber::add(RationalNumber &other) const {

    IntegerNumber numerator1 = this->numerator_integer_number_;
    IntegerNumber numerator2 = other.numerator_integer_number_;

    IntegerNumber denominator1(this->denominator_natural_number_.get_number());
    IntegerNumber denominator2(other.denominator_natural_number_.get_number());

    // Вычисляем общий знаменатель
    auto common_denominator = denominator1.multiply(denominator2);

    // Приводим числители к общему знаменателю
    auto new_numerator1 = numerator1.multiply(denominator2);
    auto new_numerator2 = numerator2.multiply(denominator1);

    // Складываем числители
    auto result_numerator = new_numerator1->add(*new_numerator2);

    // Создаем результат без сокращения дроби
    RationalNumber result(IntegerNumber(result_numerator->get_number()),
                          NaturalNumber(common_denominator->get_number()));


    return result.reduce_fraction();
}

std::unique_ptr<RationalNumber> RationalNumber::subtract(RationalNumber &other) const {

    IntegerNumber numerator1 = this->numerator_integer_number_;
    IntegerNumber numerator2 = other.numerator_integer_number_;

    IntegerNumber denominator1(this->denominator_natural_number_.get_number());
    IntegerNumber denominator2(other.denominator_natural_number_.get_number());

    // Вычисляем общий знаменатель
    auto common_denominator = denominator1.multiply(denominator2);

    // Приводим числители к общему знаменателю
    auto new_numerator1 = numerator1.multiply(denominator2);
    auto new_numerator2 = numerator2.multiply(denominator1);

    // Вычитаем числители
    auto result_numerator = new_numerator1->subtract(*new_numerator2);

    // Создаем результат без сокращения дроби
    RationalNumber result(IntegerNumber(result_numerator->get_number()),
                          NaturalNumber(common_denominator->get_number()));
    return result.reduce_fraction();
}

std::unique_ptr<RationalNumber> RationalNumber::multiply(RationalNumber &other) const {
    auto numerator1 = this->numerator_integer_number_;
    auto numenator2 = other.numerator_integer_number_;

    IntegerNumber denominator1(this->denominator_natural_number_.get_number());
    IntegerNumber denominator2(other.denominator_natural_number_.get_number());
    auto result_numerator = numerator1.multiply(numenator2);

    auto result_denominator = denominator1.multiply(denominator2);

    return std::make_unique<RationalNumber>(RationalNumber(result_numerator->get_number(), result_denominator->get_number()));
}

std::unique_ptr<RationalNumber> RationalNumber::divide(RationalNumber& other) const {
    if (other.numerator_integer_number_.get_number() == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    auto numerator1 = this->numerator_integer_number_;
    auto numenator2 = other.numerator_integer_number_;

    IntegerNumber denominator1(this->denominator_natural_number_.get_number());
    IntegerNumber denominator2(other.denominator_natural_number_.get_number());

    auto result_numerator = numerator1.multiply(denominator2); // a/b / c/d = a*d / b*c

    auto result_denominator = denominator1.multiply(numenator2);

    return std::make_unique<RationalNumber>(RationalNumber(result_numerator->get_number(), result_denominator->get_number()));
}

std::unique_ptr<RationalNumber> RationalNumber::convert_integer_to_fraction(IntegerNumber& other) const {
    
    return std::make_unique<RationalNumber>(RationalNumber(other, NaturalNumber(1)));
}

std::unique_ptr<IntegerNumber> RationalNumber::convert_reduced_fraction_to_integer() const {
    if (this->is_integer()){
        return std::make_unique<IntegerNumber>(this->numerator_integer_number_);
    }
    else{
        throw std::invalid_argument("Fraction can't be converted!");
    }
}

std::unique_ptr<RationalNumber> RationalNumber::reduce_fraction() const {
    // Проверяем, равен ли числитель нулю
    if (this->numerator_integer_number_.get_number() == 0) {
        // Если числитель ноль, знаменатель устанавливаем равным 1
        return std::make_unique<RationalNumber>(IntegerNumber(0), NaturalNumber(1));
    }

    // Получаем абсолютное значение числителя
    auto abs_numerator = this->numerator_integer_number_.get_absolute_value();

    // Получаем знаменатель
    NaturalNumber denominator = this->denominator_natural_number_;

    // Вычисляем НОД числителя и знаменателя
    auto gcd_ptr = denominator.calculate_gcd(*abs_numerator);
    NaturalNumber gcd = *gcd_ptr;

    // Если НОД равен 1, дробь уже несократима
    if (gcd.get_number() == 1) {
        return std::make_unique<RationalNumber>(*this);
    }

    // Делим числитель на НОД
    IntegerNumber divisor(gcd.get_number());
    auto new_numerator_ptr = this->numerator_integer_number_.calculating_quotient(divisor);
    if (!new_numerator_ptr) {
        throw std::runtime_error("Ошибка при делении числителя на НОД.");
    }
    IntegerNumber new_numerator = *new_numerator_ptr;

    // Делим знаменатель на НОД
    auto new_denominator_ptr = denominator.division_numbers_with_remainder(gcd);
    if (!new_denominator_ptr) {
        throw std::runtime_error("Ошибка при делении знаменателя на НОД.");
    }
    NaturalNumber new_denominator = *new_denominator_ptr;

    // Возвращаем новую, сокращенную дробь
    return std::make_unique<RationalNumber>(RationalNumber(new_numerator, new_denominator));
}

bool RationalNumber::is_integer() const {
    auto reduced_fraction = this->reduce_fraction();
    return reduced_fraction->denominator_natural_number_.get_number() == 1;
}
