#ifndef THREADSAFEQUEUE_HPP
#define THREADSAFEQUEUE_HPP

#include <queue>
#include <utility>

#include <thread>
#include <mutex>
#include <condition_variable>

namespace transfer {
	
	template<typename T>
	class ThreadSafeQueue {
	private:
		mutable std::mutex mut;
		std::queue<std::shared_ptr<T> > data_queue;
		std::condition_variable data_cond;
		const unsigned int MAX_ELEMENT;
		public:
			ThreadSafeQueue(unsigned int maxelement) : MAX_ELEMENT(maxelement)
			{}
			
			void wait_and_pop(T &value) {
				std::unique_lock<std::mutex> lk(mut);
				data_cond.wait(lk, [this]{return !data_queue.empty();});
				value = std::move(*data_queue.front());
				data_queue.pop();
			}
			
			bool try_pop(T &value) {
				std::lock_guard<std::mutex> lk(mut);
				if (data_queue.empty()) {
					return false;
				}
				value = std::move(*data_queue.front());
				data_queue.pop();
				return true;
			}
			
			std::shared_ptr<T> wait_and_pop() {
				std::unique_lock<std::mutex> lk(mut);
				data_cond.wait(lk, [this]{return !data_queue.empty();});
				std::shared_ptr<T> res = data_queue.front();
				data_queue.pop();
				return res;
			}
			
			std::shared_ptr<T> try_pop() {
				std::lock_guard<std::mutex> lk(mut);
				if (data_queue.empty())
					return std::shared_ptr<T>();
				std::shared_ptr<T> res = data_queue.front();
				data_queue.pop();
				return res;
			}
			
			bool try_push(T new_val) {
				std::shared_ptr<T> data(std::make_shared<T>(std::move(new_val)));
				std::lock_guard<std::mutex> lk(mut);
				if (data_queue.size() >= MAX_ELEMENT)
					return false;
				data_queue.push(std::move(data));
				data_cond.notify_one();
				return true;
			}
			
			bool try_push(std::shared_ptr<T> new_val) {
				std::lock_guard<std::mutex> lk(mut);
				if (data_queue.size() >= MAX_ELEMENT)
					return false;
				data_queue.push(std::move(new_val));
				data_cond.notify_one();
				return true;
			}
			
			void wait_and_push(std::shared_ptr<T> new_val) {
				std::unique_lock<std::mutex> lk(mut);
				data_cond.wait(lk, [this]{return data_queue.size() >= MAX_ELEMENT;});
				data_queue.push(std::move(new_val));
				data_cond.notify_one();
			}
			
			
			bool empty() const {
				std::lock_guard<std::mutex> lk(mut);
				return data_queue.empty();
			}
	};	
	
}

#endif //THREADSAFEQUEUE_HPP
