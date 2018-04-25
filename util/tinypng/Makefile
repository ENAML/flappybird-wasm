# main : main.c
# 	gcc -I../ -Wall -Werror -pedantic main.c -o $@

# .PHONY: clean
# clean:
# 	rm -rf atlas.png atlas.txt main

# .PHONY:clean-atlas 
# clean-atlas:
# 	rm -rf atlas.png atlas.txt main

CC  = gcc
CXX = g++ 

# Comment out one of the following 2 lines to enable/disable BASIC4TRACE.
# INCLUDES = -DBASIC4TRACE
INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g
LDLIBS  =

# executables = test1 test2 test3 test4 test5
# objects = mystring.o test1.o test2.o test3.o test4.o test5.o

main: main.o tinypng_impl.o

# isort: isort.o intarr.o random.o
# isort.o: isort.c isort.h intarr.h
# intarr.o: intarr.c intarr.h random.h
# random.o: random.c random.h

main.o: main.c tinypng.h

tinypng_impl.o: tinypng_impl.c tinypng.h

# $(executables): mystring.o

# $(objects): mystring.h


.PHONY: clean
clean:
	rm -rf *~ a.out main main.o tinypng_impl.o 

.PHONY:clean-bin 
clean-bin:
	rm -rf bin/**/*.png

.PHONY: all
all: clean default