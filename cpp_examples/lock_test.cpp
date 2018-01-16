// unique_lock example revisited
#include <iostream>       // std::cout
#include <chrono>
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock

std::mutex mtx;           // mutex for critical section

void lock_test (int sleeptime)
{
	std::unique_lock<std::mutex> lck (mtx,std::try_to_lock);

	if (lck.owns_lock()) {
		std::cout << "Lock acquired\n";
	} else {
		std::cout << "Lock not owned\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));

}


int main ()
{
	constexpr int sleeptime = 100;
	std::thread th1 (lock_test,sleeptime*2);
	std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
	
	std::thread th2 (lock_test,sleeptime);

	th1.detach();
	th2.detach();


	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return 0;
}
