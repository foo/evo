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

void specimen_rand_swap(population& a, population& b, float pbb);


