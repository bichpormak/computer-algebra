
    std::unique_ptr<Polynomial> add(const Polynomial& other) const {
        auto result = std::make_unique<Polynomial>();

        for (const auto& [key, value] : coefficients_) {
            result->coefficients_[key] = std::make_unique<RationalNumber>(*value);
        }

        for (const auto& [key, value] : other.coefficients_) {
            if (result->coefficients_.find(key) != result->coefficients_.end()) {
                result->coefficients_[key].add(*value);
            } else {
                result->coefficients_[key] = std::make_unique<RationalNumber>(*value);
            }
        }
        return result; 
    }

    std::unique_ptr<Polynomial> subtract(const Polynomial& other) const{
        auto result = std::make_unique<Polynomial>();

        for (const auto& [key, value] : coefficients_) {
            result->coefficients_[key] = std::make_unique<RationalNumber>(*value);
        }

        for (const auto& [key, value] : other.coefficients_) {
            if (result->coefficients_.find(key) != result->coefficients_.end()) {
                result->coefficients_[key].subtract(*value);
            } else {
                result->coefficients_[key] = std::make_unique<RationalNumber>(-*value);
            }
        }
        return result; 

    }


