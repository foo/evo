#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <math.h>

class sdvrp
{
  std::vector<std::vector<int> > graph;
  unsigned int size;
public:
  void initialize(int N);
  // access to time_table of machines through [] operator
  std::vector<int>& operator [] ( unsigned int n ) { assert(n < size); return graph[n]; };

  int route_cost(const std::vector<int> &v);
  friend std::ostream& operator << (std::ostream& os, const sdvrp& f);
};
