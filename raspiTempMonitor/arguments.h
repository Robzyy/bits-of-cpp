#ifndef ARGUMENTS_H
#define ARGUMENTS_H
#include <string>

struct ARGUMENTS
{
    int delay = 0;
    float threshold = 0;
    bool showTime = false;
    std::string timeFormat{};
};

ARGUMENTS parse_args(int argc, const char *argv[]);

#endif