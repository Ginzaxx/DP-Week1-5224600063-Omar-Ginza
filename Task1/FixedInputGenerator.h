#pragma once
#include "IInputGenerator.h"

// Concrete implementation: always returns a fixed value of 3
class FixedInputGenerator : public IInputGenerator {
public:
    TurnInput generate() override {
        return TurnInput{3};
    }
};
