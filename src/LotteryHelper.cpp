//
// Created by Mithrandir on 06/03/2021.
//

#include "LotteryHelper.hpp"

std::map<uint32, std::string> LotteryHelper::GetAllPrizeStr() {


    std::map<uint32, std::string> allPrize;

    QueryResult result = CharacterDatabase.PQuery("SELECT id, lotteryName FROM lottery");

    if(result)
    {
        do {

            try {
                Field *fields = result->Fetch();
                std::stringstream title;
                title << "Lot #" << fields[0].GetUInt32() << " : " << fields[1].GetString();
                allPrize.insert(std::make_pair(fields[0].GetUInt32(), title.str()));
            } catch(invalid_argument& /*e*/) {
                std::cout << "[LOTTERY SCRIPT] Error when reading a sql row";
            }

        } while(result->NextRow());
    }

    return allPrize;
}
