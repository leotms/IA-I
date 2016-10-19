#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <limits.h>

#define  MAX_LINE_LENGTH 999 

void best_first_search_expansion(state_t state, PriorityQueue<state_t> &q,state_map_t &colores,state_map_t &distancias) {
  
    init_bwd_iter(&iter, &state);
    while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
        apply_fwd_rule(ruleid, &state, &child);
        if (h(child)== INT_MAX){
            continue;
        }

        const int g = state_map_get(distancias, &state) + get_bwd_rule_cost(ruleid);

        // first time encountered
        if (state_map_get(colores, &child)==NULL){
            state_map_add(colores, &child, "Gray");
            state_map_add(distancias, &child, g);
            q.Add(g + h(child), g + h(child), child);
        }

        // a shorter path was found
        else if (g < state_map_add(distancias, &child)){
            state_map_add(distancias, &child, g);
            if (state_map_get(colores, &child) == "Gray"){
                //% re-order and re-link parent
                //q.decrease-priority(child, g+h(child))
            }else{
                // node is black: re-open state!
                state_map_add(colores, &child, "Gray");
                q.Add(g + h(child), g + h(child), child);
            }
        }

    }
}


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

    PriorityQueue<state_t> q; 
    state_map_t *colores = new_state_map(); 
    state_map_t *distancias = new_state_map(); 
    
    state_map_add(distancias, &state, 0);
    q.Add(0, 0, state);

    while( !q.Empty() ) {

        // remove top state from priority state
        state = q.Top();
        q.Pop();

        if is_goal(&state){
            printf("distancia: %d",state_map_get(distancias, &state));
            print_state(stdout,&state);
            printf(" \n");
            break;
        }else{
            best_first_search_expansion(state, q,colores,distancias)
            state_map_add(colores, &state, "black");
        }

    }

    return 0;
}