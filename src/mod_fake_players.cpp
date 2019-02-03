/* 
 <---------------------------------------------------------------------------> 
 - Developer(s): Nusky 
 - Complete: %60 
 - Date: 2019-02-03 00:12:34 
 - Last Modified by: Nusky 
 - Last Modified time: 2019-02-03 00:12:34  
 <---------------------------------------------------------------------------> 
*/

#include "ScriptMgr.h"
#include "Config.h"
#include <Player.h>

class Fake_Players : public PlayerScript
{
public:
	Fake_Players() : PlayerScript("Fake_Players") {}

};

void AddFake_PlayersScripts()
{
	new Fake_Players;
}