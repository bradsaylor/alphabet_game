#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "pick_letter.h"
#include "evaluate.h"
#include "log.h"
#include "graphics.h"
#include "audio.h"
#include "getch.h"

/******************************************
LOCAL MACROS
******************************************/
#define NUM_TURNS           10
#define CORRECT             1
#define INCORRECT           0

/******************************************
LOCAL VARIABLES
******************************************/
int  turn_counter        = 0;
char result              = 0;
char letter              = ' ';
char answer              = ' ';
char system_command[50]  = "\0";
float weights[26];
float selection_space[26];


/******************************************
MAIN()
******************************************/
int main()
{
//    assign_weights(weights);
    calc_weights(LOG_FILE, weights);
    build_selection_space(weights, selection_space);

    // Resize bash window
    system("resize -s 16 57");

    //seed rand()
    time_t t;
    srand((unsigned) time(&t));    

    // Print welcome screen
    welcome_screen_sequence();

    ///////////////////
    //// GAME LOOP ////
    ///////////////////
    while(turn_counter < NUM_TURNS)
    {
	// Pick a letter
	//letter = pick_letter();
	letter = choose_a_letter(selection_space);

	// Prompt for letter
        printf("Press the %c key: ", toupper(letter));
	fflush(stdout);

	// Play associated audio clip for letter
	sprintf(system_command, "mpg123 -q %s%c%s",
		AUDIO_PATH_LETTERS, letter, AUDIO_SUFFIX);
	system(system_command);

	// Play assocated audio clip for Letterland character
	sprintf(system_command, "mpg123 -q %s%c_char%s",
		AUDIO_PATH_CHARS, letter, AUDIO_SUFFIX);	
	system(system_command);

	// Evaluate the letter choice

	// If correct
        if((char)getch() == letter)
	{
	    // Display "correct" screen sequence
	    correct_screen_sequence();

	    // Play "correct" audio file
            sprintf(system_command, "mpg123 -q %s%s",
		    AUDIO_PATH_RESULT, "correct.mp3");
	    system(system_command);

	    // Log the result as correct
	    log_result(CORRECT, letter, answer);

	// If incorrect
	}
	else
	{
	    // Display "incorrect" screen sequence
	    incorrect_screen_sequence();

	    // Play "incorrect" audio file
	    sprintf(system_command, "mpg123 -q %s%s",
		    AUDIO_PATH_RESULT, "incorrect.mp3");
	    system(system_command);

	    // Log result as incorrect
	    log_result(INCORRECT, letter, answer);
	}

	// Increment the turn
	turn_counter++;
    }

    return 0;
}

