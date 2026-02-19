#include "main.h"

void	run_game(Session *session)
{
	Game	*game = &session->current_game;

	do
	{
		print_session(session);
		print_state(session->current_game.state);

		Option game_option;

		do
		{
			print_options();
			printf("[INFO] Enter a game option [%d-%d]: ", MOVE_UP, QUIT_GAME);
			game_option = read_int();
		} while (!is_valid_option(game_option));

		switch (game_option)
		{
			case MOVE_UP:
			case MOVE_RIGHT:
			case MOVE_DOWN:
			case MOVE_LEFT:
				game->state = move(game->state, game_option);
				game->score++;
				break;
			case SHOW_BEST_MOVE:
			// ToDo in Lab 3
			break;
			case QUIT_GAME:
			printf("[INFO] QUIT GAME!\n");
			return;
		}

	} while (!is_terminal(game->state));

	new_game_score(session);
	print_session(session);
	printf("[INFO] LEVEL COMPLETED!!!\n");
}

void	new_game(Session *session)
{
	restart_session_game(session);
	run_game(session);
}

void	save_game(Session *session)
{
	// Creating a new file here
	char saved_game_file[256];
	FILE *fp;
	Game *g = &session->current_game;
	printf("Enter filename to save: ");
	int	c;

	while ((c = getchar() != '\n') && c != EOF) { }
	
	if(fgets(saved_game_file, sizeof(saved_game_file), stdin) == NULL)
		return ;	
	// remove the new line 
	for(int i= 0; saved_game_file[i]!=0; i++)
	{
		if(saved_game_file[i] == '\n')
		{
			saved_game_file[i] = '\0';
			break;
		}
	}
	// opening the file in write mode 
	fp = fopen(saved_game_file, "w");
	// if the file doesn't exist it shows an error message
	if(fp == NULL)
	{
		printf("Error opening file fo writing.\n");
		return;
	}
	// The structure in which the info will be saved in the file
	fprintf(fp, "Score: %d", g->score);
	fprintf(fp, "\nLevel: %d", g->level);
	fprintf(fp, "\nState:");
	fprintf(fp, "\nrows: %d", g->state.rows);
	fprintf(fp, "\ncolumns: %d\n", g->state.columns);
	for(int i = 0; i < g->state.rows; i++)
	{
		for(int j= 0; j < g->state.columns; j++)
			fputc(g->state.grid[i][j], fp);
		fputc('\n',fp);
	}
	fclose(fp);
	printf("Game saved successfully.\n");
}

void	load_game(Session *session)
{
	char	filename[256];
	FILE	*file;
    //Initialising new variables to store data
    int		score, level, rows, columns;
	Game	*g = &session->current_game;
	int		c;

	printf("Enter filename to load: ");
	// Flushing the input buffer to avoid reading leftover newline characters (important for fgets to work correctly)
	while ((c = getchar() != '\n') && (c != EOF)) { }
	
	if(fgets(filename,  sizeof(filename), stdin) == NULL)
		return;

	for (int i = 0; filename[i]!= '\0'; i++)
	{
		if(filename[i] == '\n')
		{
			filename[i] = '\0';
			break;
		}
	}
	
	file = fopen(filename, "r");
	// if the file doesn't exist it shows an error message
	if(file == NULL)
	{
		printf("Error opening file fo writing.\n");
		return;
	}
	// free previous game
	free_session(session);

    fscanf(file, "Score: %d\n", &score);
    fscanf(file, "Level: %d\n", &level);
	fscanf(file, "State:\n");
    fscanf(file, "rows: %d\n", &rows);
    fscanf(file, "columns: %d\n", &columns);

    //Retreave the values of the game.
    g->score=score;
    g->level=level;
    g->state.rows=rows;
    g->state.columns=columns;
	
	// Allocate grid dynamically
	g->state.grid =make_grid(rows, columns);

    //Read grid
    for(int i=0; i<rows;++i)
	{
        for(int j=0; j<columns; ++j)
            fscanf(file, "%c", &g->state.grid[i][j]);
		fscanf(file, "\n"); // new line after each row
    }

	fclose(file);
	printf("Game loaded successfully.\n");
}

void	resume_game(Session *session)
{
	/*
		resume the game that has been initialized
		check if there is a current game
		an then the run the game
	*/
	if (session->current_game.state.grid == NULL)
	{
		printf("\t[ANY GAME STARTED]\n");
		return ;
	}

	printf("\tRESUMING GAME ... \n");
	run_game(session);
}

void	 print_menu()
{
	printf("[INFO] Menu options:\n");
	printf("\t1. New game.\n");	 // LAB1 - basic lab for creating grid and moves
	printf("\t2. Save game.\n");	 // LAB2 - Writing file
	printf("\t3. Load game.\n");	 // LAB2 - Reading file
	printf("\t4. Resume game.\n"); // LAB2 - Continue game after reading file
	printf("\t5. Exit.\n");		 // Free all reserved memory!
}

void	run(Session *session)
{
	int	option;

	do
	{
		print_menu();
		do
		{
			printf("[INFO] Enter an integer [%d-%d]: ", NEW_GAME, EXIT);
			option = read_int();
		} while (option < NEW_GAME || option > EXIT);

		switch (option)
		{
			case NEW_GAME:
				new_game(session);
				break;
			case SAVE_GAME:
				save_game(session);
				break;
			case LOAD_GAME:
				load_game(session);
				break;
			case RESUME_GAME:
				resume_game(session);
				break;
			case EXIT:
				break;
		}
	} while (option != EXIT);

	// Lab 2
	free_session(session);
}

int	main()
{
	Session	session;

	init_session(&session);
	run(&session);
}
