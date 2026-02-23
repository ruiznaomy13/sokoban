#include "session.h"
/**** LAB 1 - functions to program (start here) ****/

// using init_game and choose_level from session.h to restart the session
void	restart_session_game(Session *session)
{
	free_session(session);
	init_game(&session->current_game);
}

// This function is initialisng the session by setting the best score to 'zero'
// And it also initialise the current game by using init_game function
void	init_session(Session *session)
{
	for (int level=0; level <= MAX_LEVELS; ++level)
		session->best_score[level] = 0;
	restart_session_game(session);
}

// Prints the best score and the current game data
void	print_session(Session *session)
{ 
	int	lvl = session->current_game.level;
	printf("Best score for level %d: %d\n", lvl, session->best_score[lvl]);
	print_game(session->current_game);
}

// Ths function is assigning the current score to the best score
void	new_game_score(Session *session)
{
	// Initialising two variables by current game score and lvl
	int	score = session->current_game.score;
	int	level = session->current_game.level;
	if(score <= 0)
		return ; // not solved yet
	// If the best score is either zero or greater than the current score assign current score to best score
	if (session->best_score[level] == 0 || session->best_score[level] > score)
		session->best_score[level] = score;
}

/**** LAB 1 - functions to program (end here) ****/

// LAB 2 - functions
void	free_session(Session *s)
{
	/*
		checks if there is a session, if not returrns and don't do nothing
		otherwise free the game memmory
	*/
	if (!s)
		return ;
	
	free_game(&s->current_game);
}
