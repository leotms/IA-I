#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <limits.h>
#include <time.h>

#define GRAY  0
#define BLACK 1

//** Heuristicas ** //
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

int gap(state_t state) {

 print_state(stdout, &state);

  int h = 0;
  int len_state = sizeof(state.vars)/sizeof(state.vars[0]);

  for (int i = 0; i < len_state; i++) {

    if ((i == len_state - 1) && (abs(state.vars[i] - len_state) > 1)) {
        h += 1;
    } else if (abs(state.vars[i] - state.vars[i+1]) > 1) {
      h += 1;
    }
  }

  return h;
}

/* Funciones */

// calculates time difference in miliseconds
float timeinmiliseconds(clock_t start, clock_t stop) {
  return ((float)(stop - start) / CLOCKS_PER_SEC);
}

char * domainname(char * fullname){

  char * domain = (char *) malloc(50*sizeof(char));
  sscanf(fullname,"./%[^.]:", domain);
  return domain;

}

//* A* *//

int best_first_search_expansion(int (*h)(state_t), state_t state, PriorityQueue<state_t> *q, state_map_t *colores, state_map_t *distancias){

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  long nOpen = 0;

  init_fwd_iter(&iter, &state);

  while((ruleid = next_ruleid(&iter)) >= 0 ) {
				apply_fwd_rule(ruleid, &state, &child);

        int dist = *state_map_get(distancias, &state) + get_fwd_rule_cost(ruleid);
        nOpen++;

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

  return nOpen;
}

int best_first_seach(int (*h)(state_t), state_t state, clock_t start, long * nStates){

  PriorityQueue<state_t> q;
  state_map_t *colores = new_state_map();
  state_map_t *distancias = new_state_map();


  printf("Estro BFS\n");
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
      return *state_map_get(distancias, &state);
    }
    if (timeinmiliseconds(start, clock()) > 300.0) {
      return -2;
    }

    // printf("Entro\n");
    *nStates += best_first_search_expansion(h, state, &q, colores, distancias);

  }

  return -1;
}

int main(int argc, char **argv ) {

  state_t state;
  FILE * inputfile;
  FILE * outputfile;

  if (argc < 3) {
    printf("Missing argument.\nPlease compie with ./<problemname>.dfs <inputfile> <outputfile>\n");
    return 0;
  }

  // we open the files containing the instances
  inputfile  = fopen(argv[1], "r");
  outputfile = fopen(argv[2], "w");

  if (inputfile == NULL || outputfile == NULL){
    printf("Error with input or output files.");
  }

  char *  line = NULL;
  size_t  len = 0;
  ssize_t read;

  fprintf(outputfile,"algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec\n");

  while ((read = getline(&line, &len, inputfile)) != -1) {
    int nchars = read_state(line, &state);
    if( nchars <= 0 ) {
        printf("Error: invalid state in file.\n");
        continue;
    }

    printf("Estados del archivo: ");
    print_state(stdout, &state); printf("\n");

    long distance = 0;
    long nStates = 0;

    clock_t start = clock();
    int h0 = gap(state);
    // printf("SALIO DE LA HEURISTICA: %d\n",h0);
    distance = best_first_seach(gap, state, start, &nStates);
    float totalTime = timeinmiliseconds(start,clock());

    printf(".");

    //*Imprimimos en en el archivo*//
    fprintf(outputfile,"dfid, %s, ", domainname(argv[0]));
    print_state(outputfile, &state);
    if (distance >= 0){
        fprintf(outputfile,", %ld, %d, %ld, %f, %f\n", distance, h0, nStates, totalTime, nStates/totalTime);

    } else if (distance < 0){
        fprintf(outputfile,", na, na, na, na, na\n");
    }

  }

    return 0;
}
