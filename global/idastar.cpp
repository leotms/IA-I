#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <limits.h>
#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>

int h(state_t state){
  return 1;
}

std::tuple<state_t, int> f_bounded_dfs_visit(state_t state, int bound,int dist){
  int f;
  int t=INT_MAX;

  f = dist + h(state);
  if (f > bound){return std::make_tuple(NULL,f);};
  if (is_goal(&state)){ return std::make_tuple(state,dist);};

  state_t child;
  ruleid_iterator_t iter;
  int ruleid;

  init_fwd_iter(&iter, &state);

  while((ruleid = next_ruleid(&iter)) >= 0 ) {
				apply_fwd_rule(ruleid, &state, &child);
        printf("HIJOS: ");
        print_state(stdout, &child);
        printf("\n");
        int dist2 = dist + get_fwd_rule_cost(ruleid);

        std::tuple<state_t, int> p = f_bounded_dfs_visit(child,bound,dist2)

        if (std::get<0>(p) != NULL) {return p;}
        t = min(t,std::get<1>(p));
        return (NULL,t);
			}
}

void ida_search(int (*h)(state_t)){

  char * estadostr = "3 1 4 5 B 2 6 7 8 9 10 11";
  // char * estadostr = "B 1 2 3 4 5 6 7 8 9 10 11";
  state_t state;

  int nchars = read_state(estadostr, &state);
  int bound =h(state);
  int distInicial=0;

  while (true){
    std::tuple<state_t, int> p = f_bounded_dfs_visit(state, bound,distInicial);
    if (std::get<0>(p) != NULL) {return std::get<0>(p);}
    bound = std::get<1>(p);
  }

}


int main(int argc, char **argv ) {

    state_t goal=ida_search(h);

    printf("GOAL: ");
    print_state(stdout, &goal);
    printf("\n");

    return 0;
}
