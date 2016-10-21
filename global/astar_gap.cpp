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

int manhatan(state_t state){
  int h = 0;
  unsigned mtable[16][16] = {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
      {0,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4},
      {0,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
      {0,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
      {0,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
      {0,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
      {0,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
      {0,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
      {0,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
      {0,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
      {0,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
      {0,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
      {0,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
      {0,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
      {0,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}
  };

  for (int i = 0; i < 16; i++){
    h += mtable[state.vars[i]][i];
  }

  return h;
}

void best_first_search_expansion(state_t state, PriorityQueue<state_t> *q, 
                                 state_map_t *colores, state_map_t *distancias,
                                 state_map_t * histories){

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;


  init_fwd_iter(&iter, &state);
  int parent_history = *state_map_get(histories, &state);

  while((ruleid = next_ruleid(&iter)) >= 0 ){
    if (fwd_rule_valid_for_history(parent_history, ruleid) != 0){
			apply_fwd_rule(ruleid, &state, &child);
      int child_history = next_fwd_history(parent_history, ruleid);

      int dist = *state_map_get(distancias, &state) + get_fwd_rule_cost(ruleid);
      int cost = dist + manhatan(child);

      state_map_add(histories, &child, child_history);

      if (state_map_get(colores, &child) == NULL) {

        state_map_add(colores, &child, GRAY);
        state_map_add(distancias, &child, dist);
        q->Add(cost, cost, child);

      } else if (dist < *state_map_get(colores, &child)){
        state_map_add(distancias, &child, dist);
        if (*state_map_get(colores, &child) == BLACK){
          q->Add(cost, cost, child);
        }
      }
    }
  }
}

void best_first_seach(){

  char * estadostr = "7 15 8 2 13 6 3 12 11 B 4 10 9 5 1 14";
  state_t state;

  int nchars = read_state(estadostr, &state);

  PriorityQueue<state_t> q;
  state_map_t *colores    = new_state_map();
  state_map_t *distancias = new_state_map();
  state_map_t *histories  = new_state_map();


  // Para el primer nodo
  int history = init_history;
  state_map_add(colores, &state, GRAY);
  state_map_add(distancias, &state, 0);
  state_map_add(histories, &state, history);

  int costN0 = manhatan(state);
  // Agregamos a la cola de prioridades.
  q.Add(costN0, costN0, state);

  while(!q.Empty()){

    state = q.Top();
    q.Pop();

    //check if goal
    if (is_goal(&state)){
      printf("Distance to goal: %d\n",*state_map_get(distancias, &state));
      return;
    }

    best_first_search_expansion(state, &q, colores, distancias, histories);


  }
}

int main(int argc, char **argv ) {

    best_first_seach();

    return 0;
}
