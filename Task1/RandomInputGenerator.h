#pragma once
#include "IInputGenerator.h"
#include <cstdlib>

// Modification 1: replaces FixedInputGenerator
// Returns a random value between 1 and 10
class RandomInputGenerator : public IInputGenerator {
public:
    TurnInput generate() override {
        int val = (std::rand() % 10) + 1;
        return TurnInput{val};
    }
};
