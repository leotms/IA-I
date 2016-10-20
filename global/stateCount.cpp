#include <vector>

// Uses Iterative Deepening Depth First search
// To count the number of states in a given problem.
// Also computes the branching factor if needed.


// Calculates the total of possible states
long int findTotalPossibleStates(int longitud){
  return (longitud == 1 || longitud == 0) ? 1 : findTotalPossibleStates(longitud - 1)*longitud;
}

// Iterative Deepening DFS modification to count the number of states
// instead of finding a goal state.
long int iterative_deepening_dfs(state_t state, int history, int bound, int d) {
  if (d > bound){
    return 0;
  }

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  init_fwd_iter(&iter, &state);

  long acum = 0;
  while((ruleid = next_ruleid(&iter)) >= 0 ) {
      // we prune the search tree
			if (fwd_rule_valid_for_history(history, ruleid) != 0){
				apply_fwd_rule(ruleid, &state, &child);
				int next_history = next_fwd_history(history, ruleid);
				long aux_acum     = iterative_deepening_dfs(child, next_history, bound, d + 1);
			  acum = acum + aux_acum;
			}
  }

  return acum + 1;
}

int main(int argc, char **argv ) {

	char    str[3];
	char    *ptr;
  state_t state;
	int     bound;
  int     bf = false;

	if (argc < 2) {
		printf("Missing argument.\nPlease run ./<problemname>.stateCount <depth> ");
		printf("or ./<problemname>.stateCount <depth> <-b> if branching factor is desired.\n");
    return 0;
	} else if (argc == 3 && strcmp(argv[2], "-b") == 0) {
    bf = true;
  }

	bound = strtol(argv[1], &ptr, 10);
	if( bound < 0 ) {
		printf("Error: invalid depth entered.\n");
		return 0;
	}

  // table formatting
	printf("\nNumber of states will be calculated until depht %d\n",bound);
  if (bf) {
    printf("Branching factor will be displayed.\n");
  };
  printf("\n\n");
	printf("DEPTH\t| #STATES");
  if (bf) {
    printf("\t| BRANCHING FACTOR");
  }

  printf("\n");
	printf("--------------------------------------\n");

  //  we update this variables while we go deeper the search tree
  long  totalNodesNumber     = 0;
  float branching_factor     = 0;
  long  totalPreviousLevel   = 1;  //always cout root
  long  totalPossibleStates  = findTotalPossibleStates(sizeof(state.vars)/sizeof(state.vars[0]));
  int   minDepth       = 0;

  for(int i = 0; i<=bound; i++){
      int d;
			// every time we iterate we get set the root as the goal
			first_goal_state(&state, &d);
			d = 0;
			// we set the history = 0
			int history = init_history;
      long totalNodesUntilLevel = iterative_deepening_dfs(state , history, i, d);

      long aux = totalNodesUntilLevel;
      long statesInLevel   = totalNodesUntilLevel - totalNodesNumber;
      totalNodesNumber = aux;

      // we show branching factor:
      if (bf && i > 0) {
        minDepth = ( minDepth == 0 && statesInLevel > totalPossibleStates) ? i : 0;
        branching_factor   = (float)statesInLevel/(float)totalPreviousLevel;
        totalPreviousLevel = statesInLevel;
        printf("\t\t%f", branching_factor);
      }

      // print depht and  number of states
      printf("\n");
      printf("%d\t %ld", i, statesInLevel);

  }

	printf("\n--------------------------------------\n");
  if (bf && minDepth > 0) {
    printf("Min depth where nodes > possible states: %d\n", minDepth);
  } else if (bf){
    printf("There's no min depth were nodes > possible states until depth %d\n", bound);
  }

  return 0;
}
