#ifndef THREADGUARD_HPP
#define THREADGUARD_HPP

#include <thread>
#include <exception>

namespace transfer {
	
	class Threadguard {
	private:
		std::thread mThr;
	public:
		Threadguard(const Threadguard&) = delete;
		Threadguard& operator=(const Threadguard&) = delete;
	public:
		explicit Threadguard(std::thread &&thr)
		:	mThr(std::move(thr)) 
		{
			if (!mThr.joinable()) {
				throw std::logic_error("No thread");
			}
		}
		
		explicit Threadguard(Threadguard &&movethr) 
		: mThr(std::move(movethr.mThr))
		{
			if (!mThr.joinable()) {
				throw std::logic_error("No thread");
			}
		}
		
		~Threadguard() {
			mThr.join();
		}
	};
	
}

#endif // THREADGUARD_HPP
