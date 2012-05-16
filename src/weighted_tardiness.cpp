#include "weighted_tardiness.hpp"

int weighted_tardiness::evaluate(const permutation& p) const
{
  return 1001;
}

job job::read_job_instance()
{
  job j;
  cin >> j.weight >> j.processing_time >> j.deadline;
  return j;
}

void weighted_tardiness::read_problem_instance()
{
  int jobs_number;
  std::cin >> jobs_number;

  for(int i = 0; i < N; ++i)
    jobs.push_back(job::read_job_instance());
}
