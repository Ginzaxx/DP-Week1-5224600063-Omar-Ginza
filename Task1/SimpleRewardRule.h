#pragma once
#include "IRewardRule.h"

// Step A: reward equals base score (no modification yet)
class SimpleRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore, int round) override {
        return baseScore;
    }
};
