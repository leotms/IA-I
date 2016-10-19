#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

long int totalEstadosPosibles(int longitud){
  return (longitud == 1 || longitud == 0) ? 1 : totalEstadosPosibles(longitud - 1)*longitud;
}

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
		printf("Missing argument.\nPlease run ./<problemname>.iterativedfs <depth> ");
		printf("or ./<problemname>.iterativedfs <depth> <-b> if branching factor is desired.\n");
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

  // Recorremos en cada nivel.
  long  numeroTotalNodos     = 0;
  float branching_factor     = 0;
  long  totalNivelAnterior   = 1;  //Siempre contamos la raiz.
  long  EstadosPosibles      = totalEstadosPosibles(sizeof(state.vars)/sizeof(state.vars[0]));
  int   minProfundidad       = 0;

  for(int i=0; i<=bound; i++){
      int d;
			// Obtenemos el stado goal, cada vez que iteremos.
			first_goal_state(&state, &d);
			d = 0;
			// Obtenemos el stado goallong
			int history = init_history;
      long totalHastaNivel = iterative_deepening_dfs(state , history, i, d);
      //printf("Nivel anterior %d.\n",nivelanterior);
      long aux = totalHastaNivel;
      long estadosEnNivel   = totalHastaNivel - numeroTotalNodos;
      numeroTotalNodos = aux;
			//Imprimimos el numero de estados.s
      printf("%d\t %ld", i, estadosEnNivel);
      if (bf) {
        branching_factor   = (float)estadosEnNivel/(float)totalNivelAnterior;
        totalNivelAnterior = estadosEnNivel;
        minProfundidad = (estadosEnNivel > EstadosPosibles) ? i : 0;
        printf("      %f", branching_factor);
      }
      printf("\n");
  }

    if (bf) {
      printf("Profundida minima: %d\n", minProfundidad);
    }
    return 0;
}
