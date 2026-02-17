#include "game.h"

/**** LAB 1 - given functions ****/
void print_options()
{
	printf("Options:\n");
	printf("\t%d. Up | %d. Right | %d. Down | %d. Left |\n", MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT);
	printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
	printf("\t%d. Quit game\n", QUIT_GAME);
}

bool is_valid_option(Option o)
{
	return ((MOVE_UP <= o) && (o <= QUIT_GAME));
}

bool set_level(State *s, unsigned level)
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

void choose_level(Game *game)
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
	for(int i = 0; i < s.rows; i++){
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
	for(int i= 0; i< s.rows; i++){
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

/*
 *  @brief: Update the game grid after a move
 *
 *  @details: Checks if the movement is valid, handles box movement if needed,
 *  and updates the player's and box's positions on the grid.
 */
void update_grid(char grid[][MAX_COLUMNS], Option o, Pos pos)
{
    Pos     new = new_position(pos, o);
    bool    box = (grid[new.y][new.x] == BOX
                || grid[new.y][new.x] == B_GOAL);
    Pos next = {0, 0};

    // Return immediately if the move is invalid
    if (!valid_move(grid, new, box, o))
        return;

    if (box)
        next = new_position(new, o);

    char curr = grid[pos.y][pos.x]; // current player cell
    char dest = grid[new.y][new.x]; // destination cell for player

    if (box)
    {
        char next_cell = grid[next.y][next.x]; // destination cell for the box
        grid[next.y][next.x] = change_cell(next_cell, true); // move the box
        grid[new.y][new.x] = change_cell(dest, false);       // move the player
    }
    else
    {
        grid[new.y][new.x] = change_cell(dest, false); // move the player
    }

    grid[pos.y][pos.x] = change_cell(curr, false); // clear old player position
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
	update_grid(s.grid, o, pos); // apply the new move to the grid
	print_state(s); // updates the map on screen
	return	s;
}

/**** LAB 1 - functions to program (end here) ****/


/**** LAB 2 - functions to program (start here) ****/
void free_state(State *s)
{
	// ToDo - Lab 2
}

void free_game(Game *g)
{
	// ToDo - Lab 2
}

// free **char
char	**free_grid(char **grid)
{
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
	// ToDo - Lab 2
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
