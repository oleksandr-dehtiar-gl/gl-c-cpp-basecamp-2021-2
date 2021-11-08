#ifndef APPEXECUTIONTIMER_HPP
#define APPEXECUTIONTIMER_HPP

#include <iostream>
#include <chrono> 

namespace transfer {
	
	class AppExecutionTimer {
	private:
		std::chrono::high_resolution_clock::time_point start;
	public:
		AppExecutionTimer() : start(std::chrono::high_resolution_clock::now()) { }
		~AppExecutionTimer() {
			auto sec = std::chrono::high_resolution_clock::now()-start;
			std::cout << "Working Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(sec).count() << " ms\n";
			std::cout << "Press enter to continue...";
			std::cin.get();
		}
	};

}

#endif // APPEXECUTIONTIMER_HPP
