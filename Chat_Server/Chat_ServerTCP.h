#pragma once

#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MESSAGE_LENGTH 1024 // Буфер для данных
#define PORT 7777 // Используемый номер порта

class Chat_ServerTCP
{
public:
	~Chat_ServerTCP();
	bool createSocket();
	void run();
	void communication();
private:
	struct sockaddr_in serveraddress, client;
	socklen_t length;
	int socket_file_descriptor, connection, bind_status, connection_status;
	char message[MESSAGE_LENGTH];
};