#include "event/EventPool.hpp"

#define CALL_EVENT(evt, ...) if(this->m_ ## evt == nullptr) return -1; \
	return this->m_ ## evt->Call(__VA_ARGS__);

#define ADD_EVENT(evt) \
	if(this->m_ ## evt == nullptr) {this->m_ ## evt = new EventQueue<On ## evt ## _t>();} \
	this->m_ ## evt->Add(cb);
		

mimp::internal::event::EventPool::EventPool(): 
	m_ServerInit(nullptr),
	m_ServerExit(nullptr),
	m_PlayerConnect(nullptr), 
	m_PlayerDisconnect(nullptr),
	m_PlayerSpawn(nullptr)
{
}

void mimp::internal::event::EventPool::OnServerInit(OnServerInit_t cb) {
	ADD_EVENT(ServerInit)
}

void mimp::internal::event::EventPool::OnServerExit(OnServerExit_t cb) {
	ADD_EVENT(ServerExit)
}

void mimp::internal::event::EventPool::OnPlayerConnect(OnPlayerConnect_t cb) {
	ADD_EVENT(PlayerConnect)
}

void mimp::internal::event::EventPool::OnPlayerDisconnect(OnPlayerDisconnect_t cb) {
	ADD_EVENT(PlayerDisconnect)
}

void mimp::internal::event::EventPool::OnPlayerSpawn(OnPlayerSpawn_t cb) {
	ADD_EVENT(PlayerSpawn)
}

int mimp::internal::event::EventPool::Emit(uint16_t id, void* ctx) {
	switch (id) {
	case SERVER_EVENT_SERVERINIT: {
		CALL_EVENT(ServerInit)
	}
	case SERVER_EVENT_SERVEREXIT: {
		CALL_EVENT(ServerExit)
	}
	case SERVER_EVENT_PLAYERCONNECT: {
		OnPlayerConnect_params* p = static_cast<OnPlayerConnect_params*>(ctx);
		CALL_EVENT(PlayerConnect, p->player)
	}
	case SERVER_EVENT_PLAYERDISCONNECT: {
		OnPlayerDisconnect_params* p = static_cast<OnPlayerDisconnect_params*>(ctx);
		CALL_EVENT(PlayerDisconnect, p->player)
	}
	case SERVER_EVENT_PLAYERSPAWN: {
		OnPlayerSpawn_params* p = static_cast<OnPlayerSpawn_params*>(ctx);
		CALL_EVENT(PlayerSpawn, p->player)
	}
	default: {
		return -1;
	}
	}
}