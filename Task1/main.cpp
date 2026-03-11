#include <cstdlib>
#include <ctime>
#include "RunSession.h"
#include "RandomInputGenerator.h"  
#include "BasicScoringRule.h"
#include "EvenDoubleRewardRule.h"   

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    RandomInputGenerator inputGen;   
    BasicScoringRule     scoringRule;
    EvenDoubleRewardRule rewardRule;  

    RunSession session(&inputGen, &scoringRule, &rewardRule, 3);
    session.run();

    return 0;
}
