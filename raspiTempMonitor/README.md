# Raspberry Pi CPU temperature monitor
Simple temperature monitor because I didn't find one in 2 minutes of web searching 

## Build from source
It relies on [`Boost.Program_options`](https://www.boost.org/doc/libs/1_78_0/doc/html/program_options.html) so make sure boost libraries are installed. If not present, install them:
```
# apt install libboost-all-dev
```

```
$ g++ main.cpp arguments.cpp -L/usr/local/lib -lboost_program_options -o tempMonitor
```

## Usage
```
$ ./tempMonitor --help

Config options:
  -d [ --delay ] arg (=2)       Value for how many seconds to wait in between 
                                each read.
  -- time  [=arg(=%H:%M:%S)]    Display formatted time alongside temperature.
  -t [ --threshold ] arg (=80)  Minimum value (in degrees Celsius) to be 
                                considered unsafe and displayed in bold 
                                red.

Generic options:
  -h [ --help ]                 Display this help message and exit.
  -v [ --version ]              Display version number and exit.

```