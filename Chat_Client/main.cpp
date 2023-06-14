#include "Chat_ClientTCP.h"

int main() {

    Chat_ClientTCP client;

    if (client.createSock())
    {
        client.connectServer();
    }

    return 0;
}
