#include <vector>

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


int main(int argc, char **argv) {

  state_t goal;
  int d;

  // first_goal_state(&goal, &d);

  char * stado = "1 B 3 4 6 2 11 10 5 8 7 9 14 12 15 13";
  //char * stado = "2 1 4 0 5 3";
  read_state(stado, &goal);

  print_state(stdout, &goal);

  printf("manhatan: \n");
  printf("%d\n",manhatan(goal));

  // printf("gap: \n");
  // printf("%d\n",gap(goal));

  return 0;

}
