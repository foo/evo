#include "permutation.hpp"

permutation::permutation(const permutation& p) : perm(p.perm) {}
permutation::permutation(permutation&& p) : perm(std::move(p.perm)) {}
permutation& permutation::operator=(const permutation& p)
{
  if(&p != this)
  {
    perm = p.perm;
  }
  return *this;
}

permutation::permutation(const std::vector<int>& v)
{
  perm.reserve(v.size());
  std::copy(v.begin(), v.end(), back_inserter(perm));
  assert(valid_permutation());
}

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
    std::swap(perm[i], perm[randid() % (i + 1)]);
}

void permutation::gen_identity_perm()
{
  for(int i = 0; i < N(); ++i)
    perm[i] = i;
}

bool permutation::valid_permutation() const
{
  if(N() == 0)
    return false;
  
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

int permutation::elem_position(const int v) const
{
  assert(0 <= v);
  assert(v < N());

  auto i = find(perm.begin(), perm.end(), v);
  assert(i != perm.end());
  return i - perm.begin();
}

void permutation::transpose(const int a, const int b)
{
  std::swap(perm[a], perm[b]);
}

std::ostream& operator << (std::ostream& os, const permutation& p)
{
  os << "[ ";
  for(auto i = p.perm.begin(); i != p.perm.end(); ++i)
    os << *i << ' ';
  os << ']';
  return os;
}

permutation permutation::reversed() const
{
  permutation p;
  p.perm.resize(N());
  for(int i = 0; i < N(); i++)
    p.perm[perm[i]] = i;
  return p;
}

void permutation::rand_swap(permutation& p, float pbb){
	int treshold = (int)(pbb*(float)RAND_MAX);
	int tmp;
	for(int i = 0; i < N(); i++)
		if(rand() < treshold){
			tmp = perm[i];
			perm[i]=p.perm[i];
			p.perm[i] = tmp;
		}
}
