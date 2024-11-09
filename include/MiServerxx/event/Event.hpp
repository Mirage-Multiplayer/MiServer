#pragma once
#include <vector>
#include <functional>

namespace mimp {

	class IEventBase {
	public:
		virtual ~IEventBase() = default;
	};

	template<typename... Args>
	class CEvent : public IEventBase {
	public:
		void OnCall(const std::function<int(Args...)>& handler) {
			this->m_eventVector.push_back(handler);
		}
		int Emit(Args... args) {
			for (auto& callback : this->m_eventVector) {
				int ret = callback(std::forward<Args>(args)...);
				if (ret == 0) {
					return 0;
				}
			}
			return 1;
		}
	private:
		std::vector<std::function<int(Args...)>> m_eventVector;
	};

	template<>
	class CEvent<> : public IEventBase {
	public:
		
		void OnCall(const std::function<int()>& handler) {
			m_eventVector.push_back(handler);
		}

		
		int Emit() {
			for (auto& callback : m_eventVector) {
				int ret = callback();
				if (ret == 0) {
					return 0;
				}
			}
			return 1;
		}

	private:
		std::vector<std::function<int()>> m_eventVector;
	};
}
