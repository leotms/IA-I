/*
This program computes the distance to goal (i.e. the cost of the least-cost path to the goal)
of every state from which the goal can be reached.
It does this by executing Dijkstra's algorithm backwards from the goal.
It prints on stdout each state and its distance (distance first, then the state) and, if a filename is
provided as a command line argument, it prints the state_map it builds to that file.

Copyright (C) 2013 by the PSVN Research Group, University of Alberta
*/

#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

int main(int argc, char **argv ) {

    char str[3];
    char *ptr;
    state_t state;
    int bound;
    int bf = false;

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
  long  numeroTotalNodos    = 0;
  float branching_factor    = 0;
  long  totalNivelAnterior  = 1;  //Siempre contamos la raiz.
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
        printf("      %f", branching_factor);
      }
      printf("\n");
  }
    return 0;
}
