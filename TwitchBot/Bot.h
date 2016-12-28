#pragma once
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "KeyPress.h"

#pragma comment(lib, "Ws2_32.lib")


class Bot
{
	private:

		char* botName;	
		char* botNick;
		char* oath;

		SOCKET connectSocket;
		KeyPress kp;

	public:
		Bot(char* name, char*nick, char* oath);
		int Startup();
		int login();
		int sendData(char *message);
		int mainLoop();
		int messageHandler(char* message);
		void sendPong();
		void command(std::string);
		~Bot();
};