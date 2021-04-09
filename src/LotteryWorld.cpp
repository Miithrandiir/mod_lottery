//
// Created by mithrandir on 12/03/2021.
//

#include "LotteryWorld.hpp"
#include "LotteryHelper.hpp"
#include "thread"
#include "Config.h"
#include <random>


void LotteryWorld::OnStartup() {

    std::cout << "[Lottery] Starting thread to calculate lottery winner" << std::endl;
    std::thread t1 (Calculator);
    t1.join();
    std::cout << "[Lottery] Thread started, enjoy !" << std::endl;
}

void LotteryWorld::Calculator() {

    do {

        std::map<uint32, std::string> result = LotteryHelper::GetLotteryNeedToBeCalculate();

        if(!result.empty()) {
            std::cout << "[Lottery] " << result.size() << " lotteries need to be calculate";

            for(const auto& item : result) {

                //Alert player that we calculate the winner of the lottery
                for(const auto& item1 : sObjectAccessor->GetPlayers())
                {
                    ChatHandler(item1.second->GetSession()).SendGlobalGMSysMessage(("[Lottery] Calcul de la lotterie : "+ item.second).c_str());
                }

                std::map<uint32, uint32> participants = LotteryHelper::GetAllParticipant(item.first);

                if(participants.size() > sConfigMgr->GetIntDefault("Lottery.minimumParticipants", 0)) {

                    //If we have enough participants ...
                    std::random_device rd;
                    std::mt19937_64 eng(rd());
                    std::uniform_int_distribution<uint32> distr(0, participants.size()-1);

                    uint32 winnerPlace = distr(eng);
                    //And the winner is :
                    for(std::map<uint32,uint32>::iterator it = participants.begin(); it != participants.end(); it++)
                    {
                        if(std::distance(participants.begin(), it) == winnerPlace) {
                            //This is our winner !!
                            auto players = sObjectAccessor->GetPlayers();
                            Player* player = players.find(it->second)->second;
                            ChatHandler(player->GetSession()).SendGlobalGMSysMessage(("[Loterie] Vous êtes l'heureux gagnant de la lotterie : " + item.second).c_str());
                            //ChatHandler(player->GetSession()).SendGlobalGMSysMessage(("[Loterie] Regardez votre boîte aux lettres "));
                        }
                    }



                } else {
                    std::cout << "[Lottery] Can't calculate lottery (id: " << std::to_string(item.first) << " ) : Not enough participants" << std::endl;
                    for(const auto& item1 : sObjectAccessor->GetPlayers())
                    {
                        ChatHandler(item1.second->GetSession()).SendGlobalGMSysMessage(("[Lottery] Lotterie annulé car il n'y a pas assez de participants : "+ item.second).c_str());
                    }

                }

                LotteryHelper::MarkLotteryHasBeenDone(item.first);

            }

        }

        std::this_thread::sleep_for(std::chrono::minutes(30));

    } while(LotteryWorld::isWorldDown);

}
