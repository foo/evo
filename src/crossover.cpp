#include "crossover.hpp"

std::pair<permutation, permutation> crossover::random_crossover(crossover::type t, permutation& p1, permutation& p2)
{
  assert(p1.N() == p2.N());

  int n = p1.N();
  int l = n/4;
  int r = randid() % (n-l);
  int s = r+l;
  
  switch(t)
  {
    case OX:
      return ox(p1, p2, r, s);
    case CX:
      return cx(p1, p2, r, s);
    case PMX:
    default: // this line is only for compiler's happiness
      return pmx(p1, p2, r, s);
  }
}

std::pair<permutation, permutation> crossover::ox(permutation& p1, permutation& p2, int r, int s)
{
  if( (s-r)<=1 )
    return std::make_pair(permutation(p1),permutation(p2));
    
  int n = p1.N();
  std::vector<int> result1(p1.begin(), p1.end());
  std::vector<int> tmp1(p1.begin(), p1.end()); // copy parent 1 for computing second child
  std::vector<int> result2(p2.begin(), p2.end());

  std::vector<int>::iterator itr = result1.begin()+r;
  std::vector<int>::iterator its = result1.begin()+s+1;

  // computing first child
  int i = (s+1)%n;
  int res = (s+1)%n;
  while((i != s) || (res != r)){
    i %= n;
    if( its == find( itr, its, result2[i] ))
    {
      result1[res] = result2[i];
      res++;
      res %= n;
    }
    i++;
  }

  // computing second child
  itr = result2.begin()+r;
  its = result2.begin()+s+1;

  i = (s+1)%n;
  res = (s+1)%n;
  while((i != s) || (res != r)){
    i %= n;
    if( its == find( itr, its, tmp1[i] ))
    {
      result2[res] = tmp1[i];
      res++;
      res %= n;
    }
    i++;
  }
  
  return std::make_pair(permutation(result1), permutation(result2));
}

std::pair<permutation, permutation> crossover::cx(permutation& p1, permutation& p2, int r, int s)
{
  std::vector<int> result1,result2;
  int n = p1.N();
  int *cycle = new int[n]; //todo reserve memory during crossovers is rather bad idea ;)
  permutation rev_p1 = p1.reversed();
  
  memset(cycle,0,n*sizeof(int));

  // breaking two permutations into cycles
  int perm_count = 0;
  for(int i=0; i<n; i++)
  {
    if(cycle[i] != 0)
      continue;

    
    int first = i;
    int act = first;
    int next = rev_p1[p2[act]];

    // excluding identity cycle
    if(next == first){ cycle[i]=0; continue;}
    
    perm_count++;
    cycle[act] = perm_count;
    while( next != first )
    {
      act = next;
      next = rev_p1[p2[act]];
      cycle[act] = perm_count;
    }
  }
  
  // producing childeren
  for(int i=0; i<n; i++)
  {
    if(cycle[i] & 1) // oddity test
    {
      result1.push_back(p1[i]);
      result2.push_back(p2[i]);
    }
    else
    {
      result1.push_back(p2[i]);
      result2.push_back(p1[i]);
    }
  }

  //clean-up
  delete [] cycle;

  return std::make_pair(permutation(result1), permutation(result2));
}

std::pair<permutation, permutation> crossover::pmx(permutation& p1, permutation& p2, int r, int s)
{
  assert(p1.N() == p2.N());

  std::vector<int> result1(p1.begin(), p1.end());
  std::vector<int> result2(p2.begin(), p2.end());

  const int empty = -1;
  // make range <r, s> empty
  for(int i = r; i < s + 1; ++i)
    result1[i] = result2[i] = empty;

  // generating result1 from <r,s> part of p2
  for(int i = r; i < s + 1; ++i)
  {
    int p_gene = p2[i];
    int proposed_gene = p_gene;
    while(true)
    {
      if(result1.end() == find(result1.begin(), result1.end(), proposed_gene))
      {
        // no proposed_gene in result1
        result1[i] = proposed_gene;
        break;
      }
      else
      {
        // proposed_gene in result already
        // we should find new value

        proposed_gene = p2[p1.elem_position(proposed_gene)];
      }
    }
  }

  // generating result2 from <r,s> part of p1
  for(int i = r; i < s + 1; ++i)
  {
    int p_gene = p1[i];
    int proposed_gene = p_gene;
    while(true)
    {
      if(result2.end() == find(result2.begin(), result2.end(), proposed_gene))
      {
        // no proposed_gene in result1
        result2[i] = proposed_gene;
        break;
      }
      else
      {
        // proposed_gene in result already
        // we should find new value

        proposed_gene = p1[p2.elem_position(proposed_gene)];
      }
    }
  }

  return std::make_pair(permutation(result1), permutation(result2));
}
