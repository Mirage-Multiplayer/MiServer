#include "event/EventPool.hpp"

mimp::internal::event::EventPool::EventPool(): 
	m_ServerInit(nullptr),
	m_ServerExit(nullptr),
	m_PlayerConnect(nullptr), 
	m_PlayerDisconnect(nullptr),
	m_PlayerSpawn(nullptr)
{
}

void mimp::internal::event::EventPool::OnServerInit(OnServerInit_t cb) {
	if (this->m_ServerInit == nullptr) {
		this->m_ServerInit = new EventQueue<OnServerInit_t>();
	}

	this->m_ServerInit->Add(cb);
}

void mimp::internal::event::EventPool::OnServerExit(OnServerExit_t cb) {
	if (this->m_ServerExit == nullptr) {
		this->m_ServerExit = new EventQueue<OnServerExit_t>();
	}

	this->m_ServerExit->Add(cb);
}

void mimp::internal::event::EventPool::OnPlayerConnect(OnPlayerConnect_t cb) {
	if (this->m_PlayerConnect == nullptr) {
		this->m_PlayerConnect = new EventQueue<OnPlayerConnect_t>();
	}

	this->m_PlayerConnect->Add(cb);
}

void mimp::internal::event::EventPool::OnPlayerDisconnect(OnPlayerDisconnect_t cb) {
	if (this->m_PlayerDisconnect == nullptr) {
		this->m_PlayerDisconnect = new EventQueue<OnPlayerDisconnect_t>();
	}

	this->m_PlayerDisconnect->Add(cb);
}

void mimp::internal::event::EventPool::OnPlayerSpawn(OnPlayerSpawn_t cb) {
	if (this->m_PlayerSpawn == nullptr) {
		this->m_PlayerSpawn = new EventQueue<OnPlayerSpawn_t>();
	}
	this->m_PlayerSpawn->Add(cb);
}

int mimp::internal::event::EventPool::Emit(uint16_t id, void* ctx) {
	switch (id) {
	case SERVER_EVENT_SERVERINIT: {
		if (this->m_ServerInit == nullptr) {
			return 0;
		}
		this->m_ServerInit->Call();
		return 1;
	}
	case SERVER_EVENT_SERVEREXIT: {
		if (this->m_ServerExit == nullptr) {
			return 0;
		}
		this->m_ServerExit->Call();
		return 1;
	}
	case SERVER_EVENT_PLAYERCONNECT: {
		if (this->m_PlayerConnect == nullptr) {
			return 0;
		};

		OnPlayerConnect_params* p = static_cast<OnPlayerConnect_params*>(ctx);
		this->m_PlayerConnect->Call(p->player);
		return 1;
	}
	case SERVER_EVENT_PLAYERDISCONNECT: {
		if (this->m_PlayerDisconnect == nullptr) {
			return 0;
		}

		OnPlayerDisconnect_params* p = static_cast<OnPlayerDisconnect_params*>(ctx);
		this->m_PlayerDisconnect->Call(p->player);
		return 1;
	}
	case SERVER_EVENT_PLAYERSPAWN: {
		if (this->m_PlayerSpawn == nullptr) {
			return 0;
		}

		OnPlayerSpawn_params* p = static_cast<OnPlayerSpawn_params*>(ctx);
		this->m_PlayerSpawn->Call(p->player);
		return 1;
	}
	default: {
		return -1;
	}
	}
}