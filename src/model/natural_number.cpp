#include "natural_number.h"

std::unique_ptr<Number> NaturalNumber::add(Number &other) const {
    auto num1 = this->get_digits_of_number();// сохранение цифр первого числа 
    auto num2 = other.get_digits_of_number();
    if (this->compare(static_cast<NaturalNumber &>(other)) == 1){ // поиск большего числа 
        auto tmp = num2;
        num2 = num1;
        num1 = tmp;
    };
    std::reverse(num1.begin(), num1.end()); // разворот большего числа 
    std::reverse(num2.begin(), num2.end());
    for (size_t k = 0; k < num2.size(); ++k){ 

        num1[k] += num2[k]; // поразрядовое сложение цифр
        if (num1[k] >= 10 && k + 1 < num1.size()){ // случай, когда при сложении разрядов получилось число, которое больше 10. При этом это не максимальный разраяд
            num1[k + 1] += 1;
            num1[k] -= 10;
        }
        else if(num1[k] >= 10 && k + 1 == num1.size()){ // случай, когда при сложении разрядов получилось число, которое больше 10. При этом это максимальный разраяд
            num1.emplace_back(1);
            num1[k] -= 10;
        }
    }
    std::reverse(num1.begin(), num1.end()); // разворот числа 
    return std::make_unique<Number>((gather_digits_into_number(num1)));
    
}

std::unique_ptr<Number> NaturalNumber::subtract(Number &other) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::multiply(Number &other) const {
    auto num1 = this->get_digits_of_number();// сохранение цифр первого числа 
    auto num2 = other.get_digits_of_number();
    std::unique_ptr<NaturalNumber> result = std::make_unique<NaturalNumber>(0);

    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    std::unique_ptr<NaturalNumber> tmp = std::make_unique<NaturalNumber>(gather_digits_into_number(num1));
    
    for (size_t k = 0; k < num2.size(); ++k){ // проход по цифрам множетеля
        tmp->multiply_by_digit(num2[k]);
        result->add(tmp->multiply_by_ten_in_power(k));
        
    }

    return std::make_unique<Number>(gather_digits_into_number(result->get_digits_of_number()));
}

std::unique_ptr<Number> NaturalNumber::divide(Number &other) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::get_absolute_value() const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::change_sign() const {

    return nullptr;
}

uint8_t NaturalNumber::compare(NaturalNumber &other) const {
    auto num1 = this->get_digits_of_number(); // сохранение цифр первого числа 
    auto num2 = other.get_digits_of_number();
    int result = 0; 
    if (num1.size() > num2.size()){ // сравнение, если количество разрядов в первом числе больше количества разрядов во втором
        result = 2;
    }
    else if (num1.size() < num2.size()){ // сравнение, если количество разрядов в первом числе меньше количества разрядов во втором
        result = 1;
    }
    else{ // поразрядовое сравнение, если количетсво разрядов совпадает
        for (size_t i = 0; i < num1.size(); ++i){
            if(num1[i] > num2[i]){
                result = 2;
                break;
            }
            else if (num1[i] < num2[i]){
                result = 1;
                break;
            }
        }
    }

    return result;
}

bool NaturalNumber::is_zero() const {

    return false;
}

std::unique_ptr<Number> NaturalNumber::add_one() const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::multiply_by_digit(int64_t digit) const {

    return nullptr;
}
std::unique_ptr<Number> NaturalNumber::multiply_by_ten_in_power(int64_t power) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::subtract_with_multiply_digit(NaturalNumber& other, int64_t digit) const {

    return nullptr;
}
std::unique_ptr<Number> NaturalNumber::get_first_digit_after_division_number_on_ten_in_power(int64_t power) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::division_numbers_with_remainder(NaturalNumber& other) const {



    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::calculating_remainder_after_division(NaturalNumber& other) const {

    std::unique_ptr<Number> incomplete_quotient = division_numbers_with_remainder(other);

    return subtract_with_multiply_digit(other, incomplete_quotient->get_number());

}

std::unique_ptr<Number> NaturalNumber::calculate_gcd(NaturalNumber& other) const {

    auto firstNumber = *this;
    auto secondNumber = other;

    while (!secondNumber.is_zero()) {

        std::unique_ptr<Number> remainder_ptr = firstNumber.calculating_remainder_after_division(secondNumber);
        NaturalNumber* remainder = dynamic_cast<NaturalNumber*>(remainder_ptr.get());

        if (firstNumber.compare(secondNumber) == 2) {
            firstNumber = secondNumber;
            secondNumber = *remainder;
        } else if (firstNumber.compare(secondNumber) == 1) {
            secondNumber = firstNumber;
            firstNumber = *remainder;
        } else {
            break;
        }
    }

    return std::make_unique<NaturalNumber>(firstNumber);

}

std::unique_ptr<Number> NaturalNumber::calculate_lcm(NaturalNumber& other) const {

    return nullptr;
}