#include <MiServerxx/query/SAMPQuery.hpp>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <cstring>

static int handleServerInformation(char *reader)
{
    mimp::CCore *core = mimp::internal::server::GetCoreInstance();
    mimp::ServerInfo info = core->getInfo();

    *(unsigned char *)reader = 0;
    reader += sizeof(unsigned char);
    // playerCount
    *(unsigned short *)reader = core->GetNetGame()->GetPlayerPool()->GetCount();
    reader += sizeof(unsigned short);
    // maxPlayers
    *(unsigned short *)reader = static_cast<unsigned short>(core->GetNetGame()->GetPlayerPool()->GetMax());
    reader += sizeof(unsigned short);
    // hostname
    int hostnameLen = info.hostname.length();
    *(unsigned int *)reader = hostnameLen;
    reader += sizeof(unsigned int);

    strncpy(reader, info.hostname.c_str(), hostnameLen);
    reader += hostnameLen;
    // gamemode
    int gamemodeLen = info.gamemode.length();
    *(unsigned int *)reader = gamemodeLen;
    reader += sizeof(unsigned int);

    strncpy(reader, info.gamemode.c_str(), gamemodeLen);
    reader += gamemodeLen;
    // language
    int languageLen = info.lang.length();
    *(unsigned int *)reader = languageLen;
    reader += sizeof(unsigned int);

    strncpy(reader, info.lang.c_str(), languageLen);
    reader += languageLen;

    return 1;
}

static int handleClientList(char *reader)
{
    mimp::CCore *core = mimp::internal::server::GetCoreInstance();
    const int sz = core->GetNetGame()->GetPlayerPool()->GetCount();
    if (sz == 0)
        return 0;

    *(unsigned short *)reader = (unsigned short)sz;
    reader += sizeof(unsigned short);

    for (mimp::CPlayer *p : *core->GetNetGame()->GetPlayerPool())
    {
        if (p == nullptr)
            continue;
        *(unsigned char *)reader = p->getNickName().length();
        reader += sizeof(char);

        strncpy(reader, p->getNickName().c_str(), p->getNickName().length());
        reader += p->getNickName().length();

        *(unsigned int *)reader = p->getScore();
        reader += sizeof(unsigned int);
    }
    return 1;
}

static int handleDetailedInformation(char *reader)
{
    mimp::CCore *core = mimp::internal::server::GetCoreInstance();
    const int sz = core->GetNetGame()->GetPlayerPool()->GetCount();
    if (sz == 0)
        return 0;

    *(unsigned short *)reader = (unsigned short)sz;
    reader += sizeof(unsigned short);

    for (mimp::CPlayer *p : *core->GetNetGame()->GetPlayerPool())
    {
        if (p == nullptr)
            continue;
        *(unsigned char *)reader = p->getPlayerId();
        reader += sizeof(char);

        *(unsigned char *)reader = p->getNickName().length();
        reader += sizeof(char);

        strncpy(reader, p->getNickName().c_str(), p->getNickName().length());
        reader += p->getNickName().length();

        *(unsigned int *)reader = p->getScore();
        reader += sizeof(unsigned int);

        *(unsigned int *)reader = p->getPing();
        reader += sizeof(unsigned int);
    }
    return 1;
}

int mimp::internal::query::SAMPQueryHandler(SOCKET sListen, int iAddrSize, struct sockaddr_in client, char *pBuffer)
{
    char opt = pBuffer[10];
    char serverResponse[512];
    char *reader = (serverResponse + 11);
    std::memcpy(serverResponse, pBuffer, 15);

    switch (opt)
    {
    case 'i':
    {
        if (handleServerInformation(reader) != 0)
            sendto(sListen, serverResponse, 512, 0, reinterpret_cast<struct sockaddr *>(&client), iAddrSize);
        break;
    }
    case 'r':
    {
        break;
    }
    case 'c':
    {
        if (handleClientList(reader) != 0)
            sendto(sListen, serverResponse, 512, 0, reinterpret_cast<struct sockaddr *>(&client), iAddrSize);
        break;
    }
    case 'd':
    {
        if (handleDetailedInformation(reader) != 0)
            sendto(sListen, serverResponse, 512, 0, reinterpret_cast<struct sockaddr *>(&client), iAddrSize);
        break;
    }
    case 'x':
    {
        break;
    }
    case 'p':
    {
        sendto(sListen, pBuffer, 15, 0, reinterpret_cast<struct sockaddr *>(&client), iAddrSize);
        break;
    }

    default:
        break;
    }
    return 1;
};