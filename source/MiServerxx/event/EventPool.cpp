#include <MiServerxx/event/EventPool.hpp>

#define CALL_EVENT(evt, ...)      \
	if (this->m_##evt == nullptr) \
		return -1;                \
	return this->m_##evt(__VA_ARGS__);

mimp::internal::event::EventPool::EventPool() : m_ServerInit(nullptr),
												m_ServerExit(nullptr),
												m_PlayerConnect(nullptr),
												m_PlayerDisconnect(nullptr),
												m_PlayerSpawn(nullptr)
{
}

int mimp::internal::event::EventPool::Emit(uint16_t id, void *ctx)
{
	switch (id)
	{
	case SERVER_EVENT_SERVERINIT:
	{
		CALL_EVENT(ServerInit)
	}
	case SERVER_EVENT_SERVEREXIT:
	{
		CALL_EVENT(ServerExit)
	}
	case SERVER_EVENT_PLAYERCONNECT:
	{
		OnPlayerConnect_params *p = static_cast<OnPlayerConnect_params *>(ctx);
		CALL_EVENT(PlayerConnect, p->player)
	}
	case SERVER_EVENT_PLAYERDISCONNECT:
	{
		OnPlayerDisconnect_params *p = static_cast<OnPlayerDisconnect_params *>(ctx);
		CALL_EVENT(PlayerDisconnect, p->player, p->reason)
	}
	case SERVER_EVENT_PLAYERSPAWN:
	{
		OnPlayerSpawn_params *p = static_cast<OnPlayerSpawn_params *>(ctx);
		CALL_EVENT(PlayerSpawn, p->player)
	}
	case SERVER_EVENT_PLAYERTEXT:
	{
		OnPlayerText_params *p = static_cast<OnPlayerText_params *>(ctx);
		CALL_EVENT(PlayerText, p->player, p->text);
	}
	case SERVER_EVENT_COMMANDTEXT:
	{
		OnPlayerCommandText_params *p = static_cast<OnPlayerCommandText_params *>(ctx);
		CALL_EVENT(PlayerCMDText, p->player, p->cmd);
	}
	case SERVER_EVENT_PLAYERUPDATE:
	{
		OnPlayerUpdate_params *p = static_cast<OnPlayerUpdate_params *>(ctx);
		CALL_EVENT(PlayerUpdate, p->player);
	}
	default:
	{
		return 1;
	}
	}
}