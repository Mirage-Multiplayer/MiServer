#include "event/EventPool.hpp"

mimp::internal::event::EventPool::EventPool(): 
	m_ServerInit(nullptr),
	m_ServerExit(nullptr),
	m_PlayerConnect(nullptr), 
	m_PlayerDisconnect(nullptr),
	m_PlayerWeaponShoot(nullptr),
	m_PlayerSpawn(nullptr)
{
}

void mimp::internal::event::EventPool::OnServerInit(EventCallback_t cb) {
	if (this->m_ServerInit == nullptr) {
		this->m_ServerInit = new EventQueue();
	}

	this->m_ServerInit->Add(cb);
}

void mimp::internal::event::EventPool::OnServerExit(EventCallback_t cb) {
	if (this->m_ServerExit == nullptr) {
		this->m_ServerExit = new EventQueue();
	}

	this->m_ServerExit->Add(cb);
}

void mimp::internal::event::EventPool::OnPlayerConnect(EventCallback_t cb) {
	if (this->m_PlayerConnect == nullptr) {
		this->m_PlayerConnect = new EventQueue();
	}

	this->m_PlayerConnect->Add(cb);
}

void mimp::internal::event::EventPool::OnPlayerDisconnect(EventCallback_t cb) {
	if (this->m_PlayerDisconnect == nullptr) {
		this->m_PlayerDisconnect = new EventQueue();
	}

	this->m_PlayerDisconnect->Add(cb);
}

void mimp::internal::event::EventPool::OnPlayerSpawn(EventCallback_t cb) {
	if (this->m_PlayerSpawn == nullptr) {
		this->m_PlayerSpawn = new EventQueue();
	}
	this->m_PlayerSpawn->Add(cb);
}

void mimp::internal::event::EventPool::OnPlayerWeaponShot(EventCallback_t cb) {
	if (this->m_PlayerWeaponShoot == nullptr) {
		this->m_PlayerWeaponShoot = new EventQueue();
	}

	this->m_PlayerWeaponShoot->Add(cb);
}

int mimp::internal::event::EventPool::Emit(uint16_t id, void* ctx) {
	switch (id) {
	case SERVER_EVENT_SERVERINIT: {
		if (this->m_ServerInit == nullptr) {
			return 0;
		}
		this->m_ServerInit->Call(ctx);
		return 1;
	}
	case SERVER_EVENT_SERVEREXIT: {
		if (this->m_ServerExit == nullptr) {
			return 0;
		}
		this->m_ServerExit->Call(ctx);
		return 1;
	}
	case SERVER_EVENT_PLAYERCONNECT: {
		if (this->m_PlayerConnect == nullptr) {
			return 0;
		}

		this->m_PlayerConnect->Call(ctx);
		return 1;
	}
	case SERVER_EVENT_PLAYERDISCONNECT: {
		if (this->m_PlayerDisconnect == nullptr) {
			return 0;
		}

		this->m_PlayerDisconnect->Call(ctx);
		return 1;
	}
	case SERVER_EVENT_PLAYERSPAWN: {
		if (this->m_PlayerSpawn == nullptr) {
			return 0;
		}

		this->m_PlayerSpawn->Call(ctx);
		return 1;

	}
	case SERVER_EVENT_PLAYERWEAPONSHOT: {
		if (this->m_PlayerWeaponShoot == nullptr) {
			return 0;
		}

		this->m_PlayerWeaponShoot->Call(ctx);
		return 1;
	}
	default: {
		return -1;
	}
	}
}