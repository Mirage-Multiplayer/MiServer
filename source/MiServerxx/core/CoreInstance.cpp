#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>

mimp::CCore *mimp::internal::server::g_CoreInstance = nullptr;

mimp::CCore *mimp::internal::server::GetCoreInstance(void)
{
	return mimp::internal::server::g_CoreInstance;
}

void mimp::internal::server::SetCoreInstance(CCore *svr)
{
	mimp::internal::server::g_CoreInstance = svr;
}