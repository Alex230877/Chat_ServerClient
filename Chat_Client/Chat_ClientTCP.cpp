#include "Chat_ClientTCP.h"

Chat_ClientTCP::~Chat_ClientTCP()
{
	// Завершение соединения
	close(socket_file_descriptor);
}

bool Chat_ClientTCP::createSock()
{
    // Создаем сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        std::cout << "Socket not created!" << std::endl;
        return false;
    }

    // Устанавливаем адрес 
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Задаем номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
	return true;
}

void Chat_ClientTCP::connectServer()
{
    // Устанавливаем соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        std::cout << "No connection to the server!" << std::endl;
        exit(1);
    }
    std::cout << "Connection to server OK." << std::endl;
    communication();
}

void Chat_ClientTCP::communication()
{
    // Взаимодействие с сервером
    while (1) {
        // Читаем сообщения от сервера
        bzero(message, sizeof(message));
        // Ждем ответа от сервера
        read(socket_file_descriptor, message, sizeof(message));
        std::cout << "Message from server: " << message << std::endl;
        
        // Отправляем сообщения серверу
        bzero(message, sizeof(message));
        std::cout << "Message from client: ";
        std::cin.getline(message, MESSAGE_LENGTH);
        if ((strncmp(message, "end", 3)) == 0) {
            write(socket_file_descriptor, message, sizeof(message));
            std::cout << "Client Exit" << std::endl;
            std::cout << "Press any key to exit..." << std::endl;
            std::cin.get();
            return;
        }
        ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if (bytes >= 0) {
            std::cout << "Data send to the server successfully!" << std::endl;
        }

    }
}
