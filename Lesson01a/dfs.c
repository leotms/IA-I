/*DFS**/
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

int main(int argc, char **argv ) {
    // VARIABLES FOR INPUT
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars; 
    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

    // READ A LINE OF INPUT FROM stdin
    printf("Please enter a state followed by ENTER: ");
    if( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    }

    // CONVERT THE STRING TO A STATE
    nchars = read_state(str, &state);
    if( nchars <= 0 ) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }

    printf("The state you entered is: ");
    print_state(stdout, &state);
    printf("\n");

    // LOOP THOUGH THE CHILDREN ONE BY ONE
    state_t goal = dfs_visitado(&state);
    printf("Goal!");
    print_state(stdout, &goal);

    return 0;
}

state_t dfs_visitado(state_t state) {

    // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;
    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule

	if is_goal(state) return state;

	iter_fwd_iter(&iter, state);
	while( (ruleid = next_ruleid(&iter)) >= 0 ) {
        apply_fwd_rule(ruleid, &state, &child);
        state_t state_aux = dfs_visitado(child);
        if state_aux != NULL return state_aux;
        print_state(stdout, &child);
        printf("  %s (cost %d), goal=%d\n", get_fwd_rule_label(ruleid), get_fwd_rule_cost(ruleid), is_goal(&child));
    }

    return NULL;
}