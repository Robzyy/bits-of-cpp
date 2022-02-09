#include "arguments.h"
#include "defines.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

ARGUMENTS parse_args(int argc, const char *argv[])
{
    int delay;
    float threshold;

    ARGUMENTS args;

    // Declare the supported options.
    po::options_description config("Config options");
    config.add_options()("delay,d", po::value<int>(&args.delay)->default_value(__DELAY),
                         "Value (in secounds) for how much to wait in between each read.")(
        "threshold,t", po::value<float>(&args.threshold)->default_value(__THRESHOLD),
        "Minimum value (in degrees Celsius) to be considered unsafe and displayed in \033[1;31mbold red\033[0m.");

    po::options_description generic("Generic options");
    generic.add_options()("help,h", "Display this help message and exit.")("version,v",
                                                                           "Display version number and exit.");

    po::options_description all;
    all.add(config).add(generic);

    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, all), vm);
    }
    catch (po::multiple_occurrences e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    catch (po::unknown_option e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    catch (po::invalid_option_value e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }

    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << all << '\n';
        exit(EXIT_SUCCESS);
    }
    else if (vm.count("version"))
    {
        std::cout << "Version " << __VERSION << '\n';
        exit(EXIT_SUCCESS);
    }

    return args;
}