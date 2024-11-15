
const RationalNumber& leading_coefficient() const{
    return coefficients_[std::prev(coefficients_.end())];
}

int degree() const{
    return std::prev(coefficients_.end())
}


