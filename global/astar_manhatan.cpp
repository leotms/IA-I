#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

// Uses Best First Search with Manhatan Heuristic to
// create A* algorithm that solves the
// Pancakes Problem.

// Manhatan Heuristic
int manhatan(state_t state, float weigth = 1){
  int h = 0;
  unsigned mtable[16][16] = {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
      {2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4},
      {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
      {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
      {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
      {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
      {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
      {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
      {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
      {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
      {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
      {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
      {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
      {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
      {6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}
  };

  for (int i = 0; i < 16; i++){
    h += mtable[state.vars[i]][i];
  }

  h = (weigth*h);
  h = static_cast<int>(h);
  return h;
}

// calculates time difference in miliseconds
float timeinmiliseconds(clock_t start, clock_t stop) {
  return ((float)(stop - start) / CLOCKS_PER_SEC);
}

// Extracts the problem name from argv[0]
char * domainname(char * fullname){

  char * domain = (char *) malloc(50*sizeof(char));
  sscanf(fullname,"./%[^.]:", domain);
  return domain;

}

// Expansion function of BFS
void best_first_search_expansion(state_t state, PriorityQueue<state_t> *open,
                                 state_map_t * distances,
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
      int dist = *state_map_get(distances, &state) + get_fwd_rule_cost(ruleid);
      int cost = dist + manhatan(child);

      state_map_add(histories, &child, child_history);

      const int *dist_anterior = state_map_get(distances, &child);

      if (dist_anterior == NULL || *dist_anterior < dist ) {
        state_map_add(distances, &child, dist);
        open->Add(cost, cost, child);
      }
    }
  }

}

// BFS
int best_first_seach(state_t state, long * nStates, clock_t start){

  PriorityQueue<state_t> open;
  state_map_t *distances = new_state_map();
  state_map_t *histories  = new_state_map();

  // first node
  int history = init_history;
  state_map_add(histories, &state, history);
  state_map_add(distances, &state, 0);

  int costN0 = manhatan(state);
  open.Add(costN0, costN0, state);

  while(!open.Empty()){

    state = open.Top();
    open.Pop();

    // check if goal
    if (is_goal(&state)){
      int distance = *state_map_get(distances, &state);
      destroy_state_map(distances);
      destroy_state_map(histories);
      open.Clear();
      return distance;
    }
    // check if time's up
    if (timeinmiliseconds(start, clock()) > 300.0){
      destroy_state_map(distances);
      destroy_state_map(histories);
      open.Clear();
      // Means the algorithm ran more than 5minutes
      return -2;
    };

    best_first_search_expansion(state, &open, distances, histories, nStates);
  }

  return -1;
}

int main(int argc, char **argv ) {

    state_t state;
    FILE * inputfile;
    FILE * outputfile;

    if (argc < 3) {
      printf("Missing argument.\nPlease run with ./<problemname>.astar_manhatan <inputfile> <outputfile>\n");
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

      int  h0 = manhatan(state);
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

      fprintf(outputfile,"astar, manhatan, %s, ", domainname(argv[0]));
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
