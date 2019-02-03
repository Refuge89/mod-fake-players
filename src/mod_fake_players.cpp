/* 
 <---------------------------------------------------------------------------> 
 - Developer(s): Nusky 
 - Complete: 60% 
 - Date: 2019-02-03 00:20:00 
 - Last Modified by: Nusky 
 - Last Modified time: 2019-02-03 00:20:00  
 <---------------------------------------------------------------------------> 
*/

#include "ScriptMgr.h"
#include "Config.h"
#include <Player.h>

class Fake_Players : public PlayerScript
{
public:
	Fake_Players() : PlayerScript("Fake_Players") {}

    void Update(uint32 p_time)
    {
        // If Fake WHO List system on then change player position with every SavePlayer Interval (usually 15min) 
        if (sWorld->getBoolConfig(CONFIG_FAKE_WHO_LIST)) 
            CharacterDatabase.PExecute("UPDATE characters_fake SET zone = (FLOOR(50 * RAND()) + 1) WHERE online > 1"); 
            CharacterDatabase.PExecute("UPDATE characters_fake SET level = level+1 WHERE online > 1 AND level < 5"); 
    }
    void HandleMessagechatOpcode(WorldPacket& recvData)
    {
        // If Fake WHO List system on then show player DND 
        if (sWorld->getBoolConfig(CONFIG_FAKE_WHO_LIST)) 
        {
            sWorld->SendWorldText('|cff0000ffYou are been ignored!'); 
            return; 
        } 
        else 
        { 
            SendPlayerNotFoundNotice(to);
            return;
        }
    }
    void HandleWhoOpcode(WorldPacket& recvData)
    {      
        if (sWorld->getBoolConfig(CONFIG_FAKE_WHO_LIST) && displaycount < 49) 
        { 
            // Fake players on WHO LIST                            0,   1,    2,   3,    4,   5 
            QueryResult result = CharacterDatabase.Query("SELECT name,race,class,level,zone,gender FROM characters_fake WHERE online>1 AND level > 3"); 
            if (result) 
            { 
                do 
                { 
                    Field *fields = result->Fetch(); 
     
                    std::string pname = fields[1].GetString();    // player name 
                    std::string gname;                                // guild name 
                    uint32 lvl = fields[4].GetUInt32();                // player level 
                    uint32 class_ = fields[3].GetUInt32();            // player class 
                    uint32 race = fields[2].GetUInt32();            // player race 
                    uint32 pzoneid = fields[5].GetUInt32();            // player zone id 
                    uint8 gender = fields[6].GetUInt8();            // player gender  
                    data << pname;                              // player name 
                    data << gname;                              // guild name 
                    data << uint32(lvl);                        // player level 
                    data << uint32(class_);                     // player class 
                    data << uint32(race);                       // player race 
                    data << uint8(gender);                      // player gender 
                    data << uint32(pzoneid);                    // player zone id 
     
                    if ((++matchcount) == 49) 
                        break; 
                } while (result->NextRow()); 
            } 
        }
        data.put(0, matchcount);                            // insert right count, count displayed
    }
};

void AddFake_PlayersScripts()
{
	new Fake_Players;
}