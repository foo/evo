#include "weighted_tardiness.hpp"

int weighted_tardiness::evaluate(const permutation& p) const
{
  int cost = 0;
  int time = 0;
  for(int i = 0; i < p.N(); ++i)
  {
    const int processing_job_no = p[i];
    const job& processing_job = jobs[processing_job_no];

    // process job
    time += processing_job.processing_time;
    const int delay = std::max(0, time - processing_job.deadline);
    const int penalty = delay * processing_job.weight;
    cost += penalty;
  }
  return cost;
}

job job::read_job_instance()
{
  job j;
  std::cin >> j.weight >> j.processing_time >> j.deadline;
  return j;
}

void weighted_tardiness::read_problem_instance()
{
  int jobs_number;
  std::cin >> jobs_number;

  for(int i = 0; i < jobs_number; ++i)
    jobs.push_back(job::read_job_instance());
}
