/*DFS**/
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

#define  MAX_LINE_LENGTH 999 

int iterative_deepening_dfs(state_t state,int bound, int d, int acum) {
	if (d>bound){
		return 0;
	}
    // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;
    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule
	
	
	//printf("%d\n", d);
	/*
	print_state(stdout, &state);
	printf("\n");
	
	if (is_goal(&state)){ 
		printf("Llegue XD\n");
		print_state(stdout, &state);
		return 1;
	}*/

	init_fwd_iter(&iter, &state);
	int acum2=0;
	while((ruleid = next_ruleid(&iter)) >= 0 ) {
        apply_fwd_rule(ruleid, &state, &child);
        int aux_acum = iterative_deepening_dfs(child,bound,d+1,acum);
        acum2=acum2+aux_acum;
        //printf("Acum: %d\n",acum );

        /*print_state(stdout, &child);
        printf("\n");
        printf("  %s (cost %d), goal=%d\n", get_fwd_rule_label(ruleid), get_fwd_rule_cost(ruleid), is_goal(&child));  	
    	*/
    }

    return acum2 +1;
}

int main(int argc, char **argv ) {
    // VARIABLES FOR INPUT
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars; 
    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

    // READ A LINE OF INPUT FROM stdin
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

    // LOOP THOUGH THE CHILDREN ONE BY ONE
    int bound=17;
    int nivelanterior=0;
    for(int i=0; i<=bound; i++){ 
	    int d=0;
	    int acum=1;
    	int goal= iterative_deepening_dfs(state,i,d,acum);
    	//printf("Nivel anterior %d.\n",nivelanterior);
    	int auxnivelanterior=goal;
    	goal=goal-nivelanterior;
    	nivelanterior=auxnivelanterior;
    	printf("Para la profundidad %d para el nivel hay %d estados.\n",i,goal);
	} 
    

    return 0;
}