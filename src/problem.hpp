/*
#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <cstddef>

#include "statistics.hpp"
#include "random.hpp"
#include "sga.hpp"
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

class problem {
public:
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
	problem();

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

	void solve_flowshop(config& c);

};

void solve_flowshop(config& cfg);*/
