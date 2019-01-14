#include "log.h"
#include "pick_letter.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*****************************************************************
IMPLEMENTATION DECLARATIONS
 *****************************************************************/

//FUNCTION DECLARATIONS
int make_new_line(uint8_t result, char * file_line, char * new_line);

//Macros
#define RIGHT 1
#define WRONG 0


/*****************************************************************
INTERFACE
 *****************************************************************/

int log_result(int result, char letter, char answer)
{
    // Copy log file to "temp" file, when correct
    // letter is reached replace that line with
    // an updated log line including the last turn's
    // info.  Then proceed to the end copying each line
    FILE *fp_original;
    FILE *fp_copy;
    
    char file_line[MAX_FILE_LINE];
    char new_line[MAX_FILE_LINE];

    fp_original = fopen(LOG_FILE, "r");
    fp_copy = fopen("temp", "w");

    while(fgets(file_line, MAX_FILE_LINE, fp_original) != NULL)
    {
	if(file_line[0] == letter) {
	    if(result) {
		make_new_line(RIGHT, file_line, new_line);
	    }
	    else {
		make_new_line(WRONG, file_line, new_line);
	    }
	    strcpy(file_line, new_line);
	}
	
	fprintf(fp_copy, "%s", file_line);
    }

    fclose(fp_original);
    fclose(fp_copy);

    // Delete $LOG_FILE and, rename "temp" to $LOG_FILE
    remove(LOG_FILE);
    rename("temp", LOG_FILE);

    return 0;
}

/*****************************************************************
IMPLEMENTATION
 *****************************************************************/
int make_new_line(uint8_t result, char * file_line, char * new_line)
{
    // Replace passed file line with a modified version
    // reflecting result of the last turn

    int last_ten[10];
    int total;
    int diff;
    char letter;

    read_log_line(file_line, last_ten, &total, &diff, &letter);

    for(int count = 0; count < 9; count++){
	last_ten[count] = last_ten[count + 1];
    }

    if(result == RIGHT) last_ten[9] = 1;
    else{
	last_ten[9] = -1;
    }

    total += 1;
    diff += last_ten[9];

    sprintf(new_line, LOG_FORMAT,
	    letter, total, diff,
	    last_ten[0], last_ten[1],
	    last_ten[2], last_ten[3],
	    last_ten[4], last_ten[5],
	    last_ten[6], last_ten[7],
	    last_ten[8], last_ten[9]
	   );
	    

    return 0;
}

int read_log_line(char *file_line, int *last_ten,
		  int *total, int *diff, char *letter)
{
    sscanf(file_line, LOG_FORMAT,
	   letter, total, diff,
	   &last_ten[0], &last_ten[1],
	   &last_ten[2], &last_ten[3],
	   &last_ten[4], &last_ten[5],
	   &last_ten[6], &last_ten[7],
	   &last_ten[8], &last_ten[9]
	);


    return 0;
}

int generate_report()
{
    float report_weights[26];
    int sorted_weights[26][2];
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    
    calc_weights(LOG_FILE, report_weights);

    for(int count = 0; count < 26; count++)
    {
	sorted_weights[count][0] = (int)alphabet[count];
	sorted_weights[count][1] = (int)report_weights[count];
    }

    int sort_done = 0;
    while(!sort_done)
    {
	int temp_letter;
	int temp_weight;
	for(int count = 0; count < 25; count++)
	{
	    sort_done = 1;
	    if(sorted_weights[count][1] < sorted_weights[count+1][1])
	    {
		temp_weight = sorted_weights[count+1][1]; 
		temp_letter = sorted_weights[count+1][0];

		sorted_weights[count+1][1] = sorted_weights[count][1];
		sorted_weights[count+1][0] = sorted_weights[count][0];

		sorted_weights[count][1] = temp_weight;
		sorted_weights[count][0] = temp_letter;

		sort_done = 0;
		break;
	    }
	}
    }
    printf("\n\n******************************************************************\n");
    printf("*SORTED PERFORMANCE DIFFERENTIAL FOR LAST 10 TURNS OF EACH LETTER*\n");
    printf("******************************************************************\n\n");   

    for(int count = 0; count < 26; count++)
    {
        printf("%c:\t%d\n", (char)sorted_weights[count][0], (int)sorted_weights[count][1]);
    }

    printf("\n\n*****************************************************************\n");
    printf("*END OF REPORT                                                  *\n");
    printf("*****************************************************************\n\n");   

    return 0;
}
