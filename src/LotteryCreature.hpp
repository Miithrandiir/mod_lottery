//
// Created by Mithrandir on 06/03/2021.
//

#ifndef AZEROTHCORE_LOTTERYCREATURE_HPP
#define AZEROTHCORE_LOTTERYCREATURE_HPP


class LotteryCreature : public CreatureScript {

public:
    LotteryCreature() : CreatureScript("LotteryCreatureScript") {}

    bool OnGossipHello(Player* /*player*/, Creature* /*creature*/) override;
    bool OnGossipSelect(Player* /*player*/, Creature* /*creature*/, uint32 /*sender*/, uint32 /*action*/) override;

};


#endif //AZEROTHCORE_LOTTERYCREATURE_HPP
