#pragma once

#include <mutex>
#include <condition_variable>
#include <iostream>

using std::cout;
using std::endl;

class Semaphore {
public:
	Semaphore(int count_ = 0, int max_count = 5)
		: count(count_), max_count(max_count)
	{
	}

	inline void notify(int tid) {
		std::unique_lock<std::mutex> lock(mtx);
		if (count < max_count) {
			count++;
			//notify the waiting thread
			cv.notify_one();
		}
	}
	inline void wait(int tid) {
		std::unique_lock<std::mutex> lock(mtx);
		while (count == 0) {
			//wait on the mutex until notify is called
			cv.wait(lock);
		}
		count--;
	}

	inline void cleanup() {
		std::unique_lock<std::mutex> lock(mtx);
		count = 0;
	}
private:
	std::mutex mtx;
	std::condition_variable cv;
	int count;
	const int max_count;
};
