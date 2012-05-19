#include "population.hpp"

void specimen_rand_swap(population& a, population& b, float pbb){
	int treshold = (int)(pbb*(float)RAND_MAX);
	for(unsigned i = 0; i < a.size(); i++)
		if(rand() < treshold){
			std::swap(a[i],b[i]);
		}
}
