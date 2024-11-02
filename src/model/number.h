#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include <cstdint>

class Number {

private:
    std::vector<int8_t> digits_of_number_;
    bool is_positive_;
    int8_t elder_digit_order_;


public:
    std::vector<int8_t> getNumber() const { return digits_of_number_; }
    void setNumber(std::vector<int8_t> digits_of_number) { digits_of_number_ = digits_of_number; }

    bool get_is_positive() const { return is_positive_; }
    void set_is_positive(bool is_positive) { is_positive_ = is_positive; }

    int8_t get_elder_digit_order() const { return elder_digit_order_; }
    void set_elder_digit_order(int8_t elder_digit_order) { elder_digit_order_ = elder_digit_order; }

};


#endif