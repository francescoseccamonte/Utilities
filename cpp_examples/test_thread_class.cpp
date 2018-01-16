// test for threads in a class

#include <iostream>       		// std::cout
#include <thread>         		// std::thread, std::this_thread::sleep_for
#include <condition_variable>	// std::condition_variable
#include <chrono>         		// std::chrono::seconds

#include "Stopwatch.hpp"

#define TERMINATE 1				// define whether to terminate as soon as possible, or wait for all threads to terminate

int global_int;

class TestClass {

public :
    TestClass(int n):
    n_(n),
    has_modified_(false),
    print_has_completed_(false)
    {
    }

    ~TestClass()
    {
    }

	int long_square()
	{
		std::this_thread::sleep_for (std::chrono::seconds(3));
		modify();
		return n_*n_;
	}

	bool is_member_modified()
	{
		return has_modified_;
	}

	bool is_print_completed()
	{
		return print_has_completed_;
	}

	void modify()
	{
		has_modified_ = has_modified_ ? false : true;
		std::cout << "Thread ID (modify): " << std::this_thread::get_id() << "\n";
	}

	void print_has_modified()
	{
		print_has_completed_ = false;
		std::this_thread::sleep_for (std::chrono::seconds(3));
		std::cout << "Has modified: " << has_modified_ << "\n";
		std::cout << "Thread ID (print): " << std::this_thread::get_id() << "\n";
		global_int++;
		std::cout << "global_int (print) = " << global_int << "\n";
		print_has_completed_ = true;
		std::cout << "print_has_completed_ (print) = " << print_has_completed_ << "\n";
	}

	void print_watch()	// checks whether print_has_completed_ changes during time_threshold seconds
	{
		const double time_threshold = 2;
		auto start = std::chrono::high_resolution_clock::now();
		while (!print_has_completed_ && 
			std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < time_threshold)
		{
			std::this_thread::sleep_for (std::chrono::milliseconds(500));
			std::cout << "Waiting for print to complete\n";
		}

		std::cout<< "Elapsed time: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << "\n";
	}


	void run_threads()
	{
		std::cout << "Thread ID (run_threads): " << std::this_thread::get_id() << "\n"; // expecting same value as main thread

		std::thread t1(&TestClass::print_has_modified, this);
		std::cout << "Thread ID explicit (print): " << t1.get_id() << "\n";
		//t1.join();		// if here, run_threads waits at this point until the process in t1 is complete

		std::thread t2(&TestClass::print_watch, this);
		std::thread t3(&TestClass::modify, this);

		if (TERMINATE)
			t1.detach();	// race conditions!
		else
			t1.join();

		t2.join();
		t3.join();

		t1.~thread();	// if thread did not terminate, core dumped -> but with detach it seems ok

	}

	private :
	int n_;
	bool has_modified_;
	bool print_has_completed_;
};



int main()
{
	int n = 2;
	TestClass test(n);
	auto start = std::chrono::high_resolution_clock::now();

	global_int = 0;

	std::cout << "Thread ID (main): " << std::this_thread::get_id() << "\n";

	for (std::size_t idx = 0; idx < 2; ++idx)
	{
		test.run_threads();
		std::cout << "print_has_completed_ (main) n " << idx << " = " << test.is_print_completed() << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(3000/(idx+1)));
	} // this loop shows that a detached thread simply keeps running, it is not killed.

	//std::cout << "x^2 = " << test.long_square() << "\n";
	std::cout << "Has modified main: " << test.is_member_modified() << "\n";

	std::cout << "global_int (main)= " << global_int << "\n";

	std::cout << "Elapsed (wall) clock time: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-start).count() << "\n";

	//double time_converted = static_cast<double>std::chrono::high_resolution_clock::now();

	//std::cout << "Time converted = " << time_converted << "\n";

	nutils::Stopwatch stopwatch;

	std::cout << "Test Stopwatch: " << stopwatch.toc() <<" \n";
	std::this_thread::sleep_for (std::chrono::milliseconds(500));
	std::cout << "Test Stopwatch: " << stopwatch.toc() <<" \n";

	return 0;
}