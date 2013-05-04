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

	// TODO Create folder automatically.

	std::string foldername = std::string(getenv("HOME")) + std::string("/.local/share/battery-health");

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
