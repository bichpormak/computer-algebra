#include "natural_number.h"

std::unique_ptr<NaturalNumber> NaturalNumber::add(NaturalNumber &other) const {

    auto num1 = this->get_digits_of_number();
    auto num2 = other.get_digits_of_number();
    if (this->compare(other) == 1){ //finding a larger number
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

std::unique_ptr<NaturalNumber> NaturalNumber::subtract(NaturalNumber &other) const {

    auto digits_first = reverse_digits_in_vector(this->get_digits_of_number());
    auto digits_second = reverse_digits_in_vector(other.get_digits_of_number());

    if (this->compare(other) <= 1) {
        throw std::invalid_argument("Первое число должно быть больше или равно второму!");
    }

    std::vector<uint8_t> result;
    int carry = 0; // Debt
    for (size_t i = 0; i < digits_first.size(); ++i) { 
        int current = digits_first[i] - ( (i < digits_second.size() ) ? digits_second[i] : 0) - carry; // Result of the subtraction on the i-th step
        if (current < 0) {
            current += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result.push_back(static_cast<uint8_t>(current));
    }

    result = reverse_digits_in_vector(result);

    return std::make_unique<NaturalNumber>(gather_digits_into_number(result));
}

std::unique_ptr<NaturalNumber> NaturalNumber::multiply(NaturalNumber &other) const {

    auto num1 = this->get_digits_of_number();
    auto num2 = other.get_digits_of_number();
    num2 = reverse_digits_in_vector(num2);

    std::unique_ptr<NaturalNumber> result = this->multiply_by_digit(num2[0]);

    for (size_t k = 1; k < num2.size(); ++k) {
        auto partial_product = this->multiply_by_digit(num2[k]);
        auto shifted_product = partial_product->multiply_by_ten_in_power(k);
        result = std::unique_ptr<NaturalNumber>(result->add(*shifted_product).release());
    }

    return result;
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
    auto digits = this->get_digits_of_number();
        // If the number has only one digit and that digit is 0
    if (digits.size() == 1 && digits[0] == 0) {
        return true;
    } else {
        return false;
    }
}

std::unique_ptr<NaturalNumber> NaturalNumber::add_one() const {

    auto num1 = reverse_digits_in_vector(this->get_digits_of_number());
    int carry = 1;

    for (size_t k = 0; k < num1.size(); ++k) {
        num1[k] += carry;

        if (num1[k] >= 10) {
            num1[k] -= 10;
            carry = 1;
        } else {
            carry = 0;
            break;
        }

    }

    if (carry > 0) {
        num1.push_back(carry);
    }

    num1 = reverse_digits_in_vector(num1);
    return std::make_unique<NaturalNumber>(gather_digits_into_number(num1));

}

std::unique_ptr<NaturalNumber> NaturalNumber::multiply_by_digit(int64_t digit) const {

    if (digit < 0 || digit > 9) {
        throw std::invalid_argument("Цифра должна быть от 0 до 9");
    }

    auto num1 = this->get_digits_of_number();
    num1 = reverse_digits_in_vector(num1);
    int carry = 0;

    for (size_t k = 0; k < num1.size(); ++k) {
        int product = num1[k] * digit + carry;
        num1[k] = product % 10;
        carry = product / 10;
    }

    if (carry > 0) {
        num1.push_back(carry);
    }

    num1 = reverse_digits_in_vector(num1);
    return std::make_unique<NaturalNumber>(gather_digits_into_number(num1));
}

std::unique_ptr<NaturalNumber> NaturalNumber::multiply_by_ten_in_power(int64_t power) const {

    if (power < 0) {
        throw std::invalid_argument("Степень должна быть неотрицательной!");
    }

    auto num1 = this->get_digits_of_number();
    for (int i = 0; i < power; ++i) {
        num1.push_back(0);
    }

    return std::make_unique<NaturalNumber>(gather_digits_into_number(num1));

}

std::unique_ptr<NaturalNumber> NaturalNumber::subtract_with_multiply_digit(NaturalNumber& other, int64_t digit) const {

    std::unique_ptr<NaturalNumber> multiplied = other.multiply_by_digit(digit);
    std::unique_ptr<NaturalNumber> result = this->subtract(*multiplied);

    return result;
}

std::unique_ptr<NaturalNumber> NaturalNumber::get_first_digit_after_division_number_on_ten_in_power(int64_t power) const {
    if (power < 0) {
        throw std::invalid_argument("Power must be non-negative");
    }

    // Create divisor = 10^power
    auto divisor = std::make_unique<NaturalNumber>(1);
    if (power > 0) {
        divisor = divisor->multiply_by_ten_in_power(power);
    }

    // Find the largest digit d (from 9 down to 1) such that d * divisor <= this
    for (int d = 9; d >= 1; --d) {
        // Multiply divisor by digit d
        auto d_times_divisor = divisor->multiply_by_digit(d);

        // Compare this number with d_times_divisor
        uint8_t cmp_result = this->compare(*d_times_divisor);

        if (cmp_result == 2 || cmp_result == 0) { // this >= d_times_divisor
            return std::make_unique<NaturalNumber>(d);
        }
    }

    // If no such d found, return 0
    return std::make_unique<NaturalNumber>(0);
}

std::unique_ptr<NaturalNumber> NaturalNumber::division_numbers_with_remainder(NaturalNumber& other) const {

    auto num1 = this->get_digits_of_number();
    auto num2 = other.get_digits_of_number();

    if (this->compare(other) == 1){ //finding a larger number
        auto tmp = num2;
        num2 = num1;
        num1 = tmp;
    }

    int k = num1.size() - num2.size();
    if (num1[0] < num2[0]){
        k--;
    }

    std::unique_ptr<NaturalNumber> result = std::make_unique<NaturalNumber>(int(num1[0]) / int(num2[0]));
    result->multiply_by_ten_in_power(k);
    return result;

}

std::unique_ptr<NaturalNumber> NaturalNumber::calculating_remainder_after_division(NaturalNumber& other) const {

    std::unique_ptr<NaturalNumber> incomplete_quotient = division_numbers_with_remainder(other);

    return subtract_with_multiply_digit(other, incomplete_quotient->get_number());

}

std::unique_ptr<NaturalNumber> NaturalNumber::calculate_gcd(NaturalNumber& other) const {

    auto firstNumber = *this;
    auto secondNumber = other;

    while (!secondNumber.is_zero()) {

        std::unique_ptr<NaturalNumber> remainder_ptr = firstNumber.calculating_remainder_after_division(secondNumber);
        NaturalNumber* remainder = remainder_ptr.get();

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

std::unique_ptr<NaturalNumber> NaturalNumber::calculate_lcm(NaturalNumber& other) {

    std::unique_ptr<NaturalNumber> gcd_ptr = this->calculate_gcd(other);
    NaturalNumber* gcd = gcd_ptr.get();

    std::unique_ptr<NaturalNumber> temp_ptr = this->division_numbers_with_remainder(*gcd);
    NaturalNumber* temp = temp_ptr.get();

    return temp->multiply(other);

}
