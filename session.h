#ifndef SESSION_H
# define SESSION_H
# include "game.h"

#define	MAX_LEVELS 4

/// LAB 1 - data structure
typedef	struct s_session
{
	int		best_score[MAX_LEVELS+1];
	Game	current_game; // LAB 1
}			Session;

/// LAB 1 - functions 
void	restart_session_game(Session *s);
void	init_session(Session *s);
void	print_session(Session *s);
void	new_game_score(Session *s);

#endif