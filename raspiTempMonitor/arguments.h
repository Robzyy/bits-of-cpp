#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#define DELAY 2
#define THRESHOLD 80.0

struct ARGUMENTS {
	int delay = DELAY;
	float threshold = THRESHOLD;
};

struct ARGUMENTS getArgs(int argc, char *argv[]);

#endif