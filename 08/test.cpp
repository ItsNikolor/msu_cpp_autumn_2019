#include"ThreadPool.h"
using namespace std;




struct A {};

int foo(const A&) { cout << "Hello world   " << this_thread::get_id() << endl; return 5; }

void fun(const A&) {
	return;
}

auto func = bind(foo, A());

int main() {
	int i;
	for (i = 0; i < 50; i++) {
		{
			cout << "Main thread  " << this_thread::get_id() << endl;
			ThreadPool pool(800);

			auto task1 = pool.exec(foo, A());
			cout << task1.get() << endl;

			auto task2 = pool.exec([]() {cout << "Hell    " << this_thread::get_id() << endl; return 1; });
			cout << task2.get() << endl;
		}
		cout << "================================================\n\n\n";
		cout << i << endl;
	}
	cout << i << endl;

}