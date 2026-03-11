#pragma once
#include "IRewardRule.h"

// Modification 2: reward is no longer equal to base score(replace IRewardRule)
// Even round -> reward = baseScore * 2
// Odd round  -> reward = baseScore + 2
class EvenDoubleRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore, int round) override {
        if (round % 2 == 0) {
            return baseScore * 2;
        } else {
            return baseScore + 2;
        }
    }
};
