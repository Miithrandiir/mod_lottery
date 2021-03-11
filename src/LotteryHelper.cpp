//
// Created by Mithrandir on 06/03/2021.
//

#include "LotteryHelper.hpp"
#include "Config.h"

/**
 * TYPE OF LOTTERY_GAIN
 * TYPE 0 : ARMOR
 * TYPE 1 : SPELL
 * TYPE 2 : MONEY
 */

std::map<uint32, std::string> LotteryHelper::GetAllPrizeStr() {


    std::map<uint32, std::string> allPrize;

    QueryResult result = CharacterDatabase.PQuery("SELECT id, lotteryName FROM lottery WHERE beginDate <= NOW() AND endDate >= NOW()");

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

std::map <uint32, std::string> LotteryHelper::GetAllPrizeOfLottery(uint32 lotteryId) {
    std::cout << "[DEBUG] Lottery ID" << std::to_string(lotteryId) << std::endl;
    std::map<uint32, std::string> res;
    QueryResult result = CharacterDatabase.PQuery("SELECT id, type, typeId FROM lottery_gain WHERE lotteryId = %u", lotteryId);

    if(result)
    {
        do {

            try {
                Field *fields = result->Fetch();
                std::stringstream name;

                if (fields[1].GetUInt32() == 0) {
                    name << "[ARMURE]";
                    const ItemLocale* test =  sObjectMgr->GetItemLocale(fields[2].GetUInt32());
                    name << test->Name[LOCALE_frFR];

                } else if (fields[1].GetUInt32() == 1) {
                    name << "[SPELL]";
                    auto test = sSpellMgr->GetSpellInfo(fields[2].GetUInt32());
                    name << test->SpellName;
                } else if (fields[1].GetUInt32() == 2) {
                    name << "[MONEY]";
                    name << std::to_string(fields[2].GetUInt32()/10000) << " PO";
                } else {
                    name << "[INCONNU]";
                }

                res.insert(std::make_pair(fields[1].GetUInt32(), name.str()));

            } catch(out_of_range& /*e*/) {
                std::cout << "[Lottery] Error when reading all prize from lottery (id: " << std::to_string(lotteryId) <<  " )" << std::endl;
            }


        } while(result->NextRow());
    }
    return res;
}

void LotteryHelper::AddTicketToPlayer(uint64 characterGUID, uint32 lotteryId) {
    CharacterDatabase.PExecute("INSERT INTO lottery_member (characterId, lotteryId) VALUES (%u,%u)", characterGUID, lotteryId);
}

std::string LotteryHelper::GetPriceOfTicketStr() {

    std::stringstream msg;
    std::string currency = sConfigMgr->GetStringDefault("Lottery.currency", "MONEY");
    msg << "[" << currency << "] ";

    if(currency == "MONEY") {
        int amount = sConfigMgr->GetIntDefault("Lottery.currencyAmount", 5000000);
        msg << std::to_string(amount/10000) << " PO";

    } else if(currency == "ITEM") {
        auto itemLocale = sObjectMgr->GetItemLocale(sConfigMgr->GetIntDefault("Lottery.currencyId", 0));
        auto itemAmount = sConfigMgr->GetIntDefault("Lottery.currencyAmount", 1);
        msg << std::to_string(itemAmount) << itemLocale->Name[LOCALE_frFR];
    }

    return msg.str();

}
