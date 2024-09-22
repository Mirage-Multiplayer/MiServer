#include <MiServerxx/server/ServerInstance.hpp>
#include <MiServerxx/server/Server.hpp>

mimp::CServer *mimp::internal::server::g_ServerInstance = nullptr;

mimp::CServer *mimp::internal::server::GetServerInstance(void)
{
	return mimp::internal::server::g_ServerInstance;
}

void mimp::internal::server::SetServerInstance(CServer *svr)
{
	mimp::internal::server::g_ServerInstance = svr;
}