#include <vector>
#include "sga.hpp"

class multisga: public sga {
public:
	void run_thread(population &p);
	void run();
};
