# meminfo_sort
C++ cli app  
Print /proc/meminfo lines sorted by memory size  
GCC 11.3 + Makefile

## Tested at
ubuntu22 x86_64,  
arm-gnueabihf,  
cygwin x86_64.  

## How to build
`make` or `make all` - release build,  
`make debug` - build for debug,  
`make CROSS_COMPILE=arm-linux-gnueabihf-` or `make CROSS_COMPILE=/path/to/toolchain/arm-some-gnueabihf-` - cross-build   

Build creates `bin/` subdirectory with objects and final application

