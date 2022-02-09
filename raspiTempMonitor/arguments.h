#ifndef ARGUMENTS_H
#define ARGUMENTS_H

struct ARGUMENTS
{
    int delay = 0;
    float threshold = 0;
};

ARGUMENTS parse_args(int argc, const char *argv[]);

#endif