#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

long int iterative_deepening_dfs(state_t state, int history, int bound, int d, int acum) {
  if (d>bound){
    return 0;
  }

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  init_fwd_iter(&iter, &state);
  long acum2 = 0;
  while((ruleid = next_ruleid(&iter)) >= 0 ) {
			if (fwd_rule_valid_for_history(history, ruleid) != 0){
				apply_fwd_rule(ruleid, &state, &child);
				int next_history = next_fwd_history(history, ruleid);
				long aux_acum     = iterative_deepening_dfs(child, next_history, bound, d+1, acum);
				acum2 = acum2 + aux_acum;
			}
  }

  return acum2 +1;
}

int main(int argc, char **argv ) {

	char str[3];
	char *ptr;
  state_t state;
	int bound;

	printf("Please enter the depth to calculate the number of states followed by ENTER: ");
	if( fgets(str, sizeof str, stdin) == NULL) {
			printf("Error: please enter the depth.\n");
			return 0;
	}

	bound = strtol(str, &ptr, 10);
	if( bound < 0 ) {
			printf("Error: invalid depth entered.\n");
			return 0;
	}

	printf("\nNumber of states will be calculated until depht %d\n\n",bound);

	printf("DEPTH\t|\t #STATES \n");
	printf("--------------------------------------\n");

  // Recorremos en cada nivel.
  long nivelanterior = 0;
  for(int i=0; i<=bound; i++){
      int d;
      int acum = 1;
			// Obtenemos el stado goal, cada vez que iteremos.
			first_goal_state(&state, &d);
			d = 0;
			// Obtenemos el stado goallong
			int history = init_history;
      long goal= iterative_deepening_dfs(state , history, i, d, acum);
      //printf("Nivel anterior %d.\n",nivelanterior);
      long auxnivelanterior = goal;
      goal = goal-nivelanterior;
      nivelanterior = auxnivelanterior;
			//Imprimimos el numero de estados.
      printf("%d\t|\t%ld\n", i, goal);
  }
    return 0;
}
