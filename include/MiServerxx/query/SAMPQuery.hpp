#pragma once
#include <MiServerxx/core/Core.hpp>
namespace mimp
{
    namespace internal
    {
        namespace query
        {
            int SAMPQueryHandler(SOCKET sListen, int iAddrSize, struct sockaddr_in client, char *pBuffer);
        }
    }
}