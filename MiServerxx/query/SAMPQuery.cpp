#include <MiServerxx/query/SAMPQuery.hpp>

static void HandleInformation(char __cp[1024])
{
}

int mimp::internal::query::SAMPQueryHandler(SOCKET sListen, int iAddrSize, struct sockaddr_in client, char *pBuffer)
{
    char opt = pBuffer[10];
    switch (opt)
    {
    case 'i':
    {
        break;
    }
    case 'r':
    {
        break;
    }
    case 'c':
    {
        break;
    }
    case 'd':
    {
        break;
    }
    case 'x':
    {
        break;
    }
    case 'p':
    {
        break;
    }

    default:
        break;
    }
};