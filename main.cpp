#include <iostream>
#include "Server.hpp"
#include "Connection.hpp"

using namespace std;

int main()
{
    bool running = true;

    Server *gameServer = new Server(4500);

    while (running) {
        gameServer->CheckForNewConnections();

    }


    gameServer->Close();

    delete gameServer;

    return 0;
}
