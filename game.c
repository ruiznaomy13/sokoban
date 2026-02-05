#include "game.h"


/**** LAB 1 - given functions ****/
void	print_options()
{
	printf("Options:\n");
	printf("\t%d. Up | %d. Right | %d. Down | %d. Left |\n", MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT);
	printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
	printf("\t%d. Quit game\n", QUIT_GAME);
}

bool	is_valid_option(Option o)
{
	return ((MOVE_UP <= o) && (o<=QUIT_GAME));
}

bool	set_level(State *s, unsigned level)
{
	switch(level)
	{
		case 1:
			s->rows = 3;
			s->columns = 8;
			strcpy(s->grid[0], "########");
			strcpy(s->grid[1], "#.A.B.G#");
			strcpy(s->grid[2], "########");
			break;
		case 2:
			s->rows = 5;
			s->columns = 8;
			strcpy(s->grid[0], "########");
			strcpy(s->grid[1], "#....###");
			strcpy(s->grid[2], "#.B#.#A#");
			strcpy(s->grid[3], "#..B.GG#");
			strcpy(s->grid[4], "########");
			break;
		case 3:
			s->rows = 7;
			s->columns = 7;
			strcpy(s->grid[0], "#######");
			strcpy(s->grid[1], "###G###");
			strcpy(s->grid[2], "###B###");
			strcpy(s->grid[3], "#GBABG#");
			strcpy(s->grid[4], "###B###");
			strcpy(s->grid[5], "###G###");;
			strcpy(s->grid[6], "#######");
			break;
		case 4:
			printf("[INFO]: loading level #%d\n", level);
			s->rows = 6;
			s->columns = 8;
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
	game->state.rows = MAX_ROWS;
	game->state.columns = MAX_COLUMNS;

	for(int i=0; i<MAX_ROWS; ++i)
		for(int j=0; j<MAX_COLUMNS; ++j)
			game->state.grid[i][j] = '.';
}

void	choose_level(Game *game)
{
	game->score = 0;

	do {
		printf("[INFO] Choose the level [1-4]: ");
		game->level = read_int();
	} while(!set_level(&game->state, game->level));
}

/**** LAB 1 - functions to program (start here) ****/
// Using for loops to iterate over the whole grid and printing each point of it
void	print_state(State s)
{
	for(int i = 0; i < s.rows; i++){
		for(int j = 0; j < s.columns; j++){
			printf("%c", s.grid[i][j]);
		}
		printf("\n");
	}
}
// To print out the level, score and state of the game
void	print_game(Game game)
{
	printf("Level: %d , Score: %d\n", game.level, game.score);
	print_state(game.state);
}
// Returns true if all goal locations conatains boxes, false otherwise
bool	is_terminal(State s)
{
	for(int i= 0; i< s.rows; i++){
		for(int j= 0; j < s.columns; j++)
		{
			if(s.grid[i][j] == B_GOAL)
				return true;
		}
	}
	return true;
}

char	change_cell(char c, bool box)
{
	printf("\n\nCHANGE: \t%c -----> [?] (%d)\n\n", c, box);
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
			return PLAYER;
		default:
			return c;
	}
}

bool in_bounds(Pos p)
{
	return (p.pos_y >= 0 && p.pos_y < MAX_ROWS
		&& p.pos_x >= 0 && p.pos_x < MAX_COLUMNS);
}


bool	valid_move(char (*grid)[MAX_COLUMNS], Pos new_pos, bool box, Option o)
{
	if (!in_bounds(new_pos))
		return (0);

	if (grid[new_pos.pos_y][new_pos.pos_x] == WALL)
		return (0);

	if (box)
	{
		Pos next_pos = new_position(new_pos, o);

		if (!in_bounds(next_pos))
			return (0);

		if (grid[next_pos.pos_y][next_pos.pos_x] == WALL
		 || grid[next_pos.pos_y][next_pos.pos_x] == BOX)
			return (0);
	}
	return (1);
}

Pos	new_position(Pos curr, Option o)
{
	Pos	p = curr;

	switch (o)
	{
		case MOVE_DOWN:
			p.pos_y++;
			break;
		case MOVE_UP:
			p.pos_y--;
			break;
		case MOVE_RIGHT:
			p.pos_x++;
			break;
		case MOVE_LEFT:
			p.pos_x--;
			break;
		default:
			break;
	}
	return p;
}

void update_grid(char grid[MAX_ROWS][MAX_COLUMNS], Option o, Pos pos)
{
	Pos		new = new_position(pos, o);
	Pos		next = new_position(new, o);
	bool	box = false;
	
	if (grid[new.pos_y][new.pos_x] == BOX) box = true;
	if (!valid_move(grid, new, box, o)) return ;

	char	tmp = grid[pos.pos_y][pos.pos_x];

	grid[pos.pos_y][pos.pos_x] = change_cell(tmp, box);
	if (box)
	{
		char tmp2 = grid[new.pos_y][new.pos_x];
		grid[new.pos_y][new.pos_x] = change_cell(tmp, box);
		grid[next.pos_y][next.pos_x] = change_cell(tmp2, box);
	} else
		grid[new.pos_y][new.pos_x] = change_cell(tmp, box);
}

// void update_grid(char grid[MAX_ROWS][MAX_COLUMNS], Option o, Pos pos)
// {
// 	Pos		new = new_position(pos, o);
// 	bool	box = (grid[new.pos_y][new.pos_x] == BOX);

// 	if (!valid_move(grid, new, box, o))
// 		return ;

// 	Pos		next;
// 	if (box)
// 		next = new_position(new, o);

// 	char	curr = grid[pos.pos_y][pos.pos_x];
// 	char	dest = grid[new.pos_y][new.pos_x];

// 	if (box)
// 	{
// 		char	next_cell = grid[next.pos_y][next.pos_x];
// 		grid[next.pos_y][next.pos_x] = change_cell(next_cell, true);
// 		grid[new.pos_y][new.pos_x] = change_cell(dest, false);
// 	}
// 	else
// 		grid[new.pos_y][new.pos_x] = change_cell(dest, false);

// 	grid[pos.pos_y][pos.pos_x] = change_cell(curr, false);
// }

void	player_pos(Pos *pos, State s)
{
	for (size_t i = 0; i < s.rows; i++)
	{
		for (size_t j = 0; j < s.columns; j++)
		{
			if (s.grid[i][j] == PLAYER)
			{
				pos->pos_y = i;
				pos->pos_x = j;
			}
		}
	}
}

/*
	@return: new State after applying a new move
*/
State	move(State s, Option o)
{
	Pos	pos;

	player_pos(&pos, s);
	update_grid(s.grid, o, pos);
	return s;
}

/**** LAB 1 - functions to program (end here) ****/

