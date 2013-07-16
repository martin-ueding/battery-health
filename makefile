# Copyright © 2013 Martin Ueding <dev@martin-ueding.de>

CC = g++
CPPFLAGS = -O3 --pedantic -std=c++11 -Wall
LDLIBS = -lboost_filesystem -lboost_program_options -lboost_system

c_files := $(wildcard *.cpp)
h_files := $(wildcard *.hpp)
o_files := $(c_files:.cpp=.o)

all: battery-health

battery-health: $(o_files)
	$(CC) -o $@ $^ $(LDLIBS)

dep: dep.makefile

dep.makefile: $(c_files) $(h_files)
	gcc -MM $(c_files) > $@
	cat $@

install:
	install -d "$(DESTDIR)/usr/bin"
	install battery-health -t "$(DESTDIR)/usr/bin"
	install battery-health-plot -t "$(DESTDIR)/usr/bin"
	install submit-battery-status -t "$(DESTDIR)/usr/bin"

-include dep.makefile

distclean: clean

.PHONY: clean
clean:
	$(RM) *.o *.out
	$(RM) *.orig
	$(RM) -r battery-health
	$(RM) -r html
	$(RM) dep.makefile
