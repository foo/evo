#include "statistics.hpp"

int statistics::edit_distance( const permutation& a, const permutation& b )
{
  assert(a.N() == b.N());

  permutation p = a;
  permutation rp = p.reversed(); // move used instead of copying
  int res = 0;
  int n = p.N();
  
  for(int i=0; i<n; i++)
  {
    if(p[i] != b[i])
    {
      p.transpose(i, rp[b[i]]);
      res++;
    }
  }
  
  return res;
}

int statistics::specimen_variance( const population& p, const int i )
{
  int n = p.size();
  int sum = 0;
  int e;
  
  for(int j=0; j<n; j++)
  {
    if(i == j)
      continue;
    e = edit_distance(p[i].perm,p[j].perm);
    sum += e*e;
  }

  return sum;
}

// returns variance of population p
int statistics::variance( const population& p )
{
  assert(p.size() > 0);

  int v = specimen_variance(p, 0);
  int v2;
  
  // we look for variance of avarage specimen
  for(unsigned int i=1; i<p.size(); i++)
  {
    v2 = specimen_variance(p, i);
    if( v2 < v )
      v = v2;
  }

  return v;
}


