#include "session.h"

/**** LAB 1 - functions to program (start here) ****/
void	restart_session_game(Session *session)
{
	// ToDo
}

void	init_session(Session *session)
{
	// TODO
	for (int i=0; i <= MAX_LEVELS; i++)
		session->best_score[i] = 0;
	init_game(&session->current_game);
}

void	print_session(Session *session)
{
	// ToDo
}

void	new_game_score(Session *session)
{
	// ToDo
}
/**** LAB 1 - functions to program (end here) ****/
