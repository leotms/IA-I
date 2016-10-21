#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <limits.h>

#define GRAY  0
#define BLACK 1

int h(state_t state){
  return 1;
};

struct tuple {
    state_t *state;
    int f;
};

struct tuple f_bounded_dfs_visit(state_t state, int bound,int dist,state_map_t *colores){
  int f;
  int t=INT_MAX;
  struct tuple paux;

  printf("PADRE: ");
  print_state(stdout, &state);
  printf("\n");

  state_map_add(colores, &state, GRAY);

  f = dist + h(state);
  printf("%d",bound);
  printf("\n");
  printf("%d",f);
  printf("\n");
  if (f > bound){
    printf("bound");
    printf("\n");
    paux.state=NULL;
    paux.f=f;
    return paux;
  };

  if (is_goal(&state)){ 
    printf("goal");
    printf("\n");
    paux.state=&state;
    paux.f=dist;
    return paux;
  };

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  init_fwd_iter(&iter, &state);

  while((ruleid = next_ruleid(&iter)) >= 0 ) {
				apply_fwd_rule(ruleid, &state, &child);
        printf("HIJOS: ");
        print_state(stdout, &child);
        printf("\n");

        if (state_map_get(colores, &child) != NULL) {
          continue;
        }
        int dist2 = dist + get_fwd_rule_cost(ruleid);

        struct tuple p = f_bounded_dfs_visit(child,bound,dist2,colores);

        if (p.state != NULL) {return p;}
        t = (t>p.f)? t :p.f;
        paux.state=NULL;
        paux.f=t;
        return paux;
			}
}

state_t ida_search(int (*h)(state_t)){

  char * estadostr = "7 1 2 3 4 5 6 b 8 9 10 11";
  // char * estadostr = "B 1 2 3 4 5 6 7 8 9 10 11";
  state_t state;

  state_map_t *colores = new_state_map();

  int nchars = read_state(estadostr, &state);
  int bound =h(state);
  int distInicial=0;

  while (true){
    tuple p = f_bounded_dfs_visit(state, bound,distInicial,colores);
    if (p.state != NULL) {return *p.state;}
    bound = p.f;
  }

}


int main(int argc, char **argv ) {

    state_t goal=ida_search(h);

    printf("GOAL: ");
    print_state(stdout, &goal);
    printf("\n");

    return 0;
}
