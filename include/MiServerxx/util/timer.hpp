#pragma once
#include <chrono>

namespace mimp {
	namespace util {
		struct CSimpleTimer {
			std::chrono::time_point<std::chrono::steady_clock> start, end;
			std::chrono::duration<float> duration;

			CSimpleTimer() {
				start = std::chrono::high_resolution_clock::now();
			}

			~CSimpleTimer() {
				end = std::chrono::high_resolution_clock::now();
				duration = end - start;
				float ms = duration.count() * 1000.0f;
				printf("Timer took %fms\n", ms);
			}
		};
	}
}
