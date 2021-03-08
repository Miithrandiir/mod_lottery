//
// Created by Mithrandir on 06/03/2021.
//

#include "LotteryCreature.hpp"
#include "LotteryHelper.hpp"

bool LotteryCreature::OnGossipHello(Player *player, Creature *creature) {

    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Voir les lots", GOSSIP_SENDER_MAIN, 1);
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Achter un ticket !", GOSSIP_SENDER_MAIN, 2);
    if (player->IsGameMaster()) {
        AddGossipItemFor(player, GOSSIP_ICON_TABARD, "Administrer la lotterie", GOSSIP_SENDER_MAIN, 3);
    }

    SendGossipMenuFor(player, 68, creature);
}

bool LotteryCreature::OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action) {

    if (creature->GetGUID() == sender) {

        switch (action) {
            /*
             * SHOW ALL PRIZES
             */
            case 1: {
                ClearGossipMenuFor(player);
                std::map<uint32, std::string> allPrizes = LotteryHelper::GetAllPrizeStr();

                for (const auto &item : allPrizes) {
                    //TODO: check if (item.first*1000) < MAX(uint32)
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, item.second, GOSSIP_SENDER_MAIN, item.first * 1000);
                }

                SendGossipMenuFor(player, 68, creature);
            }
                break;
            case 2: {

                ClearGossipMenuFor(player);
                std::map<uint32, std::string> allPrizes = LotteryHelper::GetAllPrizeStr();
            }
                break;
        }

    }

}
