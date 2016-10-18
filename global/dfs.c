#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>

#define  MAX_LINE_LENGTH 999

float timeinmiliseconds(clock_t start, clock_t stop) {
  return ((float)(stop - start) / CLOCKS_PER_SEC);
}

long int dfs(state_t state, int history, int d, int bound, long * nEstados, clock_t start) {

  printf("N Estados %ld\n",*nEstados);
  *nEstados = *nEstados + 1;
  if (d > bound) {
    return -1;
  }
  // } else if (timeinmiliseconds(start, clock()) >= 600000.0) {
  //   // means time's up
  //   return -2;
  if (is_goal(&state)){
    *nEstados = *nEstados - 1;
    printf("Lo encontro\n");
    return 0;
  }

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  init_fwd_iter(&iter, &state);

  while((ruleid = next_ruleid(&iter)) >= 0) {
			if (fwd_rule_valid_for_history(history, ruleid) != 0){
				apply_fwd_rule(ruleid, &state, &child);
				int next_history = next_fwd_history(history, ruleid);
				long distancia = dfs(child, next_history, d + 1, bound, nEstados, start);
  		  if (distancia >= 0){
          return distancia  + 1;
        } else if (distancia == -2){
          return distancia;
        }
			}
  }

  return -1;
}

int main(int argc, char **argv ) {

  state_t state;
  long    nEstados = 0;
  FILE * inputfile;
  FILE * outfile;

  char str[MAX_LINE_LENGTH + 1];
  ssize_t nchars;
  printf("Please enter a state followed by ENTER: ");
  if( fgets(str, sizeof str, stdin) == NULL ) {
      printf("Error: empty input line.\n");
      return 0;
  }
  // CONVERT THE STRING TO A STATE
  nchars = read_state(str, &state);
  if( nchars <= 0 ) {
      printf("Error: invalid state entered.\n");
      return 0;
  }

  printf("The state you entered is: ");
  print_state(stdout, &state);
  printf("\n");

	int history = init_history;
  int bound   = 0;
  long distancia = 0;
  clock_t start = clock();
  while (true) {
    distancia = dfs(state , history, 0, bound, &nEstados, start);
    if (distancia >= 0){
      break;
    } else if (distancia == -2){
      printf("Time's up\n");
      break;
    }
    bound = bound + 1;
  }

  float totalTime = timeinmiliseconds(start,clock());

  printf("%ld\n", distancia);
  printf("Estados Generados: %ld\n",nEstados);
  printf("Tiempo Total %f\n",totalTime);
  printf("NODOS POR SEGUNDO: %f\n", nEstados/totalTime);

  return 0;
}
