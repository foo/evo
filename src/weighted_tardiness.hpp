#pragma once

#include <vector>
#include <iostream>

#include "permutation.hpp"

struct job
{
  int weight;
  int processing_time;
  int deadline;
  
  static job read_job_instance();
};

struct weighted_tardiness
{
  std::vector<job> jobs;

  void read_problem_instance();

  int evaluate(const permutation& p) const;
};
