#pragma once

#include "population.hpp"

namespace statistics
{
  int edit_distance( const permutation& a, const permutation& b );
  int specimen_variance( const population& p, const int i);
  int variance( const population& p);
}
