//
// Created by Mithrandir on 06/03/2021.
//

#ifndef AZEROTHCORE_LOTTERYCREATURE_HPP
#define AZEROTHCORE_LOTTERYCREATURE_HPP


#include <mutex>

class LotteryCreature : public CreatureScript {
private:
    enum STATE {
        MAIN_MENU,
        BUY_TICKET,
        SHOW_PRIZES,
    };
    std::map<uint64, STATE> data;
    std::mutex mutex;
public:
    LotteryCreature() : CreatureScript("LotteryCreatureScript") {}

    bool OnGossipHello(Player * /*player*/, Creature * /*creature*/) override;

    bool OnGossipSelect(Player * /*player*/, Creature * /*creature*/, uint32 /*sender*/, uint32 /*action*/) override;

    void ReturnToMainPage(Player *, Creature *);

    void PrizeShow(Player *, Creature *, uint32);

    void buyTicket(Player *, Creature *, uint32);

    void OnUpdate(Creature* /*obj*/, uint32 /*diff*/) override;
};


#endif //AZEROTHCORE_LOTTERYCREATURE_HPP
