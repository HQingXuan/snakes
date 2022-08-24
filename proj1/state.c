#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake_utils.h"
#include "state.h"

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int x, unsigned int y, char ch);
static bool is_tail(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static unsigned int get_next_x(unsigned int cur_x, char c);
static unsigned int get_next_y(unsigned int cur_y, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);


/* helper function in case of allocation failure. */
static void fail_allocate() {
  fprintf(stderr, "Out of memory.\n");
  exit(1);
}

/* Task 1 */
game_state_t* create_default_state() {
  // TODO: Implement this function.
  game_state_t *gs; /* create game_state_t pointer */
  gs = malloc(sizeof(game_state_t)); /* allocate space for game_state_t struct. */

  if (gs == NULL) {
    fail_allocate();
  }

  gs->num_rows = 18; /* set number of rows.*/
  gs->num_snakes = 1; /* set number of snakes. */
  gs->snakes = calloc((gs->num_snakes), sizeof(snake_t)); /* allocate space for snake struct. */
  
  /* if no snake struct, free game board and return error. */
  if (gs->snakes == NULL) {
    free(gs);
    fail_allocate();
  }

  /* allocate space for the board (pointer of pointers)*/
  gs->board = (char **) calloc((gs->num_rows), sizeof(char *));
  if (gs->board == NULL) {
    free(gs);
    fail_allocate();
  }
  
  /* allocate space for the board (pointer of array) */
  unsigned int i, num_cols = 20; 
  for (i = 0; i < gs->num_rows; i++) {
    gs->board[i] = (char *) calloc(num_cols + 1, sizeof(char));
    if (gs->board[i] == NULL) {
      free(gs->board);
      free(gs);
    }
  }

  /* set '#' at the first row of the game board and the second row of the game board. */
  for (i = 0; i < num_cols; i++) {
    set_board_at(gs, i, 0, '#');
    if (i == 0 || i == num_cols - 1) {
      set_board_at(gs, i, 1, '#');
    } else {
      set_board_at(gs, i, 1, ' ');
    }
  }
  set_board_at(gs, num_cols, 0, '\0');
  set_board_at(gs, num_cols, 1, '\0');
  /* set the rest of the game board using strcpy. */
  for (i = 0; i < gs->num_rows; i++) {
    if (i == gs->num_rows - 1) {
      strcpy(gs->board[i], gs->board[0]);
    } else {
      strcpy(gs->board[i], gs->board[1]);
    }
  }

  /* set snake and the fruit. */ 
  set_board_at(gs, 2, 9, '*');
  gs->snakes[0].tail_x = 2;
  gs->snakes[0].tail_y = 2;
  gs->snakes[0].head_x = 4;
  gs->snakes[0].head_y = 2;
  set_board_at(gs, gs->snakes[0].tail_x, gs->snakes[0].tail_y, 'd');
  set_board_at(gs, gs->snakes[0].head_x, gs->snakes[0].head_y, 'D');
  set_board_at(gs, gs->snakes[0].head_x - 1, gs->snakes[0].head_y, '>');
  return gs;
}


/* Task 2 */
void free_state(game_state_t* state) {
  // TODO: Implement this function.
  free(gs->snakes);

  return;
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.
  unsigned int i;
  for (i = 0; i < gs->num_cols; i++) {
    fprintf(fp, gs->board[i]);
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}


/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t* state, unsigned int x, unsigned int y) {
  return state->board[y][x];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t* state, unsigned int x, unsigned int y, char ch) {
  state->board[y][x] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  return true;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASD"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  return true;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<>v"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  return true;
}

/*
  Converts a character in the snake's body ("^<>v")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<>v").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  return '?';
}

/*
  Returns cur_x + 1 if c is '>' or 'd' or 'D'.
  Returns cur_x - 1 if c is '<' or 'a' or 'A'.
  Returns cur_x otherwise.
*/
static unsigned int get_next_x(unsigned int cur_x, char c) {
  // TODO: Implement this function.
  return cur_x;
}

/*
  Returns cur_y + 1 if c is '^' or 'w' or 'W'.
  Returns cur_y - 1 if c is 'v' or 's' or 'S'.
  Returns cur_y otherwise.
*/
static unsigned int get_next_y(unsigned int cur_y, char c) {
  // TODO: Implement this function.
  return cur_y;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  return '?';
}


/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the x and y coordinates of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  return;
}


/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^v<>) into a tail character (wasd)

  ...in the snake struct: update the x and y coordinates of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  return;
}


/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
  return;
}


/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
  return NULL;
}


/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail coordinates filled in,
  trace through the board to find the head coordinates, and
  fill in the head coordinates in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  return;
}


/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  return NULL;
}
