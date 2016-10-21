#include <vector>

int manhatan(state_t state, float weigth = 1){
  int h = 0;
  unsigned mtable[16][16] = {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
      {2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4},
      {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
      {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
      {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
      {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
      {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
      {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
      {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
      {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
      {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
      {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
      {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
      {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
      {6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}
  };

  for (int i = 0; i < 16; i++){
    h += mtable[state.vars[i]][i];
  }

  h = (weigth*h);
  h = static_cast<int>(h);
  return h;
}

int gap(state_t state, float weigth = 1) {

  int h = 0;
  int len_state = sizeof(state.vars)/sizeof(state.vars[0]);

  for (int i = 0; i < len_state - 1; i++) {
    if (abs(state.vars[i] - state.vars[i+1]) > 1) {
      h += 1;
    }
  }

  if (abs(state.vars[len_state-1] - len_state) > 1) {
    h += 1;
  }

  h = (weigth*h);
  h = static_cast<int>(h);
  return h;
}


int main(int argc, char **argv) {

  state_t goal;
  int d;

  // first_goal_state(&goal, &d);

  char * stado = "5 6 10 11 14 12 13 18 17 16 15 3 0 1 2 26 25 24 23 4 19 9 8 7 20 21 22 27";
  //char * stado = "2 1 4 0 5 3";
  read_state(stado, &goal);

  print_state(stdout, &goal);

  printf("manhatan: \n");
  printf("%d\n",gap(goal));
  printf("%d\n",gap(goal,1.5));
  // printf("gap: \n");
  // printf("%d\n",gap(goal));

  return 0;

}
