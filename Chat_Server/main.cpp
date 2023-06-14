#include "Chat_ServerTCP.h"

int main() {

    Chat_ServerTCP server;
    if (server.createSocket())
    {
        server.run();
    }

    return 0;
}