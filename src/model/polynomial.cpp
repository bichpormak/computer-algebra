#include "polynomial.h"
#include <memory>

std::unique_ptr<Polynomial> Polynomial::multiply(const Polynomial& other) const{
    auto res = std::make_unique<Polynomial>();
    for(const auto& iter : coefficients_){
        auto polinomial = other.multiply_by_rational(*iter.second);
        auto temp = polinomial->multiply_by_x_power(*iter.first);
        res->add(*temp);
    }
    return res;
}

std::unique_ptr<Polynomial> Polynomial::remainder(const Polynomial& divisor) const{
    auto quotient = this->divide(divisor);
    auto temp = quotient->multiply(divisor);
    return std::make_unique<Polynomial>(this->subtract(*temp));
}
