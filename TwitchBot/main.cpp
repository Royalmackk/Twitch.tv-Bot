#include <stdio.h>
#include "Bot.h"

int main()
{
	Bot *chatBot = new Bot("NICK  //username in lower", "USER //bots username", "PASS oauth://oauth key");

	chatBot->Startup();
	chatBot->login();
	chatBot->mainLoop();

	return 0;
}