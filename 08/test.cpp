#include"ThreadPool.h"
#include<cassert>
using namespace std;




struct A {};

int foo(const A&) {
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	cout << "1 func. Thread =  " << this_thread::get_id() << endl;
	return 1;
}

int main() {
	int N = 1;
		for (int i=0;i<N;i++)
		{
			cout << "Main thread  " << this_thread::get_id() << endl;
			ThreadPool pool(8);

			auto task1 = pool.exec(foo, A());
			assert(task1.get() == 1);

			auto task2 = pool.exec([]() {cout << "2 func. Thread =  " << this_thread::get_id() << endl; return 1; });
			assert(task2.get() == 1);

			auto task3 = pool.exec([]() {cout << "3 func. Thread =  " << this_thread::get_id() << endl; return true; });
			assert(task3.get() == true);

			auto task4 = pool.exec([]() {cout << "4 func. Thread =  " << this_thread::get_id() << endl; return "cool"; });
			assert(task4.get() == "cool");

			auto task5 = pool.exec([]() {cout << "5 func. Thread =  " << this_thread::get_id() << endl; return 4.2; });
			assert(task5.get() == 4.2);

			auto task6 = pool.exec([]() {cout << "6 func. Thread =  " << this_thread::get_id() << endl; return 6; });
			assert(task6.get() == 6);

			auto task7 = pool.exec([]() {cout << "7 func. Thread =  " << this_thread::get_id() << endl; return 7; });
			assert(task7.get() == 7);

			auto task8 = pool.exec([]() {cout << "8 func. Thread =  " << this_thread::get_id() << endl; return 8; });
			assert(task8.get() == 8);

			auto task9 = pool.exec([]() {cout << "9 func. Thread =  " << this_thread::get_id() << endl; return 9; });
			assert(task9.get() == 9);

			auto task10 = pool.exec([]() {cout << "10 func. Thread =  " << this_thread::get_id() << endl; return 10; });
			assert(task10.get() == 10);
			
		}
		cout << "================================================\n\n\n";

		for (int i = 0; i < N; i++)
		{
			cout << "Main thread  " << this_thread::get_id() << endl;
			ThreadPool pool(8);

			auto task1 = pool.exec(foo, A());
			

			auto task2 = pool.exec([]() {cout << "2 func. Thread =  " << this_thread::get_id() << endl; return 1; });
			

			auto task3 = pool.exec([]() {cout << "3 func. Thread =  " << this_thread::get_id() << endl; return true; });
			

			auto task4 = pool.exec([]() {cout << "4 func. Thread =  " << this_thread::get_id() << endl; return "cool"; });
			

			auto task5 = pool.exec([]() {cout << "5 func. Thread =  " << this_thread::get_id() << endl; return 4.2; });
			

			auto task6 = pool.exec([]() {cout << "6 func. Thread =  " << this_thread::get_id() << endl; return 6; });
			

			auto task7 = pool.exec([]() {cout << "7 func. Thread =  " << this_thread::get_id() << endl; return 7; });
			
			auto task8 = pool.exec([]() {cout << "8 func. Thread =  " << this_thread::get_id() << endl; return 8; });

			auto task9 = pool.exec([]() {cout << "9 func. Thread =  " << this_thread::get_id() << endl; return 9; });

			auto task10 = pool.exec([]() {cout << "10 func. Thread =  " << this_thread::get_id() << endl; return 10; });

			assert(task10.get() == 10);
			assert(task1.get() == 1);
			assert(task9.get() == 9);
			assert(task8.get() == 8);
			assert(task7.get() == 7);
			assert(task6.get() == 6);
			assert(task5.get() == 4.2);
			assert(task2.get() == 1);
			assert(task4.get() == "cool");
			assert(task3.get() == true);

		}
		cout << "================================================\n\n\n";
		for (int i = 0; i < N; i++)
		{
			cout << "Main thread  " << this_thread::get_id() << endl;
			ThreadPool pool(8);

			pool.exec(foo, A());


			pool.exec([]() {cout << "2 func. Thread =  " << this_thread::get_id() << endl; return 1; });


			pool.exec([]() {cout << "3 func. Thread =  " << this_thread::get_id() << endl; return true; });


			pool.exec([]() {cout << "4 func. Thread =  " << this_thread::get_id() << endl; return "cool"; });


			pool.exec([]() {cout << "5 func. Thread =  " << this_thread::get_id() << endl; return 4.2; });


			pool.exec([]() {cout << "6 func. Thread =  " << this_thread::get_id() << endl; return 6; });


			pool.exec([]() {cout << "7 func. Thread =  " << this_thread::get_id() << endl; return 7; });

			pool.exec([]() {cout << "8 func. Thread =  " << this_thread::get_id() << endl; return 8; });

			pool.exec([]() {cout << "9 func. Thread =  " << this_thread::get_id() << endl; return 9; });

			pool.exec([]() {cout << "10 func. Thread =  " << this_thread::get_id() << endl; return 10; });
		}
		cout << "================================================\n\n\n";
	return 0;
}