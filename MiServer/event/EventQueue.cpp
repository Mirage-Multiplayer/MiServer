#include "event/EventQueue.hpp"

mimp::internal::event::EventQueue::EventQueue() {
}

int mimp::internal::event::EventQueue::Call(void* ctx) {
	if (this->m_queue.empty()) {
		return 0;
	}
	for (auto& func : this->m_queue)
	{
		int ret = func(ctx);
		if (ret == 0) {
			break;
		}
	}
	return 1;
}

void mimp::internal::event::EventQueue::Add(EventCallback_t event) {
	m_queue.push_back(event);
}