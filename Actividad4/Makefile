CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --no_abstraction --backward_moves
N = 0

psvn2c_core.c:
	cp ../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT) --name=$(*F) --history_len=$(N) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.astar_gap: %.c ../global/astar_gap.cpp
	$(CXX) $(OPT) ../global/astar_gap.cpp -include $< -o $@
	rm -f $*.c

%.astar_manhatan: %.c ../global/astar_manhatan.cpp
	$(CXX) $(OPT) ../global/astar_manhatan.cpp -include $< -o $@
	rm -f $*.c

%.idastar_manhatan: %.c ../global/idastar_manhatan.cpp
	$(CXX) $(OPT) ../global/idastar_manhatan.cpp -include $< -o $@
	rm -f $*.c

%.idastar_gap: %.c ../global/idastar_gap.cpp
	$(CXX) $(OPT) ../global/idastar_gap.cpp -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.astar_gap *.astar_manhatan *.idastar_gap *.idastar_manhatan psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~ *.c
