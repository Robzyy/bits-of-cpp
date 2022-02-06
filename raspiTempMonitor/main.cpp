#include "arguments.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <signal.h> // CTRL	C signal processing
#include <string.h> // Arguments processing
#include <unistd.h> // sleep()

using namespace std;

ifstream thermal("/sys/class/thermal/thermal_zone0/temp");
// ifstream thermal("temp.in"); // Test file

void signal_handler(int signum) {
	cout << " - Caught SIGINT signal\nExiting...\n";
	thermal.close();
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
	signal(SIGINT, signal_handler);

	ARGUMENTS args = getArgs(argc, argv);

	cout << fixed << showpoint << setprecision(1);
	float temp = 0, realTemp;
	while (true) {
		thermal.seekg(0, ios::beg);
		thermal >> temp;
		realTemp = temp / 1000;
		if (realTemp >= args.threshold) {
			cout << "\033[1;31m" << realTemp << " C\033[0m\n";
		} else {
			cout << realTemp << " C\n";
		}
		sleep(args.delay);
	}

	return 0;
}
