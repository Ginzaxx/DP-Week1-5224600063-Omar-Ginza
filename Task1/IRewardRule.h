#pragma once

class IRewardRule {
public:
    virtual int computeReward(int baseScore, int round) = 0;
    virtual ~IRewardRule() = default;
};
