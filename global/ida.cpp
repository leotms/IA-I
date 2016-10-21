#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <algorithm>

//*Heuristicas*//
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

// calculates time difference in miliseconds
float timeinmiliseconds(clock_t start, clock_t stop) {
  return ((float)(stop - start) / CLOCKS_PER_SEC);
}

char * domainname(char * fullname){
  printf("%s\n",fullname);

  char * domain = (char *) malloc(50*sizeof(char));
  sscanf(fullname,"./%[^.]:", domain);
  return domain;

}

typedef struct {
    int primero; // or char strVal[20];
    int segundo;
} tupla;

// searches for goal using deeping iterative first search
tupla dfs(state_t state, int history, int d, int bound, long * nStates, clock_t start, int g) {

  int f = g + manhatan(state);

  // printf("%f\n",timeinmiliseconds(start, clock()));
  *nStates = *nStates + 1;
  if (g > bound) {
    tupla p;
    p.primero = false;
    p.segundo = f;
    return p;
  }
  if (timeinmiliseconds(start, clock()) > 20.0){
    tupla p;
    p.primero = false;
    p.segundo = -1;
    return p;
  }
  if (is_goal(&state)){
    tupla p;
    p.primero = true;
    p.segundo = g;
    return p;
  }

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  init_fwd_iter(&iter, &state);

  int t = INT_MAX;

  while((ruleid = next_ruleid(&iter)) >= 0) {
			if (fwd_rule_valid_for_history(history, ruleid) != 0){
				apply_fwd_rule(ruleid, &state, &child);
				int next_history = next_fwd_history(history, ruleid);
				tupla p = dfs(child, next_history, d + 1, bound, nStates, start);
  		  if (p.primero){
          return p;
        } else if (p.segundo < 0){
          return p;
        }
          t = min(t, p.segundo);
			}
  }

  tuple ans;
  ans.primero = false;
  ans.second  = t;
  return ans;
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

  fprintf(outputfile,"algorithm, domain, instance, cost, generated, time, gen_per_sec\n");

  while ((read = getline(&line, &len, inputfile)) != -1) {
    int nchars = read_state(line, &state);
    if( nchars <= 0 ) {
        printf("Error: invalid state in file.\n");
        continue;
    }

    int  history   = init_history;
    int  bound     = manhatan(state);
    int  g = 0;
    int  d = 0;
    tupla res;
    long nStates = 0;

    // Start clock
    clock_t start = clock();
    while (true) {
      res = dfs(state , history, 0, bound, &nStates, start, g);
      if (res.primero){
        break;
      } else if (distance == -2){
        break;
      }
      bound = bound + 1;
    }

    // total time for the algorithm
    float totalTime = timeinmiliseconds(start,clock());

    fprintf(outputfile,"dfid, %s, ", domainname(argv[0]));
    print_state(outputfile, &state);
    if (distance >= 0){
      fprintf(outputfile,", %ld, %ld, %f, %f\n", distance, nStates, totalTime, nStates/totalTime);
    } else {
      fprintf(outputfile,", na, na, na, na\n");
    }
  }

  return 0;

}
