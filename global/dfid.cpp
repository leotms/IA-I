#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>

// calculates time difference in miliseconds
float timeinmiliseconds(clock_t start, clock_t stop) {
  return ((float)(stop - start) / CLOCKS_PER_SEC);
}

char * domainname(char * fullname){

  char * domain = (char *) malloc(50*sizeof(char));
  sscanf(fullname,"./%[^.]:", domain);
  return domain;

}


// searches for goal using deeping iterative first search
long int dfs(state_t state, int history, int d, int bound, long * nStates, clock_t start) {

  *nStates = *nStates + 1;
  if (d > bound) {
    return -1;
  }
  if (timeinmiliseconds(start, clock()) > 300.0){
    //more than 5 minutes
    return -2;
  }
  if (is_goal(&state)){
    return 0;
  }

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  init_fwd_iter(&iter, &state);

  while((ruleid = next_ruleid(&iter)) >= 0) {
      // we prune the search tree
			if (fwd_rule_valid_for_history(history, ruleid) != 0){
				apply_fwd_rule(ruleid, &state, &child);
				int next_history = next_fwd_history(history, ruleid);
				long distance = dfs(child, next_history, d + 1, bound, nStates, start);
  		  if (distance >= 0){
          return distance + 1;
        } else if (distance == -2){
          return -2;
        }
			}
  }

  return -1;
}

int main(int argc, char **argv ) {

  state_t state;
  FILE * inputfile;
  FILE * outputfile;

  if (argc < 3) {
    printf("Missing argument.\nPlease run with ./<problemname>.dfid <inputfile> <outputfile>\n");
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

    int history   = init_history;
    int bound     = 0;
    long distance = 0;
    long nStates = 0;

    // Start clock
    clock_t start = clock();
    while (true) {
      distance = dfs(state , history, 0, bound, &nStates, start);
      if (distance >= 0){
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
    printf(".");
  }

  printf("\nResults stored in %s\n",argv[2]);
  return 0;

}
