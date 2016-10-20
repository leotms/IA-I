CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --no_abstraction --history_len=0

psvn2c_core.c:
	cp ../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.astar: %.c ../global/astar.cpp
	$(CXX) $(OPT) ../global/astar.cpp -include $< -o $@
	rm -f $*.c

%.idastar: %.c ../global/idastar.cpp
	$(CXX) $(OPT) ../global/idastar.cpp -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.astar *.idastar psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~
