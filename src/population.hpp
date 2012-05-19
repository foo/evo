#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include "permutation.hpp"

struct specimen {
	permutation perm;
	float eval, adapt; // evaluation and adaptation value

	specimen& operator=(const specimen& s) {
		if (this != &s) {
			perm = s.perm;
			eval = s.eval;
			adapt = s.adapt;
		}
		return *this;
	}
};

typedef std::vector<specimen> population;

void specimen_rand_swap(population& a, population& b, float pbb){
	int treshold = (int)(pbb*(float)RAND_MAX);
	for(unsigned i = 0; i < a.size(); i++)
		if(rand() < treshold){
			std::swap(a[i],b[i]);
			/*tmp = a[i];
			a[i]=b[i];
			b[i] = tmp;*/
		}
}

#endif
