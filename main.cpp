#include <iostream>
#include "Server.hpp"
#include "Connection.hpp"

using namespace std;

int main()
{
    Server *gameServer = new Server(4500);

    gameServer->Close();

    delete gameServer;

    return 0;
}
