include "polynomail.h"
include "rational_numbers.h"
include "natural_numbers.h"
include "integer_numbers.h"

typedef void (NaturalNumber::*MethodPtr)(NaturalNumber&);

int callMethod(MethodPtr method, NaturalNumber& value) {
    return (this->*method)(value);
}

int func_of_list(std::vector<int>& numbers, MethodPtr method) {
    if (numbers.empty()) {
        return 0;
    }
    int current_func = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        current_func = callMethod(method, numbers[i]);
        if (current_func == 1 && method == &NaturalNumber::calculate_gcd) {
            break;
        }
    }
    return current_func;
}

void normalize(){
    std::vector<int> numerators;
    std::vector<int> denominators;

    for (const auto& pair : coefficients_) {
            numerators.push_back(std::get_absolute_value(std::make_unique<IntegerNumber>(*pair.second).numerator)->converting_positive_integer_to_natural);
            denominators.push_back(std::make_unique<NaturalNumber>(*pair.second).denominator);
    }

    gcd_ = func_of_list(numerators, &NaturalNumber::calculate_gcd) 
    lcm_ = func_of_list(denominators, &NaturalNumber::calculate_lcm);

    for (const auto& pair : coefficients_) {
        this->coefficients_[pair.first] = std::make_unique<RationalNumber>(std::make_unique<IntegerNumber>(*pair.second).numerator / gcd_,  std::make_unique<NaturalNumber>(*pair.second).denominator / lcm_);
    }
}