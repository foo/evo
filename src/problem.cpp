#include "problem.hpp"

config cfg;

int iter = 0;
population prev_population;

int population_size;
int parents;

float mutation_prob = 0.30f; // probability of mutation

int N;  // number of graph vertices
int eval_count = 0;
int xop_count = 3;
int ox_count = 0;
int cx_count = 0;
int pmx_count = 0;
long long x_count = 0;

specimen best_specimen;
int deviate_count = 0;

sdvrp f;

void init_prev_population()
{
  for(int i = 0; i < population_size; ++i)
  {
    specimen s;
    s.perm = permutation(N - 1);
    s.eval = s.adapt = 0.0;
    prev_population.push_back(s);
  }
}

float evaluation(const permutation& p)
{
  eval_count++;
  return f.route_cost(p.P());
}

void evaluate_population(population& p)
{
  for(unsigned int i=0; i<p.size(); i++)
    p[i].eval = evaluation(p[i].perm);
}

population initial_population()
{
  population pop;
  for(int i = 0; i < population_size; ++i)
  {
    specimen s;
    s.perm = permutation(N, permutation::type::random);
    s.eval = s.adapt = 0.0;
    pop.push_back(s);
  }

  best_specimen = pop[0];
  best_specimen.eval = evaluation(pop[0].perm);
  
  return pop;
}

bool eval_comp(specimen a, specimen b) { return a.eval<b.eval; }

void adapt_population(population& p)
{
  float F_min = min_element(p.begin(),p.end(),eval_comp)->eval;
  for(unsigned int i=0; i<p.size(); i++)
  {
    float sum = 0.0;
    for(unsigned int j=0; j<p.size(); j++)
      sum += p[j].eval - F_min;
    p[i].adapt = (p[i].eval - F_min)/sum;
  }
}

bool optimum_termination(const population& p)
{
    return p[0].eval <= cfg.optimum;
}

bool termination(const population& p)
{
  return optimum_termination(p) || (++iter > cfg.max_iter);
}

bool smart_termination(const population& p)
{
  return optimum_termination(p) || (deviate_count > population_size);
}

void mutation_function(population& p)
{
  for(auto i = p.begin(); i != p.end(); ++i)
  {
    float r = uniform_random(); // random float between <0,1)

    if(r < mutation_prob)
    {
      mutation::random_transposition(i->perm);
      i->eval = evaluation(i->perm); // after mutation is done we have to evaluate this specimen again
    }
  }
}

// used by random_shuffle
ptrdiff_t randgenid (ptrdiff_t i) { return randid()%i;}
ptrdiff_t (*p_randgenid)(ptrdiff_t) = randgenid;

void crossover_function(population& p)
{
  population new_population;
  std::vector<int> cross_set;
  std::vector<int>::iterator it;
  float rd;
  
  // choose which specimen will crossover
  for(int i=0; i<population_size; i++)
  {
    rd = (randid()*1.0f) / (RAND_MAX*1.0f*population_size);
    if(rd > p[i].adapt)
      cross_set.push_back(i);
  }
  
  // we want even number of parents
  if(cross_set.size() & 1)
    cross_set.pop_back();

  // more randomness
  random_shuffle ( cross_set.begin(), cross_set.end(), p_randgenid );

  it = cross_set.begin();
  // crossover each pair from left to right
  while( it != cross_set.end())
  {
    std::pair<permutation,permutation> desc;
    crossover::type ctype;

    if(cfg.compare_operators)
    {
      switch(randid() % xop_count)
      {
        case 0: ctype = crossover::type::OX; break;
        case 1: ctype = crossover::type::CX; break;
        case 2:
        default: ctype = crossover::type::PMX; break;
      }
      desc = crossover::random_crossover(ctype, p[*it].perm, p[*(it+1)].perm);
    }
    else
    {
      desc = crossover::random_crossover(cfg.crossover_type, p[*it].perm, p[*(it+1)].perm);
    }
        
    specimen ch1, ch2;
    ch1.perm = desc.first;
    ch1.eval = evaluation(ch1.perm);
    ch1.adapt = 0.0;
    ch2.perm = desc.second;
    ch2.eval = evaluation(ch2.perm);
    ch2.adapt = 0.0;
    
    if(cfg.compare_operators && ( ((p[*it].eval + p[*(it+1)].eval) / (ch1.eval + ch2.eval)) >= 1 ) )
    {
      switch(ctype)
      {
        case crossover::type::OX: ox_count++; break;
        case crossover::type::CX: cx_count++; break;
        case crossover::type::PMX:
        default: pmx_count++; break;
      }
    }
    
    it++; it++;
    x_count++;

    new_population.push_back(ch1);
    new_population.push_back(ch2);
  }

  p.insert(p.end(), new_population.begin(), new_population.end());
}

struct eval_cmp
{
  bool operator()(const specimen& s1, const specimen& s2) const
  {
    return std::less<float>()(s1.adapt, s2.adapt);
  }
};

void replacement(population& p)
{
  std::sort(p.begin(), p.end(), eval_cmp());
  p.resize(population_size);
  
  if( p[0].eval < best_specimen.eval )
  {
    best_specimen = p[0];
    deviate_count = 0;
  }
  else
  {
    deviate_count++;
  }
}

void report(population& p)
{
  switch(cfg.report_every)
  {
    case config::report::none:
      break;
    case config::report::avg:
      {
        float avg = 0.0;
        for(auto i = p.begin(); i != p.end(); ++i)
          avg += i->eval;
        avg /= static_cast<float>(p.size());
        std::cout << iter << ' ' << avg << '\n';
      }
      break;
    case config::report::best:
      std::cout << iter << ' ' << p[0].eval << '\n';
      break;
  }
  
  if(cfg.report_var)
  {
    std::cout << iter << ' ' << statistics::variance(p) << '\n';
  }

  if(cfg.ping_frequency > 0)
  {
    if(iter % cfg.ping_frequency == 0)
    {
      std::cout << iter << ", best: " << best_specimen.eval << '\n';
    }
  }
}

void report_end(population& p)
{
  if(cfg.report_every == config::report::none)
  {
    if(cfg.report_population)
    {
      if(cfg.debug)
      {
        std::cout << "Reporting population\n";
        std::cout << "Evaluation = [ permutation ]\n";
      }
      std::sort(p.begin(), p.end(), eval_cmp());
      for(auto i = p.begin(); i != p.end(); ++i)
        std::cout << i->eval << " = " << i->perm << std::endl;
    }

    if(cfg.report_best)
    {
      if(cfg.debug)
      {
        std::cout << "Reporting best speciman\n";
        std::cout << "Evaluation = [ permutation ]\n";
      }
      std::cout << best_specimen.eval << " = " << best_specimen.perm << std::endl;
    }

    if(cfg.optimum > -1)
    {
      if(cfg.debug)
      {
        std::cout << "Reporting number of evaluations needed to compute best specimen with given optimum value or --max-iter if optimum is not reached\n";
      }
      std::cout << population_size << ' ' << eval_count << "\n";
    }

    if(cfg.compare_operators)
    {
      std::cout << x_count << ' ' << ox_count << ' ' << cx_count << ' ' << pmx_count << "\n";
    }
  }
}

void read_input()
{
  std::cin >> N;

  f.initialize(N);

  for(int row = 0; row < N; ++row)
    for(int col = 0; col < N; ++col)
      std::cin >> f[row][col];
}

void solve_sdvrp(config& c)
{
  cfg = c;
  
  population_size = cfg.population_size;
  parents = population_size / 2;

  if(cfg.seed == 0)
    init_random_based_on_time();
  else
    init_random(cfg.seed);

  if(cfg.debug)
  {
    std::cout << "Crossover operator: ";
    switch(cfg.crossover_type)
    {
      case crossover::type::PMX:
        std::cout << "PMX";
        break;
      case crossover::type::CX:
        std::cout << "CX";
        break;
      case crossover::type::OX:
        std::cout << "OX";
        break;
    }
    std::cout << std::endl;
  }

  if(cfg.crossover_type == crossover::type::OX)
    mutation_prob = 0.15f;

  read_input();
  
  init_prev_population();

  sga algorithm;
  algorithm.initial_population = initial_population;
  algorithm.evaluate = evaluate_population;
  algorithm.adaptation = adapt_population;
  algorithm.termination = cfg.smart_termination ? smart_termination : termination;
  algorithm.mutation = mutation_function;
  algorithm.crossover = crossover_function;
  algorithm.replacement = replacement;
  algorithm.report = report;
  algorithm.report_end = report_end;
  algorithm.run();
}
