// mutex::lock/unlock
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex

std::mutex mtx;           // mutex for critical section

/*
void print_thread_id (int id) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
  std::cout << "thread #" << id << '\n';
  mtx.unlock();
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_thread_id,i+1);

  for (auto& th : threads) th.join();

  return 0;
}
*/

class TestMutex
{
public:
	TestMutex()
	{
		mtx.lock();
		std::cout << "Mutex locked in constructor.\n"; 
	}

	~TestMutex()
	{
		mtx.unlock();
		std::cout << "Mutex unlocked in destructor.\n"; 
	}

};


int main()
{
	TestMutex test;

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	if (mtx.try_lock())
		std::cout << "Mutex locked in main.\n";
	else
		std::cout << "Could not lock mutex in main.\n";

	return 0;
}
