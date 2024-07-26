#ifndef __MISERVER_EVENTQUEUE_HPP
#define __MISERVER_EVENTQUEUE_HPP
#include <queue>
namespace mimp {
	namespace internal {
		namespace event {

			template<typename T>
			class EventQueue {
			public:
				EventQueue() = default;

				template<typename... Args>
				int Call(Args... args) {
					auto aux = this->m_queue;
					while (!aux.empty()) {
						auto func = this->m_queue.front();
						func(args...);
					}
				}

				inline int Add(T event) {
					m_queue.push(event);
				}
			private:
				std::queue<T> m_queue;
			};
		}
	}
}
#endif