
#include <iostream>
#include <thread>
#include <vector>
#include "winSocketpair.h"

WinSockPair winSockPair("/temp/winsocketpair.sock");
bool stopThread = false;

void txMsg(int64_t sock)
{
    std::stringstream ss;

    ss << "Message From: " << sock << std::endl;
    send(sock, ss.str().c_str(), (int32_t)ss.str().length(), 0);
}

void rxtxMsg(int64_t sock)
{
    std::stringstream ss;
    char recvMsg[200];

    // recv will not get whole message sometimes because sys buffers may be full.
    // For this simple example, it is alright
    int msgSize = recv(sock, recvMsg, sizeof(recvMsg), 0);
    recvMsg[msgSize] = '\0';
    std::cout << sock << ": Message received : " << recvMsg << std::endl;
    ss << "Message From: " << sock << std::endl;
    send(sock, ss.str().c_str(), (int32_t)ss.str().length(), 0);
}

void th(int64_t sock, bool initiate)
{
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    if (initiate)
    {
        txMsg(sock);
    }
    while (!stopThread)
    {
        int32_t nfds = 0;
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        nfds = (int32_t)sock + 1;

        switch (select(nfds+1, &readfds, NULL, NULL, &tv))
        {
        case 0:
            break;
        case -1:
            std::cout << "Select Error" << std::endl;
            break;
        default:
            rxtxMsg(sock);
            break;
        }
    }
}


int main()
{
#define MAX_PAIRS       10

    int64_t socks[2] = {0, 0};
    std::vector<std::thread> threads;

    for (int i = 0; i < MAX_PAIRS; i++)
    {
        if (winSockPair.get_sockPair(socks) )
        {
            std::cout << "Get Pair Returned: socks[0] = " << socks[0] << ", socks[1] = " << socks[1] << std::endl;
            threads.push_back(std::thread(th, socks[0], false));
            threads.push_back(std::thread(th, socks[1], true));
        }
        else
        {
            std::cout << "WinSockPair Failed: socks[0] = " << socks[0] << ", socks[1] = " << socks[1] << std::endl; 
        }
    }
    // Wait for sometime and then stop all the threads
    Sleep(10 * 1000);
    stopThread = true;
    
    for (std::thread& th: threads)
    {
        th.join();
    }

    threads.clear();
    return 0;
}
