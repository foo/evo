#include <thread>
#include <system_error>
#include <iostream>
#include "multisga.hpp"

void multisga::run_thread(population &p) {

	evaluate(p);
	while (!termination(p)) {
		adaptation(p);
		crossover(p);
		adaptation(p);
		mutation(p);
		adaptation(p);
		replacement(p);
		evaluate(p);
		report(p);
	}
	report_end(p);
	std::cout << "Koniec watku" << std::endl;
}

void multisga::run() {
	int threads_count = 4;
	std::vector < std::thread > threads;
	std::vector < population > populations;
	population p;

	for (int i = 0; i < threads_count; i++) {
		p = initial_population();
		populations.push_back(p);
		threads.push_back(std::thread([this](population p){this->run_thread(p); }, p ));
	}
	try {
		for (std::thread& t : threads) {
			t.join();
		}
	} catch (std::system_error & e) {
		std::cout << "Error: thread joining" << std::endl;
	}
}


