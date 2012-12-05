#include "sdvrp.hpp"

void sdvrp::initialize(int N)
{
  size = N;
  
  for(int i = 0; i < N; ++i)
    graph.resize(N);
}

int sdvrp::route_cost(const std::vector<int> &v)
{
  return 0;
}


std::ostream& operator << (std::ostream& os, const sdvrp& f)
{
  os << "Print sdvrp instance";
  return os;
}
