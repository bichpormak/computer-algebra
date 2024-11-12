#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include <cstdint>
#include <memory>

#include "../core/processing_input.h"


class Number {
private:
    int64_t number_;
    std::vector<uint8_t> digits_of_number_;
    SignNumber sign_;
    uint8_t highest_order_digit_;

public:
    Number(int64_t input_number)
        :
        number_(input_number),
        digits_of_number_(split_number_into_digits(input_number)),
        sign_(determining_sign_number(input_number)),
        highest_order_digit_(digits_of_number_[0]) {}

    virtual ~Number() = default;


public:
    int64_t get_number() const { return number_; }
    std::vector<uint8_t> get_digits_of_number() const { return digits_of_number_; }
    SignNumber get_sign() const { return sign_; }
    uint8_t get_elder_digit_order() const { return highest_order_digit_; }

};


#endif