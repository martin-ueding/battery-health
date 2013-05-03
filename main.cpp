// Copyright © 2013 Martin Ueding <dev@martin-ueding.de>

#include <ctime>
#include <fstream>
#include <iostream>

int main() {
	int energy_now;
	int energy_full;
	int energy_full_design;
	int power_now;

	int time = std::time(NULL);

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

	std::cout << "Time		" << time << std::endl;
	std::cout << "Current Charge	" << charge << std::endl;
	std::cout << "Possible Charge	" << max_charge << std::endl;
	std::cout << "Time Left	" << time_left << std::endl;
	std::cout << "Time Until	" << time_until << std::endl;

	return 0;
}
