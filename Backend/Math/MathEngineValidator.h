//
// Created by kianw on 12/3/2025.
//

#ifndef MATHRADICAL_MATHENGINEVALIDATOR_H
#define MATHRADICAL_MATHENGINEVALIDATOR_H

#include <string>
#include <cstdint>
#include <functional>
#include <vector>

namespace RadMath{

    struct ValidationResult {
        bool isValid = true;

        std::vector<std::string> errorMessages = {};

        [[nodiscard]] std::string GetAggregatedMessage() const {
            std::string full_error = "Validation failed. Errors: ";
            for (const auto& msg : errorMessages) {
                full_error += msg + "; ";
            }
            return full_error;
        }
    };

class MathEngineValidator {
private:
    ValidationResult FinalResults;

public:
    /**
    * @brief adds a ValidationResult to results
    * @param result the ValidationResult to process
    * @return GCD of a and b
    */
    ValidationResult handleResult(const ValidationResult& result);

    void ValidateNotAllZeros(const std::vector<long long>& nums);

    void ValidateWholeNumbers(const std::vector<long long>& nums);

    void printErrors();

    bool wasValid();

};
}


#endif //MATHRADICAL_MATHENGINEVALIDATOR_H
