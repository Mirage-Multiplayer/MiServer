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
					if (this->m_queue.empty()) {
						return 0;
					}

					auto aux = this->m_queue;
					while (!aux.empty()) {
						std::function<int(Args...)> func = aux.front();
						aux.pop();
						int ret = func(args...);
						if (ret == 0)
							break;
					}
					return 0;
				}

				int CallVoid() {
					if (this->m_queue.empty()) {
						return 0;
					}
					auto aux = this->m_queue;
					while (!aux.empty()) {
						std::function<int(void)> func = aux.front();
						aux.pop();
						int ret = func();
						if (ret == 0)
							break;
					}
					return 0;
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