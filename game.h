#ifndef GAME_H
# define GAME_H
# include "common.h"
# include "utils.h"

/// LAB 1 - macros
# define	MAX_ROWS 8
# define	MAX_COLUMNS 8


typedef	struct
{
	int	pos_y;
	int	pos_x;
}		Pos;


/// LAB 1 - data structures
typedef struct
{
	int		rows;
	int		columns;
	char	grid[MAX_ROWS][MAX_COLUMNS]; // '#' wall; '.' empty; 'G' goal location; 'A' agent; 'Y' agent at goal location;  'B' box;  'X' box at goal location
}			State;

typedef struct
{	
	int			score;	// Current score
	unsigned	level;	// Current level
	State		state;	// State status
}				Game;

typedef enum
{
	MOVE_UP = 1,
	MOVE_RIGHT = 2,
	MOVE_DOWN = 3,
	MOVE_LEFT = 4,
	SHOW_BEST_MOVE = 5,
	QUIT_GAME = 6
}	Option;

/// LAB 1 - given functions
void	print_options();
bool	is_valid_option(Option o);
bool	set_level(State *s, unsigned level);
void	init_game(Game *g);
void	choose_level(Game *g);

/**** LAB 1 - functions to program (start here) ****/
// AUXILIAR FUNCTIONS
void	player_pos(Pos *pos, State s); // look for the player position
void	update_grid(char (*grid)[MAX_COLUMNS], Option o, Pos pos); //change the grid to new one
Pos		new_position(Pos curr, Option o); // return the new position BOX or Pos
bool	valid_move(char (*grid)[MAX_COLUMNS], Pos new_pos, bool box, Option o); // True if the move is valid
char	change_cell(char c, bool box); //

void	print_state(State s);
void	print_game(Game g);
bool	is_terminal(State s); // True if all boxes are in goal locations, otherwise false
State	move(State b, Option o); // move/push in one of the 4 cardinal directions
/**** LAB 1 - functions to program (end here) ****/

#endif