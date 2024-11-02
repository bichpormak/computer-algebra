#ifndef NATURAL_NUMBER_H
#define NATURAL_NUMBER_H

#include "number.h"

class NaturalNumber : public Number {
public:
    uint8_t comparison_natural_numbers() const;              // COM_NN_D
    bool is_natural_number_zero() const;                     // NZER_N_B
    uint64_t adding_one_to_natural_number();                 // ADD_1N_N
    uint64_t adding_natural_numbers();                       // ADD_NN_N - dependence COM_NN_D
    uint64_t subtracting_natural_numbers();                  // SUB_NN_N - dependence COM_NN_D
    uint64_t multiply_natural_number_by_digit();             // MUL_ND_N
    uint64_t multiply_natural_number_by_ten_in_power();      // MUL_Nk_N
    uint64_t multiply_natural_numbers();                     // MUL_NN_N - dependence MUL_ND_N, MUL_Nk_N, ADD_NN_N
    uint64_t subtracting_from_natural_number_natural_number_multiply_by_digit(); // SUB_NDN_N - dependence SUB_NN_N, MUL_ND_N, COM_NN_D

};


#endif