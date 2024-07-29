#ifndef __MISERVER_EVENTQUEUE_HPP
#define __MISERVER_EVENTQUEUE_HPP
#include <vector>
#include <type_traits>
#include "EventTypes.hpp"

namespace mimp {
	namespace internal {
		namespace event {
			template<class T>
			class EventQueue {
			public:
				EventQueue() = default;

				template<typename... Args>
				int Call(Args&&... args) {
					if (this->m_queue.empty()) {
						return 0;
					}
					for (auto& func : this->m_queue)
					{
						int ret = std::forward<T>(func)(std::forward<Args>(args)...);
						if (ret == 0) {
							break;
						}
					}
						
					return 1;
				}

				void Add(T event) {
					m_queue.push_back(event);
				}
			private:
				std::vector<T> m_queue;
			};
		}
	}
}
#endif