#include <tbb/tbb.h>
#include <vector>
#include <chrono>
#include <iostream>

long long fibonacci(int n) {
	if (n <= 1) return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

constexpr int X = 43;

int main() {
	std::vector<long long> v1, v2;
	tbb::task_group group1;

	auto start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		group1.run([i, &v1] {
			v1.push_back(fibonacci(X));
		});
	}
	group1.wait();

	auto end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_time = end_time - start_time;
	std::cout << "Time taken in multithreaded system to calculate fib(" << X << "): " << elapsed_time << std::endl << "concurrent vector (first 3):" << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << v1.at(i) << " | ";
	}


	auto start_time2 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		v2.push_back(fibonacci(X));
	}

	auto end_time2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_time2 = end_time2 - start_time2;
	std::cout << "\n\n" << "Time taken in single threaded system to calculate fib(" << X << "): " << elapsed_time2 << std::endl << "single threaded vector (first 3):" << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << v2.at(i) << " | ";
	}

	return EXIT_SUCCESS;
}