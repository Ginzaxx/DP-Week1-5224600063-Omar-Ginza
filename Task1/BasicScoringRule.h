#pragma once
#include "IScoringRule.h"

// Base score equals the input value directly
class BasicScoringRule : public IScoringRule {
public:
    int computeScore(const TurnInput& input) override {
        return input.value;
    }
};
