#include "Server.hpp"
#include "Connection.hpp"

#include <iostream>

using namespace std;

int main()
{
    bool running = true;

    Server *gameServer = new Server(9500);
    gameServer->Listen();

    while (running) {
        if (gameServer->CheckForNewConnections() == -1) {
            running = false;
        };
        gameServer->ReceiveConnections();
    }


    delete gameServer;

    return 0;
}
