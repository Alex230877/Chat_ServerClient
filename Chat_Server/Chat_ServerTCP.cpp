#include "Chat_ServerTCP.h"
#include <arpa/inet.h>

Chat_ServerTCP::~Chat_ServerTCP()
{
    // Завершение соединения
    close(socket_file_descriptor);
}

bool Chat_ServerTCP::createSocket()
{
    // Создаем сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        std::cout << "Socket not created!" << std::endl;
        return false;
    }
    // Устанавливаем адрес хоста
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Задаем номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    
    // Привяжем сокет
    bind_status = bind(socket_file_descriptor, (struct sockaddr*)&serveraddress,
        sizeof(serveraddress));
    // если не удалось
    if (bind_status == -1) {
        std::cout << "Socket binding failed!" << std::endl;
        return false;;
    }
    return true;
}

void Chat_ServerTCP::run()
{
    // Переводим сокет в режим ожидания запросов со стороны клиентов
    connection_status = listen(socket_file_descriptor, 5);
    // если не удалось
    if (connection_status == -1) {
        std::cout << "Socket is unable to listen for new connections!" << std::endl;
        exit(1);
    }
    else {
        std::cout << "Server is listening for new connection..." << std::endl;
    }

    length = sizeof(client);
    // Создаём для общения с клиентом новый сокет и возвращаем его дескриптор
    connection = accept(socket_file_descriptor, (struct sockaddr*)&client, &length);
    // если не удалось
    if (connection == -1) {
        std::cout << "Server is unable to accept the data from client!" << std::endl;
        exit(1);
    }

    std::cout << "Server: got connection from " << inet_ntoa(client.sin_addr)  << " port " << ntohs(client.sin_port) << std::endl;
    communication();
}

void Chat_ServerTCP::communication()
{
    // Отправка и получение данных
    while (1) {
        // Отправка сообщения
        bzero(message, MESSAGE_LENGTH);
        std::cout << "Message from Server: ";
        std::cin.getline(message, MESSAGE_LENGTH);
        ssize_t bytes = write(connection, message, sizeof(message));
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if (bytes >= 0) {
            std::cout << "Data successfully sent to the client!" << std::endl;
        }

        // Прием сообщения
        bzero(message, MESSAGE_LENGTH);
        read(connection, message, sizeof(message));
        if (strncmp("end", message, 3) == 0) {
            std::cout << "Client Exited" << std::endl;
            std::cout << "Press any key to exit..." << std::endl;
            std::cin.get();
            return;
        }
        std::cout << "Message from client: " << message << std::endl;
    }
}


