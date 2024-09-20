#ifndef __MISERVER_SAMPQUERY_HPP
#define __MISERVER_SAMPQUERY_HPP
#include <MiServerxx/server/Server.hpp>
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
#endif