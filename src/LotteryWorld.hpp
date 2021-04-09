//
// Created by mithrandir on 12/03/2021.
//

#ifndef AZEROTHCORE_LOTTERYWORLD_HPP
#define AZEROTHCORE_LOTTERYWORLD_HPP

#include "mutex"

class LotteryWorld : public WorldScript {
    static bool isWorldDown;
public:
    LotteryWorld() : WorldScript("LotteryWorld") {};

    void OnStartup() override;
    static void Calculator();

};


#endif //AZEROTHCORE_LOTTERYWORLD_HPP
