# Copyright © 2013 Martin Ueding <dev@martin-ueding.de>

CC = g++
CPPFLAGS = -O3 --pedantic -std=c++11 -Wall

c_files := $(wildcard *.cpp)
h_files := $(wildcard *.hpp)
o_files := $(c_files:.cpp=.o)

all: battery-health

battery-health: $(o_files)
	$(CC) -o $@ $^

dep: dep.makefile

dep.makefile: $(c_files) $(h_files)
	gcc -MM $(c_files) > $@
	cat $@

-include dep.makefile

.PHONY: clean
clean:
	$(RM) *.o *.out
	$(RM) *.orig
	$(RM) -r battery-health
	$(RM) -r html
	$(RM) dep.makefile
