#include <iostream>
#include "Server.hpp"
#include "Connection.hpp"

using namespace std;

int main()
{
    bool running = true;

    Server *gameServer = new Server(4500);

    while (running) {
        if (gameServer->CheckForNewConnections() == 1) {
                running = false;
        }
        //gameServer->ReceiveConnections();
    }


    gameServer->Close();

    delete gameServer;

    return 0;
}
