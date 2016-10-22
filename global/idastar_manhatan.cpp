#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

// Uses Iterative Deepening A* with Manhatan Heuristic to
// create an algorithm that solves the
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

// tuple structure for results
struct tuple {
    int dist;
    int f;
};
// bounded Depth First Search Visit
struct tuple f_bounded_dfs_visit(state_t state, int history,
                                 int bound, int dist,
                                 long * nStates, clock_t start){

  *nStates = *nStates + 1;
  int f;
  int t = INT_MAX;
  struct tuple paux;

  f = dist + manhatan(state);


  if (is_goal(&state)){
    paux.dist = 0;
    paux.f = dist;
    return paux;
  };

  if (timeinmiliseconds(start, clock()) > 300.0){
    // more than 5 mins
    paux.dist = -2;
    paux.f = f;
    return paux;
  };

  if (f > bound){
    paux.dist = -1;
    paux.f = f;
    return paux;
  };

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  init_fwd_iter(&iter, &state);

  while((ruleid = next_ruleid(&iter)) >= 0 ) {
    if (fwd_rule_valid_for_history(history, ruleid) != 0){
      apply_fwd_rule(ruleid, &state, &child);
      int next_history = next_fwd_history(history, ruleid);

      int dist2 = dist + get_fwd_rule_cost(ruleid);

      struct tuple p = f_bounded_dfs_visit(child, next_history, bound, dist2, nStates, start);

      if (p.dist >= 0) {
        p.dist = p.dist + 1;
        return p;
      } else if (p.dist == -2){
        return p;
      }
      t = (t < p.f) ? t : p.f;
      paux.dist=-1;
      paux.f=t;
    }
  }

  return paux;
}

// IDA* Serach Algorithm Initialization
int ida_search(state_t state, int history, long * nStates, clock_t start){

  int bound  = manhatan(state);

  while (true){
    tuple p = f_bounded_dfs_visit(state, history, bound, 0, nStates, start);
    if (p.dist >= 0)  {return p.dist;}
    if (p.dist == -2) {return p.dist;}
    bound = p.f;
  }

  return -1;
}


int main(int argc, char **argv ) {

  state_t state;
  FILE * inputfile;
  FILE * outputfile;

  if (argc < 3) {
    printf("Missing argument.\nPlease run with ./<problemname>.idastar_manhatan <inputfile> <outputfile>\n");
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

    int  history   = init_history;
    int  h0 = manhatan(state);
    long distance = 0;
    long nStates = 0;

    printf("Solving state: ");
    print_state(stdout, &state);
    printf("\n");

    // Start clock
    clock_t start = clock();
    while (true) {
      distance = ida_search(state, history, &nStates, start);
      if (distance >= 0){
        break;
      } else if (distance == -2){
        break;
      }
    }

    // total time for the algorithm
    float totalTime = timeinmiliseconds(start,clock());

    fprintf(outputfile,"ida, manhatan, %s, ", domainname(argv[0]));
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
