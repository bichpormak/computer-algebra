#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include <cstdint>

class Number {
private:
    std::vector<int8_t> digits_of_number_;




public:
    std::vector<int8_t> getNumber() const { return digits_of_number_; }


};


#endif