#include "Bot.h"
#include <vector>

#define PORT  "6667"
#define SERVER_NAME "irc.chat.twitch.tv"

Bot::Bot(char*name, char *nick, char* oath)
{
	this->botName = name;	
	this->botNick = nick;
	this->oath = oath;
	connectSocket = INVALID_SOCKET;
}


Bot::~Bot()
{
	delete(this);
}

int Bot::Startup()
{
	//Create WSAData
	WSADATA wsaData;
	int iResult = 0;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		std::cout << "Error is WSA Startup" << std::endl;
		WSACleanup();
		return -1;
	}
	else	
		std::cout << "WSA Startup Successful" << std::endl;
	
	//Create addrinfo
	struct addrinfo *results = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	//setup addrinfo
	iResult = getaddrinfo(SERVER_NAME, PORT, &hints, &results);
	if (iResult != 0)
	{
		std::cout << "GetAddrInfo failed: " << iResult << std::endl;
		WSACleanup();
		return -1;
	}
	else
		std::cout << "GetAddrInfo Successful" << std::endl;

	//Check to see if connection socket is not invalid
	connectSocket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
	if (connectSocket == INVALID_SOCKET)
	{
		std::cout << "Error in socket" << std::endl;
		WSACleanup();
		freeaddrinfo(results);
		return -1;
	}
	else
		std::cout << "Connection Successful" << std::endl;

	//Connect to socket
	iResult = connect(connectSocket, results->ai_addr, (int)results->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "Connection to server failed" << std::endl;
		closesocket(connectSocket);
		connectSocket = INVALID_SOCKET;
		WSACleanup();
		return -1;
	}
	else
		std::cout << "Connection to socket successful" << std::endl;

	freeaddrinfo(results);	

	return 0;
}

int Bot::login()
{
	//Used to send login data to the Twitch Socket
	int i = 0;
	int iResult = 0;
	const int maxData = 256;
	char recvData[maxData];

	//Two process loops
	//First sends login information to Twitch.tv Servers
	//Second pass sends data for which channel to join
	do
	{
		switch (i)
		{
			case 0:
				sendData(oath);
				sendData(botNick);
				sendData(botName);
			break;

			case 1:
				sendData("JOIN #channelname\r\n");
			break;

			default:
			break;
		}

		iResult = recv(connectSocket, recvData, maxData - 1, 0);
		recvData[iResult] = '\0';

		std::cout << recvData << std::endl;

		if (iResult == 0)
		{
			std::cout << " Connection Closed." << std::endl;
		}

		i++;

	} while (i < 2);

	return 0;

}

int Bot::sendData(char *message)
{
	//Send data to connected socket
	int bytesSent = send(connectSocket, message, (int)strlen(message), 0);
	if (bytesSent == SOCKET_ERROR)
	{
		std::cout << "Sending failed." << std::endl;
		closesocket(connectSocket);
		WSACleanup();
		return -1;
	}

	return 0;
}

int Bot::mainLoop()
{
	//Main loop for the bot, will loop forever recieveing user messages
	
	const int maxData = 2056;
	char buf[maxData];
	int res = 0;

	while (true)
	{
		res = recv(connectSocket, buf, maxData - 1, 0);
		buf[res] = '\0';

		if (res == 0)
		{
			std::cout << "Connection Closed" << std::endl;
			WSACleanup();
			closesocket(connectSocket);
		}
		else
		{
			messageHandler(buf);
		}
	}
	return 0;
}

int Bot::messageHandler(char* message)
{	
	//Split string based on # or : characters and store them into a array of strings
	std::string messages[100];
	char *token;
	int i = 0;

	token = strtok(message, ":#");
	while (token != NULL)
	{
		messages[i] = token;
		token = strtok(NULL, ":#");
		i++;
	}

	switch (i)
	{
		case 2:
			sendPong();
		break;

		case 3:
			command(messages[2]);
		break;
	}
	return 0;
}

void Bot::sendPong()
{
	//used to bounce back connection status to Twitch.tv
	sendData("PONG :tmi.twitch.tv");
	std::cout << "Pong sent" << std::endl;
}


//Compares the command message with a list of set commands
void Bot::command(std::string message)
{
	char *command = new char[message.length()];
	strcpy(command, message.c_str());
	
	if (strcmp(command, "up\r\n") == 0)
	{
		//up Arrow
		kp.pressKey(1);
	}
	else if (strcmp(command, "down\r\n") == 0)
	{
		//down arrow
		kp.pressKey(2);
	}
	else if (strcmp(command, "left\r\n") == 0)
	{
		//down arrow
		kp.pressKey(3);
	}
	else if (strcmp(command, "right\r\n") == 0)
	{
		//down arrow
		kp.pressKey(4);
	}
	else if (strcmp(command, "bA\r\n") == 0)
	{
		//Z Key
		kp.pressKey(5);
	}
	else if (strcmp(command, "bB\r\n") == 0)
	{
		//X Key
		kp.pressKey(6);
	}
	else if (strcmp(command, "start\r\n") == 0)
	{
		//Enter Key
		kp.pressKey(7);
	}
}