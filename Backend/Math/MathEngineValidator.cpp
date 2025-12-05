//
// Created by kianw on 12/3/2025.
//

#include "MathEngineValidator.h"

#include <iostream>
#include <ostream>

namespace RadMath {

    bool MathEngineValidator::wasValid() {
        return FinalResults.isValid;
    }

    void MathEngineValidator::printErrors() {
        for (const auto& error : FinalResults.errorMessages) {
            std::cout << error << std::endl;
        }
    }

    ValidationResult MathEngineValidator::handleResult(const ValidationResult &result) {
        if (!result.isValid) {
            FinalResults.errorMessages.insert(
                FinalResults.errorMessages.end(),
                result.errorMessages.begin(),
                result.errorMessages.end()
            );

            FinalResults.isValid = false;
        }

        return result;
    }

    void MathEngineValidator::ValidateNotAllZeros(const std::vector<long long>& nums) {
        for ( long long x: nums) {
        if (x != 0) {handleResult(ValidationResult{true}); }
        }
        handleResult(
        ValidationResult{
            true,
            {"Error: all values are zero"},
        });
    }

}
