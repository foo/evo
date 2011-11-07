#include "permutation.hpp"

permutation::permutation(const int N, const type t)
{
  perm.resize(N);

  switch(t)
  {
    case random:
      gen_random_perm();
      break;
    case identity:
      gen_identity_perm();
      break;
  }
  
  assert(valid_permutation());
}

void permutation::gen_random_perm()
{
  for(int i = 0; i < N(); ++i)
    perm[i] = i;
  for(int i = 0; i < N(); ++i)
    std::swap(perm[i], perm[rand() % (i + 1)]);
}

void permutation::gen_identity_perm()
{
  for(int i = 0; i < N(); ++i)
    perm[i] = i;
}

bool permutation::valid_permutation() const
{
  std::vector<bool> is_in(N(), false);
  for(int i = 0; i < N(); ++i)
    if(is_in[perm[i]])
      return false; // two elements of value p[i]
    else
      is_in[perm[i]] = true;
  for(int i = 0; i < N(); ++i)
    if(!is_in[i])
      return false; // no element of value i
  return true;
}

std::ostream& operator << (std::ostream& os, const permutation& p)
{
  os << "[ ";
  for(auto i = p.perm.begin(); i != p.perm.end(); ++i)
    os << *i << ' ';
  os << ']';
  return os;
}
