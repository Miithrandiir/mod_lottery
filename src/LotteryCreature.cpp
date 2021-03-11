//
// Created by Mithrandir on 06/03/2021.
//

#include "LotteryCreature.hpp"
#include "LotteryHelper.hpp"
#include "Config.h"

bool LotteryCreature::OnGossipHello(Player *player, Creature *creature) {

    ReturnToMainPage(player, creature);

    return true;
}

bool LotteryCreature::OnGossipSelect(Player *player, Creature *creature, uint32 /*sender*/, uint32 action) {

    if (!player || !creature)
        return true;

    //Avoid exception in switch statement
    if (data.find(player->GetGUID()) == data.end()) {
        data[player->GetGUID()] = STATE::MAIN_MENU;
    }

    ClearGossipMenuFor(player);

    if (action == 0) {
        ReturnToMainPage(player, creature);
        return true;
    }

    //INTERCEPT AND CHECK
    switch (data[player->GetGUID()]) {
        case STATE::SHOW_PRIZES:
            PrizeShow(player, creature, action);
            return true;
            break;
        case STATE::BUY_TICKET:
            buyTicket(player, creature, action);
            return true;
            break;
        case STATE::MAIN_MENU:
            break;
    }


    switch (action) {
        case 1: {
            data[player->GetGUID()] = STATE::SHOW_PRIZES;

            std::map<uint32, std::string> allPrizes = LotteryHelper::GetAllPrizeStr();

            for (const auto &item : allPrizes) {
                //FIX: check if (item.first*1000) < MAX(uint32)
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, item.second, GOSSIP_SENDER_MAIN, item.first);
            }

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "<- Menu principal", GOSSIP_SENDER_MAIN, 0);

            SendGossipMenuFor(player, 68, creature);

            break;
        }

        case 2: {
            data[player->GetGUID()] = STATE::BUY_TICKET;
            std::map<uint32, std::string> allPrizes = LotteryHelper::GetAllPrizeStr();

            for (const auto &item : allPrizes) {
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, item.second, GOSSIP_SENDER_MAIN, item.first);
            }

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "<- Menu principal", GOSSIP_SENDER_MAIN, 0);

            SendGossipMenuFor(player, 68, creature);

            break;
        }
    }

    return true;
}


void LotteryCreature::ReturnToMainPage(Player *player, Creature *creature) {

    data[player->GetGUID()] = STATE::MAIN_MENU;

    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Voir les lots", GOSSIP_SENDER_MAIN, 1);
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Acheter un ticket ! " + LotteryHelper::GetPriceOfTicketStr(),
                     GOSSIP_SENDER_MAIN, 2);
    if (player->IsGameMaster()) {
        AddGossipItemFor(player, GOSSIP_ICON_TABARD, "Administrer la lotterie", GOSSIP_SENDER_MAIN, 3);
    }

    SendGossipMenuFor(player, 68, creature);

}

void LotteryCreature::PrizeShow(Player *player, Creature *creature, uint32 action) {
    std::map<uint32, std::string> prizes = LotteryHelper::GetAllPrizeOfLottery(action);

    if(prizes.empty()) {
        ChatHandler(player->GetSession()).SendSysMessage("Aucun gain pour cette loterie");
        ReturnToMainPage(player,creature);
    }

    for (const auto &item : prizes) {
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, item.second, GOSSIP_SENDER_MAIN, action);
    }
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "<- Menu principal", GOSSIP_SENDER_MAIN, 0);
    SendGossipMenuFor(player, 68, creature);
}

void LotteryCreature::buyTicket(Player *player, Creature *creature, uint32 lotteryId) {

    if (!player)
        return;

    std::string currency = sConfigMgr->GetStringDefault("Lottery.currency", "MONEY");
    std::cout << currency << std::endl;
    std::cout << std::to_string(lotteryId) << std::endl;
    if (currency == "MONEY") {
        uint32 amount = sConfigMgr->GetIntDefault("Lottery.currencyAmount", 5000000);
        if (player->HasEnoughMoney(amount)) {
            player->SetMoney(player->GetMoney() - amount);
            LotteryHelper::AddTicketToPlayer(player->GetGUID(), lotteryId);
            ChatHandler(player->GetSession()).SendSysMessage("Vous êtes bien inscrit à la lotterie !");
            CloseGossipMenuFor(player);
        } else {
            ChatHandler(player->GetSession()).SendSysMessage("Vous n'avez pas assez d'argent");
            ChatHandler(player->GetSession()).SendSysMessage(LotteryHelper::GetPriceOfTicketStr().c_str());
            ReturnToMainPage(player, creature);
        }

    }

}

void AddSC_LotteryCreature() {
    new LotteryCreature();
}