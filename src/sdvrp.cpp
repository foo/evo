#include "sdvrp.hpp"

void sdvrp::initialize(int N)
{
  size = N;
  
  graph.resize(N);
  for(int j = 0;j < N; ++j)
    graph[j].resize(N);
}

int sdvrp::route_cost(const std::vector<int> &v)
{
  int days = 0;
  int hours_used = 0;
  for(unsigned int i=0; i<size-1; i+=3)
  {
    const int v1 = v[i];
    const int v2 = v[i+1];
    const int v3 = v[i+2];
    const int base = size - 1;

    // cost trip in hours
    const int trip_cost = graph[base][v1] + graph[v1][v2] + graph[v2][v3] + graph[v3][base]; 
    if(trip_cost > 8)
      return INT_MAX; // infinity
    
    if(trip_cost + hours_used <= 8)
      hours_used += trip_cost;
    else
      {
	// new day job
	hours_used = 0;
	++days;
      }
  }
  if(hours_used != 0)
    ++days;
  return days;
}


std::ostream& operator << (std::ostream& os, const sdvrp& f)
{
  os << "Print sdvrp instance";
  return os;
}
