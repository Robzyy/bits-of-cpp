# Raspberry Pi CPU temperature monitor
Simple temperature monitor which features command line arguments (man those are a pain to work with)

## Build from source
It's as easy as it can get!
```
$ g++ main.cpp arguments.cpp -o tempMonitor
```

## Usage
```
$ ./tempMonitor --help
Monitor the CPU temperature of your Raspberry Pi.

Options:
-d, --delay                     Value (in secounds) for how much to wait in between each read.
-h, --help                      Display this help message and exit.
-t, --threshold                 Minimum value (in degrees Celsius) to be considered unsafe
                                and displayed in bold red.
```