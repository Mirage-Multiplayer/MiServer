#include "server/ServerInstance.hpp"
#include "server/Server.hpp"

mimp::Server* mimp::internal::server::g_ServerInstance = nullptr;

mimp::Server* mimp::internal::server::GetServerInstance(void) {
	return mimp::internal::server::g_ServerInstance;
}

void mimp::internal::server::SetServerInstance(Server* svr) {
	mimp::internal::server::g_ServerInstance = svr;
}