error_flags = -Wall -Werror
std_flag = -std=c++0x
compiler = g++-4.6
libs = -l boost_program_options

modules = random.o permutation.o statistics.o mutation.o crossover.o sga.o flowshop.o problem.o

out = evo.e brute.e

all: $(out)

random.o: random.cpp random.hpp
	$(compiler) $(error_flags) $(std_flag) -c random.cpp -o random.o

permutation.o: permutation.cpp permutation.hpp
	$(compiler) $(error_flags) $(std_flag) -c permutation.cpp -o permutation.o

statistics.o: statistics.cpp statistics.hpp
	$(compiler) $(error_flags) $(std_flag) -c statistics.cpp -o statistics.o

mutation.o: mutation.cpp mutation.hpp
	$(compiler) $(error_flags) $(std_flag) -c mutation.cpp -o mutation.o

crossover.o: crossover.cpp crossover.hpp
	$(compiler) $(error_flags) $(std_flag) -c crossover.cpp -o crossover.o

sga.o: sga.cpp sga.hpp
	$(compiler) $(error_flags) $(std_flag) -c sga.cpp -o sga.o

flowshop.o: flowshop.cpp flowshop.hpp
	$(compiler) $(error_flags) $(std_flag) -c flowshop.cpp -o flowshop.o

problem.o: problem.cpp problem.hpp
	$(compiler) $(error_flags) $(std_flag) -c problem.cpp -o problem.o

evo.e: main.cpp $(modules)
	$(compiler) $(error_flags) $(std_flag) main.cpp $(modules) $(libs) -o evo.e

brute.e: random-bruteforce.cpp random.o flowshop.o permutation.o
	$(compiler) $(error_flags) $(std_flag) random-bruteforce.cpp random.o flowshop.o permutation.o $(libs) -o brute.e

clear:
	rm $(out) $(modules)
