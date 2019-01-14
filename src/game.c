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
LOCAL FUNCTION DECLARATIONS
******************************************/
int handle_arguments(int argc, char *argv[]);

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
int main(int argc, char *argv[])
{
    //handle command line arguments
    if(argc > 1){
	handle_arguments(argc, argv);
	return 0;
    }
    
//    assign_weights(weights);
    calc_weights(LOG_FILE, weights);
    transform_weights(weights);
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
	sprintf(system_command, "sudo mpg123 -q %s%c%s",
		AUDIO_PATH_LETTERS, letter, AUDIO_SUFFIX);
#ifdef ENABLE_MEDIA
	system(system_command);
#endif
	// Play assocated audio clip for Letterland character
	sprintf(system_command, "sudo mpg123 -q %s%c_char%s",
		AUDIO_PATH_CHARS, letter, AUDIO_SUFFIX);	
#ifdef ENABLE_MEDIA
	system(system_command);
#endif
	// Evaluate the letter choice

	// If correct
        if((char)getch() == letter)
	{
	    // Display "correct" screen sequence
	    correct_screen_sequence();

	    // Play "correct" audio file
            sprintf(system_command, "sudo mpg123 -q %s%s",
		    AUDIO_PATH_RESULT, "correct.mp3");
#ifdef ENABLE_MEDIA
	    system(system_command);
#endif
	    // Log the result as correct
	    log_result(CORRECT, letter, answer);

	// If incorrect
	}
	else
	{
	    // Display "incorrect" screen sequence
	    incorrect_screen_sequence();

	    // Play "incorrect" audio file
	    sprintf(system_command, "sudo mpg123 -q %s%s",
		    AUDIO_PATH_RESULT, "incorrect.mp3");
#ifdef ENABLE_MEDIA
	    system(system_command);
#endif
	    // Log result as incorrect
	    log_result(INCORRECT, letter, answer);
	}

	// Increment the turn
	turn_counter++;
    }

    return 0;
}

int handle_arguments(int argc, char *argv[])
{
    if (argc > 2)
    {
	printf("\n\n***Too many command line arguments ... aborting\n\n");
	return 1;
    }

    if (!strcmp(argv[1], "-report")){
        generate_report();
	return 0;
    } 
    else{
	printf("\n\n***Argument was not understood ... aborting***\n\n");
	return 1;
    }

    return 0;
}
