#include <iostream>       // std::cout
#include <vector>         // std::vector
#include <chrono>		  	  // std::chrono
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock, 

#define N 1000

//std::mutex mtx;           // mutex for critical section
std::timed_mutex mtx;

void print_char(char to_print)
{
	for (int idx=0; idx<N; ++idx)
		std::cout << to_print;
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void print_char_unique (char to_print)
{
  //std::unique_lock<std::mutex> lck(mtx,std::try_to_lock);
  std::unique_lock<std::timed_mutex> lck(mtx,std::defer_lock);

  /*if (lck.owns_lock())
    print_char(to_print);*/

  while(!lck.try_lock_for(std::chrono::milliseconds(10000)))
  {
  	std::cout << "Acquiring lock\n";
  }
  print_char(to_print);
}

int main()
{
	std::cout << "Without mutex\n";

	std::thread thread1(print_char, '-');
	std::thread thread2(print_char, '|');

	thread1.join();
	thread2.join();

	std::cout << "\nUsing mutex\n";

	std::thread thread3(print_char_unique, '-');
	std::thread thread4(print_char_unique, '|');

	thread3.join();
	thread4.join();

	std::cout << "\n";

	return 0;
}
