#include <stdio.h>
#include "Bot.h"

int main()
{
	Bot *chatBot = new Bot("NICK royalbotjr\r\n", "USER royalbotjr\r\n", "PASS oauth:p7vxe7h7nvn0oz4n8yqosapfrlwa4w\r\n");

	chatBot->Startup();
	chatBot->login();
	chatBot->mainLoop();

	return 0;
}