#include "game.h"

/**** LAB 1 - given functions ****/
void print_options()
{
	printf("Options:\n");
	printf("\t%d. Up | %d. Right | %d. Down | %d. Left |\n", MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT);
	printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
	printf("\t%d. Quit game\n", QUIT_GAME);
}

bool	is_valid_option(Option o)
{
	return ((MOVE_UP <= o) && (o <= QUIT_GAME));
}

bool	set_level(State *s, unsigned level)
{
	switch (level)
	{
		case 1:
			printf("[INFO]: loading level #%d\n", level);
			s->rows = 3;
			s->columns = 8;
			s->grid = make_grid(s->rows, s->columns + 1);
			strcpy(s->grid[0], "########");
			strcpy(s->grid[1], "#.A.B.G#");
			strcpy(s->grid[2], "########");
			break;
		case 2:
			printf("[INFO]: loading level #%d\n", level);
			s->rows = 5;
			s->columns = 8;
			s->grid = make_grid(s->rows, s->columns + 1);
			strcpy(s->grid[0], "########");
			strcpy(s->grid[1], "#....###");
			strcpy(s->grid[2], "#.B#.#A#");
			strcpy(s->grid[3], "#..B.GG#");
			strcpy(s->grid[4], "########");
			break;
		case 3:
			printf("[INFO]: loading level #%d\n", level);
			s->rows = 7;
			s->columns = 7;
			s->grid = make_grid(s->rows, s->columns + 1);
			strcpy(s->grid[0], "#######");
			strcpy(s->grid[1], "###G###");
			strcpy(s->grid[2], "###B###");
			strcpy(s->grid[3], "#GBABG#");
			strcpy(s->grid[4], "###B###");
			strcpy(s->grid[5], "###G###");
			;
			strcpy(s->grid[6], "#######");
			break;
		case 4:
			printf("[INFO]: loading level #%d\n", level);
			s->rows = 6;
			s->columns = 8;
			s->grid = make_grid(s->rows, s->columns + 1);
			strcpy(s->grid[0], "#######.");
			strcpy(s->grid[1], "#.B.AG##");
			strcpy(s->grid[2], "#.XXG..#");
			strcpy(s->grid[3], "#....B.#");
			strcpy(s->grid[4], "#..#####");
			strcpy(s->grid[5], "####....");
			break;
		default:
			printf("[ERROR]: level not found!\n");
			return false;
	};

	return true;
}

void	init_game(Game *game)
{
	game->score = 0;
	game->level = 0;
	// LAB 1
	/*
	game->state.rows = MAX_ROWS;
	game->state.columns = MAX_COLUMNS;
	for(int i=0; i<MAX_ROWS; ++i)
		for(int j=0; j<MAX_COLUMNS; ++j)
			game->state.grid[i][j] = '.';
	*/
	// LAB 2
	game->state.rows = 0;
	game->state.columns = 0;
	game->state.grid = NULL;
}

void	choose_level(Game *game)
{
	game->score = 0;

	do
	{
		printf("[INFO] Choose the level [1-4]: ");
		game->level = read_int();
	} while (!set_level(&game->state, game->level));
}

/**** LAB 1 - functions to program (start here) ****/
void print_state(State s)
{
	for(int i = 0; i < s.rows; i++)
	{
		for(int j = 0; j < s.columns; j++)
			printf("%c", s.grid[i][j]);
		printf("\n");
	}
}

void print_game(Game game)
{
	printf("Level: %d , Score: %d\n", game.level, game.score);
	print_state(game.state);
}

bool is_terminal(State s)
{
	for(int i= 0; i< s.rows; i++)
	{
		for(int j= 0; j < s.columns; j++)
		{
			if(s.grid[i][j] == BOX)
				return false;
		}
	}
	return true;
}

/*
 * @brief: Calculate the new position after a move
 *
 * @details: Given a current position and a move direction, returns the resulting position.
 *
 * @return: New position after applying the move
 */
Pos	new_position(Pos curr, Option o)
{
	Pos	p = curr;

	switch (o)
	{
		case MOVE_DOWN:
			p.y++;
			break;
		case MOVE_UP:
			p.y--;
			break;
		case MOVE_RIGHT:
			p.x++;
			break;
		case MOVE_LEFT:
			p.x--;
			break;
		default:
			break;
	}
	return (p);
}

bool    in_bounds(State s, Pos p)
{
	return (p.y >= 0 && p.y < s.rows
		&& p.x >= 0 && p.x < s.columns);
}

/*
 * @brief: Check whether a move is valid
 *
 * @details: Validates if the new player position (and box if pushed) is within bounds
 *          and does not collide with walls or other boxes.
 *
 * @return: True if the move is valid, false otherwise
 */
bool	valid_move(State s, Pos new_pos, bool box, Option o)
{
	if (!in_bounds(s, new_pos)) // check the bounds (in this case maybe is not usefull)
		return (false);

	if (s.grid[new_pos.y][new_pos.x] == WALL) // check if in new position is a wall
		return (false);

	if (box) // also check for box
	{
		Pos next_pos = new_position(new_pos, o);

		if (!in_bounds(s, next_pos))
			return (false);

		if (s.grid[next_pos.y][next_pos.x] == WALL
		 || s.grid[next_pos.y][next_pos.x] == BOX) // we cannot update if there is wall or another box
			return (false);
	}
	return (true);
}

/*
 * @brief: Determine the new value of a grid cell after a move
 *
 * @details: Updates the character of a cell based on whether the player or a box
 *          is moving into or out of it.
 *
 * @return: The new character for the cell
 */
char	change_cell(char c, bool box)
{
	switch (c)
	{
		case PLAYER:
			return EMPTY;
		case BOX:
			return PLAYER;
		case EMPTY:
			return (box ? BOX : PLAYER);
		case GOAL:
			return (box ? B_GOAL : P_GOAL);
		case P_GOAL:
			return GOAL;
		case B_GOAL:
			return P_GOAL;
		default:
			return c;
	}
}


/*
 *  @brief: Update the game grid after a move
 *
 *  @details: Checks if the movement is valid, handles box movement if needed,
 *  and updates the player's and box's positions on the grid.
 */
void	update_grid(State s, Option o, Pos pos)
{
    Pos     new = new_position(pos, o);
    bool    box = (s.grid[new.y][new.x] == BOX
                || s.grid[new.y][new.x] == B_GOAL);
    Pos     next = {0, 0};

    // Return immediately if the move is invalid
    if (!valid_move(s, new, box, o))
        return;

    if (box)
        next = new_position(new, o);

    char curr = s.grid[pos.y][pos.x];     // current player cell
    char dest = s.grid[new.y][new.x];     // destination cell for player

    if (box)
    {
        char next_cell = s.grid[next.y][next.x]; // destination cell for the box
        s.grid[next.y][next.x] = change_cell(next_cell, true);  // move the box
        s.grid[new.y][new.x] = change_cell(dest, false);        // move the player
    }
    else
    {
        s.grid[new.y][new.x] = change_cell(dest, false);        // move the player
    }

    s.grid[pos.y][pos.x] = change_cell(curr, false); // clear old player position
}

/*
 * @brief: Find the player's position in the grid
 *
 * @details: Searches the entire grid for the player. If found, saves the
 *          current position in the provided Pos pointer.
*/
bool	player_pos(State s, Pos *pos)
{
	for (int i = 0; i < s.rows; i++)
	{
		for (int j = 0; j < s.columns; j++)
		{
			if (s.grid[i][j] == PLAYER || s.grid[i][j] == P_GOAL)
			{
				pos->y = i;
				pos->x = j;
				return (true);
			}
		}
	}
	return (false);
}

/*
	@return: new State after applying a new move
*/
State	move(State s, Option o)
{
	Pos pos = {0, 0};

	if (!player_pos(s, &pos)) // check if there is a player
		return s; // in future maybe handle it

	update_grid(s, o, pos); // apply the new move to the grid
	print_state(s); // updates the map on screen

	return	s;
}

/**** LAB 1 - functions to program (end here) ****/


/**** LAB 2 - functions to program (start here) ****/
void free_state(State *s)
{
    if (!s)
		return;

    if (s->grid)
        s->grid = free_grid(s->grid);

    s->columns = 0;
    s->rows = 0;
}

void free_game(Game *g)
{
	g->level=0;
    g->score=0;
    free_state(&(g->state));
}

char	**free_grid(char **grid)
{
	/*
		free the memmory of a char**
		it nust be finished with NULL
	*/
	int	i = -1;

	if (!grid)
		return NULL;
	while (grid[++i])
		free(grid[i]);
	free(grid);
	return NULL;
}

char **make_grid(int rows, int columns)
{
	/*
		This function allows that our grid have any size
		allocates memory for each row and each colum space
		also we make sure to protect each calloc
	*/
	char	**grid = calloc(rows + 1, sizeof(char *));

	if (!grid)
		return (NULL);

	for (int i=0; i < rows; ++i)
	{
		grid[i] = calloc(columns, sizeof(char));
		
		if (!grid[i])
			return (free_grid(grid));
	}
	grid[rows] = NULL;

	return grid;
}

/**** LAB 2 - functions to program (end here) ****/
