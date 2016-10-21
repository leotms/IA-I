#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

int gap(state_t state, float weigth = 1) {

  int h = 0;
  int len_state = sizeof(state.vars)/sizeof(state.vars[0]);

  for (int i = 0; i < len_state - 1; i++) {
    if (abs(state.vars[i] - state.vars[i+1]) > 1) {
      h += 1;
    }
  }

  if (abs(state.vars[len_state-1] - len_state) > 1) {
    h += 1;
  }

  h = (weigth*h);
  h = static_cast<int>(h);
  return h;
}

// calculates time difference in miliseconds
float timeinmiliseconds(clock_t start, clock_t stop) {
  return ((float)(stop - start) / CLOCKS_PER_SEC);
}

char * domainname(char * fullname){

  char * domain = (char *) malloc(50*sizeof(char));
  sscanf(fullname,"./%[^.]:", domain);
  return domain;

}

void best_first_search_expansion(state_t state, PriorityQueue<state_t> *open,
                                 state_map_t * distancias,
                                 state_map_t * histories,
                                 long * nStates){

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  init_fwd_iter(&iter, &state);
  int parent_history = *state_map_get(histories, &state);

  while((ruleid = next_ruleid(&iter)) >= 0 ){
    if (fwd_rule_valid_for_history(parent_history, ruleid) != 0){

      *nStates = *nStates + 1;
			apply_fwd_rule(ruleid, &state, &child);

      int child_history = next_fwd_history(parent_history, ruleid);
      int dist = *state_map_get(distancias, &state) + get_fwd_rule_cost(ruleid);
      int cost = dist + gap(child);

      state_map_add(histories, &child, child_history);

      const int *dist_anterior = state_map_get(distancias, &child);

      if (dist_anterior == NULL || *dist_anterior < dist ) {
        state_map_add(distancias, &child, dist);
        open->Add(cost, cost, child);
      }
    }
  }

}

int best_first_seach(state_t state, long * nStates, clock_t start){

  PriorityQueue<state_t> open;
  state_map_t *distancias = new_state_map();
  state_map_t *histories  = new_state_map();


  // Para el primer nodo
  int history = init_history;
  state_map_add(histories, &state, history);
  state_map_add(distancias, &state, 0);

  int costN0 = gap(state);
  // Agregamos a la cola de prioridades.
  open.Add(costN0, costN0, state);

  while(!open.Empty()){

    state = open.Top();
    open.Pop();

    // check if goal
    if (is_goal(&state)){
      return *state_map_get(distancias, &state);
    }
    // check if time's up
    if (timeinmiliseconds(start, clock()) > 300.0){
      // Means the algorithm ran more than 5minutes
      return -2;
    };

    best_first_search_expansion(state, &open, distancias, histories, nStates);
  }

  return -1;
}

int main(int argc, char **argv ) {

    state_t state;
    FILE * inputfile;
    FILE * outputfile;

    if (argc < 3) {
      printf("Missing argument.\nPlease run with ./<problemname>.idastar <inputfile> <outputfile>\n");
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

      int  h0 = gap(state);
      long distance = 0;
      long nStates = 0;

      printf("Solving state: ");
      print_state(stdout, &state);
      printf("\n");

      // Start clock
      clock_t start = clock();

      distance = best_first_seach(state, &nStates, start);

      // total time for the algorithm
      float totalTime = timeinmiliseconds(start,clock());

      fprintf(outputfile,"astar, gap, %s, ", domainname(argv[0]));
      print_state(outputfile, &state);
      if (distance >= 0){
        fprintf(outputfile,", %ld, %d, %ld, %f, %f\n", distance, h0, nStates, totalTime, nStates/totalTime);
      } else {
        fprintf(outputfile,", na, %d, na, na, na\n", h0);
      }
    }

    fclose(inputfile);
    fclose(outputfile);
    printf("\nResults stored in %s\n",argv[2]);
    return 0;

}
