#pragma once

#include <vector>
#include <iostream>

#include "permutation.hpp"

struct job
{
  int deadline;
  int weight;
};

struct weighted_tardiness
{
  std::vector<job> jobs;

  int evaluate(const permutation& p) const;
};
