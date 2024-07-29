#ifndef __MISERVER_EVENTQUEUE_HPP
#define __MISERVER_EVENTQUEUE_HPP
#include <vector>
#include "EventTypes.hpp"
namespace mimp {
	namespace internal {
		namespace event {
			class EventQueue {
			public:
				EventQueue();
				int Call(void* ctx);

				void Add(EventCallback_t event);
			private:
				std::vector<EventCallback_t> m_queue;
			};
		}
	}
}
#endif