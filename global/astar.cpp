#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <limits.h>

#define GRAY  0
#define BLACK 1

int h(state_t state){
  return 1;
}

void best_first_search_expansion(state_t state, PriorityQueue<state_t> *q, state_map_t *colores, state_map_t *distancias){

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;


  init_fwd_iter(&iter, &state);

  while((ruleid = next_ruleid(&iter)) >= 0 ) {
				apply_fwd_rule(ruleid, &state, &child);
        printf("HIJOS: ");
        print_state(stdout, &child);
        printf("\n");
        int dist = *state_map_get(distancias, &state) + get_fwd_rule_cost(ruleid);

        if (state_map_get(colores, &child) == NULL) {

          state_map_add(colores, &child, GRAY);
          state_map_add(distancias, &child, dist);
          q->Add(dist + h(state), dist + h(state), child);

        } else if (dist < *state_map_get(colores, &child)){
          state_map_add(distancias, &child, dist);

          if (*state_map_get(colores, &child) == BLACK){
            q->Add(dist + h(state), dist + h(state), child);
          }
        }
			}
}

void best_first_seach(int (*h)(state_t)){

  char* estadostr = "3 1 4 5 b 2 6 7 8 9 10 11 12 13 14 15";
  // char * estadostr = "B 1 2 3 4 5 6 7 8 9 10 11";
  state_t state;

  int nchars = read_state(estadostr, &state);

  PriorityQueue<state_t> q;
  state_map_t *colores = new_state_map();
  state_map_t *distancias = new_state_map();


  // Para el primer nodo
  state_map_add(colores, &state, GRAY);
  state_map_add(distancias, &state, 0);

  // Agregamos a la cola de prioridades.
  q.Add(h(state), h(state), state);

  while(!q.Empty()){

    state = q.Top();
    q.Pop();

    //check if goal
    if (is_goal(&state)){
      printf("Distance to goal: %d\n",*state_map_get(distancias, &state));
      return;
    }

    best_first_search_expansion(state, &q, colores, distancias);


  }
}


int main(int argc, char **argv ) {

    best_first_seach(h);


    // // VARIABLES FOR INPUT
    // char str[MAX_LINE_LENGTH + 1];
    // ssize_t nchars;
    // state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.
    //
    // // READ A LINE OF INPUT FROM stdin
    // printf("Please enter a state followed by ENTER: ");
    // if( fgets(str, sizeof str, stdin) == NULL ) {
    //     printf("Error: empty input line.\n");
    //     return 0;
    // }
    //
    // // CONVERT THE STRING TO A STATE
    // nchars = read_state(str, &state);
    // if( nchars <= 0 ) {
    //     printf("Error: invalid state entered.\n");
    //     return 0;
    // }
    //
    // printf("The state you entered is: ");
    // print_state(stdout, &state);
    // printf("\n");
    //
    // PriorityQueue<state_t> q;
    // state_map_t *colores = new_state_map();
    // state_map_t *distancias = new_state_map();
    //
    // state_map_add(distancias, &state, 0);
    // q.Add(0, 0, state);
    //
    // while( !q.Empty() ) {
    //     printf("entro\n");
    //
    //     // remove top state from priority state
    //     state = q.Top();
    //     q.Pop();
    //
    //     printf("Estado:\n");
    //     print_state(stdout, &state);
    //
    //     if (is_goal(&state)){
    //         printf("distancia: %d",*state_map_get(distancias, &state));
    //         print_state(stdout,&state);
    //         printf(" \n");
    //         break;
    //     }else{
    //         printf("entro2\n");
    //         best_first_search_expansion(state, q, colores, distancias);
    //         state_map_add(colores, &state, BLACK);
    //     }
    //
    // }

    return 0;
}
