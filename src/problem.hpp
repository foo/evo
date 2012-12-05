#include <iostream>
#include <vector>
#include <functional>
#include <cassert>

#include "statistics.hpp"
#include "random.hpp"
#include "sga.hpp"
#include "mutation.hpp"
#include "crossover.hpp"
#include "sdvrp.hpp"

struct config
{
  enum report
    {
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

void solve_sdvrp(config& cfg);
