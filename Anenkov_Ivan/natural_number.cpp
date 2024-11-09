#include "number.h" 

std::unique_ptr<Number> NaturalNumber::subtract_with_multiply_digit(NaturalNumber& other, int64_t digit) const { 

    NaturalNumber *subtract_with_multiply_digit = new NaturalNumber(this->subtract(other.multiply_by_digit(digit))); 
    
    return std::unique_ptr<Number>(subtract_with_multiply_digit); 
} 

