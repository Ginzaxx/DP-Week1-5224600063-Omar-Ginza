#include "RunSession.h"
#include "FixedInputGenerator.h"
#include "BasicScoringRule.h"
#include "SimpleRewardRule.h"

int main() {
    FixedInputGenerator inputGen;
    BasicScoringRule    scoringRule;
    SimpleRewardRule    rewardRule;

    RunSession session(&inputGen, &scoringRule, &rewardRule, 3);
    session.run();

    return 0;
}
