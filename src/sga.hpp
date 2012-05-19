#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <cstddef>

#include "permutation.hpp"

#include "statistics.hpp"
#include "random.hpp"
#include "population.hpp"
#include "mutation.hpp"
#include "crossover.hpp"
#include "weighted_tardiness.hpp"

struct config {
	enum report {
		none, best, avg
	};
	crossover::type crossover_type;
	bool debug;
	bool report_population;
	bool report_best;
	bool smart_termination;
	int max_iter;
	int optimum;
	bool report_var;
	bool compare_operators;
	report report_every;
	int seed;
	int population_size;
	int ping_frequency;
};

class sga {
public:

	/*// create initial population
	 population (*initial_population)();

	 // compute adaptation function for every specimen in population
	 void (*adaptation)(population& p);

	 // compute elavuation function for every specimen in population
	 void (*evaluate)(population& p);

	 bool (*termination)(const population& p);
	 void (*mutation)(population& p);
	 void (*crossover)(population& p);
	 void (*replacement)(population& p);
	 void (*report)(population& p);
	 void (*report_end)(population& p);*/
	config cfg;

	int iter;
	population prev_population;

	int population_size;
	int parents;

	float mutation_prob; // probability of mutation

	int eval_count;
	int xop_count;
	int ox_count;
	int cx_count;
	int pmx_count;
	long long x_count;

	specimen best_specimen;
	int deviate_count;

	weighted_tardiness wt_problem;
	sga(config c, weighted_tardiness wt);

	void init_prev_population();
	float evaluation(const permutation& p);

	void evaluate_population(population& p);

	population initial_population();

	//bool eval_comp(specimen a, specimen b);

	void adapt_population(population& p);

	bool optimum_termination(const population& p);

	bool termination(const population& p);

	bool smart_termination(const population& p);

	void mutation_function(population& p);

	// used by random_shuffle
	ptrdiff_t randgenid(ptrdiff_t i);
	//ptrdiff_t (*p_randgenid)(ptrdiff_t);

	void crossover_function(population& p);

	struct eval_cmp {
		bool operator()(const specimen& s1, const specimen& s2) const {
			return std::less<float>()(s1.adapt, s2.adapt);
		}
	};

	void replacement(population& p);

	void report(population& p);

	void report_end(population& p);

	void read_input();

	population solve_flowshop();

	population solve_flowshop(population pop);

	population run(population p);
};
