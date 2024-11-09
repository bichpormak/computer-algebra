#include "natural_number.h"

std::unique_ptr<Number> NaturalNumber::add(Number &other) const {
    auto num1 = this->get_digits_of_number();
    auto num2 = other.get_digits_of_number();
    if (this->compare(dynamic_cast<NaturalNumber &>(other)) == 1){ //finding a larger number
        auto tmp = num2;
        num2 = num1;
        num1 = tmp;
    };
    num1 = reverse_digits_in_vector(num1); // reversal of a larger number 
    num2 = reverse_digits_in_vector(num2);
    for (size_t k = 0; k < num2.size(); ++k){ 

        num1[k] += num2[k]; // bitwise addition of digits
        if (num1[k] >= 10 && k + 1 < num1.size()){ // the result of adding is greater than 10. Moreover, this is not the maximum digit
            num1[k + 1] += 1;
            num1[k] -= 10;
        }
        else if(num1[k] >= 10 && k + 1 == num1.size()){ //  the result of adding is greater than 10. Moreover, this is the maximum digit
            num1.emplace_back(1);
            num1[k] -= 10;
        }
    }
    num1 = reverse_digits_in_vector(num1); 
    
    return std::make_unique<NaturalNumber>((gather_digits_into_number(num1)));
    
}

std::unique_ptr<Number> NaturalNumber::subtract(Number &other) const {

    return nullptr;
}

std::unique_ptr<Number> NaturalNumber::multiply(Number &other) const {
    auto num1 = this->get_digits_of_number();
    auto num2 = other.get_digits_of_number();

    std::unique_ptr<NaturalNumber> result = std::make_unique<NaturalNumber>(0);

    num2 = reverse_digits_in_vector(num2);

    std::unique_ptr<NaturalNumber> tmp = std::make_unique<NaturalNumber>(gather_digits_into_number(num1));

    for (size_t k = 0; k < num2.size(); ++k) {
        auto partial_product = tmp->multiply_by_digit(num2[k]);

        auto shifted_product_ptr = dynamic_cast<NaturalNumber*>(partial_product.get());

        auto shifted_product = shifted_product_ptr->multiply_by_ten_in_power(k);

        result = std::unique_ptr<NaturalNumber>(dynamic_cast<NaturalNumber*>(result->add(*shifted_product).release()));
    }
    
    return result;

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
    auto num1 = this->get_digits_of_number();
    auto num2 = other.get_digits_of_number();
    int result = 0; 
    if (num1.size() > num2.size()){ // if the number of digits in the first number is greater than the number of digits in the second, then the first number is greater than the second
        result = 2;
    }
    else if (num1.size() < num2.size()){ // if the number of digits in the first number is less than the number of digits in the second, then the second number is greater
        result = 1;
    }
    else{ // bitwise comparison, if the number of bits matches
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
    std::unique_ptr<Number> multiplied = other.multiply_by_digit(digit);

    std::unique_ptr<Number> result = this->subtract(*multiplied);

    return result;
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
