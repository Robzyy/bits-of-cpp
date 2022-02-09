#include "arguments.h"
#include "defines.h"
#include <boost/program_options.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <signal.h> // CTRL	C signal processing
#include <unistd.h> // sleep()

void signal_handler(int signum)
{
    std::cout << " - Caught SIGINT signal\nExiting...\n";
    exit(EXIT_SUCCESS);
}

int main(int argc, const char *argv[])
{
    signal(SIGINT, signal_handler);

#if __DEBUG == 0
    std::ifstream thermal("/sys/class/thermal/thermal_zone0/temp");
#else
    std::ifstream thermal("temp.in"); // Test file
#endif

    ARGUMENTS args = parse_args(argc, argv);

    std::cout << std::fixed << std::showpoint << std::setprecision(1);

    float temp = 0, realTemp = 0;
    while (true)
    {
#if __DEBUG == 0
        thermal.seekg(0, std::ios::beg);
#endif
        thermal >> temp;
        realTemp = temp / 1000;
        if (realTemp >= args.threshold)
        {
            std::cout << "\033[1;31m" << realTemp << " C\033[0m\n";
        }
        else
        {
            std::cout << realTemp << " C\n";
        }
        sleep(args.delay);
    }
}
