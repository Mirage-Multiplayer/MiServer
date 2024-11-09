#pragma once

#include <queue>
#include <vector>
#include <map>
#include <MiServerxx/event/EventTypes.hpp>

#define MIMP_GET_EVENT(name,eventpool) \
    mimp::internal::event::SERVER_EVENT_##name##_T* name = eventpool->GetEvent<mimp::internal::event::SERVER_EVENT_##name##_T>(mimp::internal::event::SERVER_EVENT_##name);

/* Event Pool
	Class who handle Event Queues and emit'em
*/
namespace mimp
{
	namespace internal
	{
		namespace event
		{
            class CEventPool {
            public:
                template<typename... Args>
                void RegisterEvent(uint16_t key, std::unique_ptr<CEvent<Args...>> event) {
                    m_eventMap[key] = std::move(event);
                }

                template<typename EventType>
                EventType* GetEvent(uint16_t key) {
                    auto it = m_eventMap.find(key);
                    if (it != m_eventMap.end()) {
                        return dynamic_cast<EventType*>(it->second.get());
                    }
                    return nullptr;
                }

            private:
                std::map<uint16_t, std::unique_ptr<IEventBase>> m_eventMap;
            };
		}

	}
}