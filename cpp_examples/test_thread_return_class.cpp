// Test function for thread and future/promise

#include<iostream>
#include<future>
#include<thread>
//#include<mutex>

//#include "Stopwatch.hpp"

#define WAIT 0	// whether joining or detaching threads

class thread_class
{

public:

	thread_class() = default;

	void function_wait_for (int waittime, std::promise<int>&& flag)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(waittime));
		if (waittime < 1000)
			flag.set_value_at_thread_exit(1);
		else
			flag.set_value_at_thread_exit(2);
	}

	void loop_set(std::size_t iter, int waittime)
	{
		std::cout << "Loop_set iteration " << iter << "\n";

		constexpr int total_timebound = 900;

		int flag_checked;

		std::unique_lock<std::mutex> thread_lock(thread_mtx_,std::try_to_lock);

		if (thread_lock.owns_lock()) {

			std::promise<int> flag;
			std::future<int> flag_value = flag.get_future();
			
			std::thread worker(&thread_class::function_wait_for, this, waittime,
				std::move(flag));	// it works with a new thread
			/*
			worker(&thread_class::function_wait_for, this, waittime,
				std::move(flag));	// it doesn't work with a class-member thread
			*/
			if (WAIT)
				worker.join();
			else
				worker.detach();

			std::future_status status = flag_value.wait_for(std::chrono::milliseconds(total_timebound));

			if (status == std::future_status::ready)	{
				flag_checked = flag_value.get();
				std::cout << "Flag (future): " << flag_checked << "\n";
			} else {
				flag_checked = -1;
				std::cout << "Flag (backup): " << flag_checked << "\n";
			}
		}	else {
			flag_checked = -2;
			std::cout << "Flag (not joined): " << flag_checked << "\n";
		}

	}

private:
	std::mutex thread_mtx_;
	//std::thread worker;		// trying to use just one worker thread
};

int main()
{
	constexpr int num_times = 2;

	constexpr int waittime = 1200;

	thread_class test_class;

	for (std::size_t i=1; i<=num_times; ++i)
	{
		test_class.loop_set(i, waittime/i);
		//thread_class::loop_set(i, waittime/i);
	}
	

	return 0;
}