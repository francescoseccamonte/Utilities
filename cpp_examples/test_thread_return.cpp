// Test function for thread and future/promise

#include<iostream>
#include<future>
#include<thread>
//#include<mutex>

#define WAIT 0	// whether joining or detaching threads


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

	std::promise<int> flag;
    std::future<int> flag_value = flag.get_future();

    std::thread thread_wait(&function_wait_for, waittime,
                            std::move(flag));

    if (WAIT)
    	thread_wait.join();
    else
    	thread_wait.detach();
	
	// to wait approx. total_timebound
	std::this_thread::sleep_for(std::chrono::milliseconds(total_timebound-1));
	std::future_status status = flag_value.wait_for(std::chrono::milliseconds(1));

    if (status == std::future_status::ready)	{
    	flag_checked = flag_value.get();
		std::cout << "Flag (future): " << flag_checked << "\n";
    } else {
    	flag_checked = -1;
    	std::cout << "Flag (backup): " << flag_checked << "\n";
    }

}

int main()
{
	constexpr int num_times = 2;

	constexpr int waittime = 1200;

	for (std::size_t i=1; i<=num_times; ++i)
	{
		loop_set(i, waittime/i);
	}
	

	return 0;
}
