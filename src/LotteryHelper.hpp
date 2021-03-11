//
// Created by Mithrandir on 06/03/2021.
//

#ifndef AZEROTHCORE_LOTTERYHELPER_HPP
#define AZEROTHCORE_LOTTERYHELPER_HPP


class LotteryHelper {
private:

public:

    static std::map<uint32, std::string> GetAllPrizeStr();
    static std::map<uint32, std::string> GetAllPrizeOfLottery(uint32 lotteryId);
    static void AddTicketToPlayer(uint64 CharacterGUID, uint32 lotteryId);
    static std::string GetPriceOfTicketStr();
};


#endif //AZEROTHCORE_LOTTERYHELPER_HPP
