#include "session.h"

/**** LAB 1 - functions to program (start here) ****/
// using init_game and choose_level from session.h to restart the session
void restart_session_game(Session *session)
{
	init_game(&session->current_game);
	choose_level(&session->current_game);
}
// This function is initialisng the session by setting the best score to 'zero'
// And it also initialise the current game by using init_game function
void init_session(Session *session)
{
	for (int i=0; i <= MAX_LEVELS; i++){
		session->best_score[i] = 0; // setting best score to zero for all levels
	}
	init_game(&session->current_game);
}
// Prints the best score and the current game data
void print_session(Session *session)
{ 
	printf("Best Scores: \n");
	// using the for loop to print the best score for each lvl
	for(int i= 1; i<= MAX_LEVELS; i++){
		printf("Level %d: %d\n", i, session->best_score[i]);
	}
	printf("Current Game: \n");
	print_game(session->current_game);
}
// Ths function is assigning the current score to the best score
void new_game_score(Session *session){
	// Initialising two variables by current game score and lvl
	int score = session->current_game.score;
	int level = session->current_game.level;
	if(score < 0){
	// if the score is negative, we are setting it to zero to not have negative scores in the best score array
		score = 0; 
	}
	// If the current is higher than the best score, it'll become the best score for the current game
	if(score > session->best_score[level]){
		session->best_score[level] = score;
	}
}
/**** LAB 1 - functions to program (end here) ****/
