
#include <iostream>
#include <thread>
#include <vector>
#include "winSocketpair.h"

WinSockPair winSockPair("/temp/winsocketpair.sock");

void serverTh(int64_t srvSock, int64_t cliSock)
{
    std::stringstream ss;
    char recvMsg[200];

    // recv will not get whole message sometimes because sys buffers may be full.
    // For this simple example, it is alright
    int msgSize = recv(srvSock, recvMsg, sizeof(recvMsg), 0);
    recvMsg[msgSize] = '\0';
    std::cout << srvSock << ": Message received from " << cliSock << ": " << recvMsg << std::endl;
    ss << srvSock << " Server Message to Client " << cliSock << std::endl;
    send(srvSock, ss.str().c_str(), (int32_t)ss.str().length(), 0);
}

void clientTh(int64_t srvSock, int64_t cliSock)
{
    std::stringstream ss;
    char recvMsg[200];

    ss << cliSock << " Client Message to Server " << srvSock << std::endl;
    send(cliSock, ss.str().c_str(), (int32_t)ss.str().length(), 0);
    int msgSize = recv(cliSock, recvMsg, sizeof(recvMsg), 0);
    recvMsg[msgSize] = '\0';
    std::cout << cliSock << ": Message received from " << srvSock << ": " << recvMsg << std::endl;
}

int main()
{
#define MAX_PAIRS       1024

    int64_t socks[2] = {0, 0};
    std::vector<std::thread> srvThreads;
    std::vector<std::thread> cliThreads;

    for (int i = 0; i < MAX_PAIRS; i++)
    {
        if (winSockPair.get_sockPair(socks) )
        {
            std::cout << "Get Pair Returned: socks[0] = " << socks[0] << ", socks[1] = " << socks[1] << std::endl;
            srvThreads.push_back(std::thread(serverTh, socks[0], socks[1]));
            cliThreads.push_back(std::thread(clientTh, socks[0], socks[1]));
        }
        else
        {
            std::cout << "WinSockPair Failed: socks[0] = " << socks[0] << ", socks[1] = " << socks[1] << std::endl; 
        }
    }
    for (std::thread& th: srvThreads)
    {
        th.join();
    }
    for (std::thread& th: cliThreads)
    {
        th.join();
    }
    srvThreads.clear();
    cliThreads.clear();
}
