#include <vector>
#include "priority_queue.hpp"

int main(int argc, char **argv) {
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;
    ruleid_iterator_t iter;

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated


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

    open.Add(0,0,state);
    state_map_add(map, &state, 0);

    d = 0;
    while( !open.Empty() ) {
        // get current distance from goal; since operator costs are
        // non-negative this distance is monotonically increasing
        d = open.CurrentPriority();

        // remove top state from priority state
        state = open.Top();
        open.Pop();
        
        // check if we already expanded this state.
        // (entries on the open list are not deleted if a cheaper path to a state is found)
        const int *best_dist = state_map_get(map, &state);
        assert(best_dist != NULL);
        if( *best_dist < d ) continue;
        
        // print the distance then the state
        printf("%d  ",d);
        print_state(stdout,&state);
        printf(" \n");

        // look at all predecessors of the state
        init_fwd_iter(&iter, &state);
        while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
            apply_fwd_rule(ruleid, &state, &child);
            const int child_d = d + get_fwd_rule_cost(ruleid);

            // check if either this child has not been seen yet or if
            // there is a new cheaper way to get to this child.
            const int *old_child_d = state_map_get(map, &child);
            if( (old_child_d == NULL) || (*old_child_d > child_d) ) {
                // add to open with the new distance
                state_map_add(map, &child, child_d);
                open.Add(child_d, child_d, child);
            }
        }
    }

    state_t goal_state;
    first_goal_state(&goal_state, &d);

    const int *best_dist = state_map_get(map, &goal_state);

    printf("Mejor Distancia al Goal %d \n", best_dist);

    return 0;
}