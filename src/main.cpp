#include <iostream>
#include <vector>
#include <functional>
#include <thread>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "sga.hpp"
#include "crossover.hpp"

po::variables_map read_command_line(
		po::options_description command_line_args_desc, int argc,
		char* argv[]) {
	po::variables_map args;
	po::store(po::parse_command_line(argc, argv, command_line_args_desc), args);
	po::notify(args);

	return args;
}

po::options_description command_line_args_create() {
	po::options_description command_line_args("Available options");

	command_line_args.add_options()("help,h", "Produce help message.")(
			"debug,d", "Show assignment of command line parameters.")(
			"report-population,R", "Reports whole population.")("report-best,r",
			"Reports best found speciman.")("report-every-frame,e",
			po::value<std::string>(),
			"Reports every frame. Available: best, avg.")("max-iter,i",
			po::value<int>()->default_value(1000),
			"Maximum number of iterations.")("crossover,x",
			po::value<std::string>()->default_value("pmx"),
			"Crossover operators. Available: pmx, cx, ox")(
			"smart-termination,t",
			"Use termination condition that does not depend on --max-iter. Also overrides --max-iter")(
			"optimum,o", po::value<int>(),
			"Program will not stop until it reaches given optimal value (or --max-iter). Also prints number of evaluations.")(
			"report-var,v",
			"Similar to --report-every-frame, but instead best/avg specimen, it prints variance of each population.")(
			"compare-operators,c",
			"Executes program with special mode, in which crossover operation is selected randomly with each iteration. Returns statistical 'power' of each operator.")(
			"set-seed,S", po::value<int>(), "Sets random number seed.")(
			"population-size,p", po::value<int>()->default_value(200),
			"Population size")("ping,a", po::value<int>()->default_value(0),
			"Gives sing that agorithm is still running fine by printing msg after each arg1 iterations.");
	return command_line_args;
}

config interpret_cmd_line_arguments(
		const po::variables_map& command_line_args) {
	config c;

	assert(command_line_args.count("crossover"));
	const std::string crossover_operator = command_line_args["crossover"].as<
			std::string>();
	if (crossover_operator == "pmx")
		c.crossover_type = crossover::type::PMX;
	else if (crossover_operator == "ox")
		c.crossover_type = crossover::type::OX;
	else if (crossover_operator == "cx")
		c.crossover_type = crossover::type::CX;
	else
		throw std::runtime_error("Crossover operator unspecified.");

	if (command_line_args.count("debug"))
		c.debug = true;
	else
		c.debug = false;

	if (command_line_args.count("report-population"))
		c.report_population = true;
	else
		c.report_population = false;

	if (command_line_args.count("report-best"))
		c.report_best = true;
	else
		c.report_best = false;

	if (command_line_args.count("report-every-frame")) {
		const std::string to_report =
				command_line_args["report-every-frame"].as<std::string>();
		if (to_report == "best")
			c.report_every = config::report::best;
		else if (to_report == "avg")
			c.report_every = config::report::avg;
	} else
		c.report_every = config::report::none;

	if (command_line_args.count("smart-termination"))
		c.smart_termination = true;
	else
		c.smart_termination = false;

	if (command_line_args.count("optimum"))
		c.optimum = command_line_args["optimum"].as<int>();
	else
		c.optimum = -1;

	if (command_line_args.count("report-var"))
		c.report_var = true;
	else
		c.report_var = false;

	if (command_line_args.count("compare-operators"))
		c.compare_operators = true;
	else
		c.compare_operators = false;

	if (command_line_args.count("population-size"))
		c.population_size = command_line_args["population-size"].as<int>();
	else
		c.population_size = 200;

	if (command_line_args.count("ping"))
		c.ping_frequency = command_line_args["ping"].as<int>();
	else
		c.ping_frequency = 0;

	assert(command_line_args.count("max-iter"));
	c.max_iter = command_line_args["max-iter"].as<int>();

	if (command_line_args.count("set-seed"))
		c.seed = command_line_args["set-seed"].as<int>();
	else
		c.seed = 0;
	return c;
}

void read_cmd_params(int argc, char* argv[]) {
	po::options_description command_line_args_desc = command_line_args_create();
	po::variables_map command_line_args = read_command_line(
			command_line_args_desc, argc, argv);

	if (command_line_args.count("crossover")) {
		const std::string crossover_operator =
				command_line_args["crossover"].as<std::string>();
		std::cout << "crossover operator: " << crossover_operator << std::endl;
	}

	if (command_line_args.count("help")) {
		std::cout << command_line_args_create() << "\n";
	}
}

int main(int argc, char* argv[]) {
	try {
		po::options_description command_line_args_desc =
				command_line_args_create();
		po::variables_map command_line_args = read_command_line(
				command_line_args_desc, argc, argv);

		if (command_line_args.count("help")) {
			std::cout << command_line_args_create() << "\n";
			return 0;
		}

		config cfg = interpret_cmd_line_arguments(command_line_args);

		weighted_tardiness wt;
		wt.read_problem_instance();

		int threads_count = 4;
		int merge_count = 10;
		std::vector<std::thread> threads;
		std::mutex mut;
		std::vector<population> populations;

		for(int j=0; j < merge_count; j++){
			for (int i = 0; i < threads_count; i++) {
				threads.push_back(
						std::thread([cfg,wt,&populations,&mut,i,j]() {
					sga *s = new sga(cfg,wt);
					population p;
					if(j==0){
						p= s->solve_flowshop();
						mut.lock();
						populations.push_back(p);
						mut.unlock();
					}else{
						p = populations[i];
						p= s->solve_flowshop(p);
						populations[i] = p;
					}

				}));
			}
			try {
				for (std::thread& t : threads) {
					t.join();
				}
			} catch (std::system_error & e) {
				std::cout << "Error: thread joining" << std::endl;
			}
			std::cout << std::endl;
			threads.clear();

			for(int i=0; i<threads_count-1; i++){
				specimen_rand_swap(populations[i],populations[i+1], 0.0);
			}
		}
		//---------
		/*std::cout << std::endl;
		threads.clear();
		for (int i = 0; i < threads_count; i++) {
			threads.push_back(
					std::thread([cfg,&populations,wt,&mut,i]() {
				sga *s = new sga(cfg,wt);

				mut.lock();
				//std::cout << "pop[1]" << populations[0][1].perm << " " << i << std::endl;
				population p = populations[i];
				mut.unlock();
				s->solve_flowshop(p);

			}));
		}
		try {
			for (std::thread& t : threads) {
				t.join();
			}
		} catch (std::system_error & e) {
			std::cout << "Error: thread joining" << std::endl;
		}*/

	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	return 0;
}
