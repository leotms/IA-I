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

%.stateCount: %.c ../global/stateCount.cpp
	$(CXX) $(OPT) ../global/stateCount.cpp -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.stateCount psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~ *.c
