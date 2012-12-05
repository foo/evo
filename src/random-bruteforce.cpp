#include <iostream>

#include "random.hpp"
#include "sdvrp.hpp"
#include "permutation.hpp"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

sdvrp f;
int N,M;

po::variables_map read_command_line(po::options_description command_line_args_desc, int argc, char* argv[])
{
  po::variables_map args;
  po::store(po::parse_command_line(argc, argv, command_line_args_desc), args);
  po::notify(args);
  
  return args;
}

po::options_description command_line_args_create()
{
  po::options_description command_line_args("Available options");

  command_line_args.add_options()
    ("help,h", "Produce help message.")
    ("max-eval,i", po::value<int>()->default_value(1000), "Maximum number of evaluations.")
    ("report-every,e", po::value<int>(), "Reports best specimen of N evaluations")
    ;
  return command_line_args;
}


void read_input()
{
  std::cin >> N;
  std::cin >> M;

  f.initialize(N,M);

  for(int x = 0; x < M; ++x)
    for(int y = 0; y < N; ++y)
      std::cin >> f[x][y];
}

int main(int argc, char* argv[])
{
  srand(time(0));
  try
  {
    po::options_description command_line_args_desc = command_line_args_create();
    po::variables_map command_line_args = read_command_line(command_line_args_desc, argc, argv);

    if(command_line_args.count("help"))
    {
      std::cout << command_line_args_create() << "\n";
      return 0;
    }

    read_input();

    int evals = command_line_args["max-eval"].as<int>() - 1;

    permutation best_p(N, permutation::type::random);
    int best = f.route_cost(best_p.P());
    int acc;
    int i = 0;
    int best_of_N = f.route_cost(best_p.P());
    int report_every = command_line_args["report-every"].as<int>();
    while(i <= evals)
    {
      i++;
      permutation p(N, permutation::type::random);
      acc = f.route_cost(p.P());
    
      if(command_line_args.count("report-every"))
      {
        if(acc < best_of_N)
          best_of_N = acc;
        if(i != 0 && i % report_every == 0)
        {
          std::cout << i / report_every << ' ' << best_of_N << "\n";
          best_of_N = INT_MAX;
        }
      }

      if(acc < best)
      {
        best = acc;
        best_p = p;
      }
    }
    if(!command_line_args.count("report-every"))
      std::cout << best << " = " << best_p << "\n";
  }
  catch(std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
