#include "session.h"

/**** LAB 1 - functions to program (start here) ****/
void restart_session_game(Session *session)
{
	init_game(&session->current_game);
	choose_level(&session->current_game);
}
void init_session(Session *session)
{
	// TODO
	for (int i=0; i <= MAX_LEVELS; i++){
		session->best_score[i] = 0;
	}
	init_game(&session->current_game);
}

void print_session(Session *session)
{ 
	printf("Best Scores: \n");
	for(int i= 1; i<= MAX_LEVELS; i++){
		printf("Level %d: %d\n", i, session->best_score[i]);
	}
	printf("Current Game: \n");
	print_game(session->current_game);
}

void new_game_score(Session *session)
{
}
/**** LAB 1 - functions to program (end here) ****/
