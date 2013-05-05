// Copyright © 2013 Martin Ueding <dev@martin-ueding.de>

#include <boost/program_options.hpp>
#include <ctime>
#include <fstream>
#include <iostream>

namespace po = boost::program_options;

po::variables_map parse_args(int argc, char **argv) {
	std::string foldername = std::string(getenv("HOME")) + std::string("/.local/share/battery-health");

	po::options_description desc("Allowed Options");
	desc.add_options()
		("help", "Display help")
		("folder", po::value<std::string>()->default_value(foldername), "Output folder")
		;

	po::variables_map options;
	try {
		po::store(po::parse_command_line(argc, argv, desc), options);
	}
	catch (...) {
		std::cout << desc << std::endl;
		throw;
	}
	po::notify(options);


	return options;
}

int main(int argc, char **argv) {
	po::variables_map options = parse_args(argc, argv);

	std::string foldername = options["folder"].as<std::string>();
	std::cout << foldername << std::endl;

	int energy_now;
	int energy_full;
	int energy_full_design;
	int power_now;

	int time = std::time(NULL);

	// TODO Create folder automatically.

	std::ifstream in;

	in.open("/sys/class/power_supply/BAT0/energy_now");
	in >> energy_now;
	in.close();

	in.open("/sys/class/power_supply/BAT0/energy_full");
	in >> energy_full;
	in.close();

	in.open("/sys/class/power_supply/BAT0/energy_full_design");
	in >> energy_full_design;
	in.close();

	in.open("/sys/class/power_supply/BAT0/power_now");
	in >> power_now;
	in.close();

	double charge = (double) energy_now / energy_full;
	double max_charge = (double) energy_full / energy_full_design;
	double time_left = (double) energy_now / power_now;
	int time_until = time + 3600 * time_left;

	std::ofstream out;

	out.open(foldername+"/charge.txt", std::fstream::app);
	out << time << "\t" << charge << "\t" << max_charge << std::endl;
	out.close();

	out.open(foldername+"/timeleft.txt", std::fstream::app);
	out << time << "\t" << time_left << std::endl;
	out.close();

	out.open(foldername+"/powernow.txt", std::fstream::app);
	out << time << "\t" << power_now / 1000000. << std::endl;
	out.close();

	out.open(foldername+"/timeuntil.txt", std::fstream::app);
	out << time << "\t" << time_until << std::endl;
	out.close();

	return 0;
}
