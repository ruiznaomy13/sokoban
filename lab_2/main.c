#include "main.h"

void	run_game(Session *session)
{
	Game	*game = &session->current_game;

	do
	{
		print_session(session);

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
	choose_level(&(session->current_game));
	run_game(session);
}

void	save_game(Session *session)
{
	// Creating a new file here
	char saved_game_file[256];
	FILE *fp;
	Game *g = &session->current_game;
	printf("Enter filename to save: ");
	if(fgets(saved_game_file, sizeof(saved_game_file), stdin) == NULL){
		return;
	}
	// remove the new line 
	for(int i= 0; saved_game_file[i]!=0; i++){
		if(saved_game_file[i] == '\n'){
			saved_game_file[i] = '\0';
			break;
		}
	}
	// opening the file in write mode 
	fp = fopen(saved_game_file, "w");
	// if the file doesn't exist it shows an error message
	if(fp == NULL){
		printf("Error opening file fo writing.\n");
		return;
	}
	// The structure in which the info will be saved in the file
	fprintf(fp, "Score: %d", g->score);
	fprintf(fp, "\nLevel: %d", g->level);
	fprintf(fp, "\nState:");
	fprintf(fp, "\nrows: %d", g->state.rows);
	fprintf(fp, "\ncolumns: %d\n", g->state.columns);
	for(int i = 0; i < g->state.rows; i++){
		for(int j= 0; j < g->state.columns; j++){
			fputc(g->state.grid[i][j], fp);
			fputc('\n',fp);
		}
	}
	fclose(fp);
	printf("Game saved successfully.\n");
}
void	load_game(Session *session)
{
	// ToDo - Lab 2
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
		printf("[ANY GAME STARTED]\n");
		return ;
	}

	printf("RESUMING GAME ... \n");
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
