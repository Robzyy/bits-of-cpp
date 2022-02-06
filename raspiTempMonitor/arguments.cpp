#include <iostream>
#include <string.h>
#include "arguments.h"

ARGUMENTS getArgs(int argc, char *argv[]) {
	ARGUMENTS args;

	// std::cout << "Printing arguments:\n"; 	// debug
	// std::cout << "argc = " << argc << '\n';	// debug

	for (int i = 0; i < argc; i++) {
		bool unexpectedArg = true; // Assume there is an unexpected argument
		// std::cout << argv[i] << '\n';	// debug

		// Check for --help or -h argument
		if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
			unexpectedArg = false;
			std::cout << "Monitor the CPU temperature of your Raspberry Pi.\n\n";
			std::cout << "Options:\n";

			std::cout
				<< "-d, --delay\t\t\tValue (in secounds) for how much to wait "
				   "in between each read.\n";

			std::cout
				<< "-h, --help\t\t\tDisplay this help message and exit.\n";

			std::cout
				<< "-t, --threshold\t\t\tMinimum value (in degrees Celsius) "
				   "to be considered unsafe\n\t\t\t\tand displayed in "
				   "\033[1;31mbold red\033[0m.\n";
			// OK, I fell like
			// /t/t/t/t/t//t/t/t/t/tt//t/t/t
			// is bad, I have no clue
			// how to improve this.
			exit(EXIT_SUCCESS);
		}

		// Check for --delay or -d argument
		if (strcmp(argv[i], "--delay") == 0 || strcmp(argv[i], "-d") == 0) {
			unexpectedArg = false;
			if (i < argc - 1) { // Does the next argument exist?
				args.delay = atoi(argv[i + 1]);
				if (args.delay == 0) { // Damn that wasn't a number though
					std::cout << "Args fail\n";
					exit(EXIT_FAILURE);
				}
				i++;
			} else {
				std::cout << "Args fail\n";
				exit(EXIT_FAILURE);
			}
		}

		// Check for --threshold or -t argument
		if (strcmp(argv[i], "--threshold") == 0 || strcmp(argv[i], "-t") == 0) {
			unexpectedArg = false;
			if (i < argc - 1) { // Does the next argument exist?
				args.threshold = atof(argv[i + 1]);
				if (args.threshold == 0) { // Damn that wasn't a number though
					std::cout << "Args fail\n";
					exit(EXIT_FAILURE);
				}
				i++;
			} else {
				std::cout << "Args fail\n";
				exit(EXIT_FAILURE);
			}
		}

		if (unexpectedArg && i != 0) {
			std::cout << "Unexpected arguments\n";
			exit(EXIT_FAILURE);
		}
	}

	// debug:
	// std::cout << "------------------------------\n";
	// std::cout << "Processed arguments:\n";
	// std::cout << "delay = " << args.delay << '\n';
	// std::cout << "threshold = " << args.threshold << '\n';
	// std::cout << "------------------------------\n\n";

	return args;
}