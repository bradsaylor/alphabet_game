#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "getch.h"
#include "log.h"   //for LOG_FORMAT and MAX_FILE_LINE macros

char pick_letter()
{
   time_t t;
   
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
   
    /* Intializes random number generator */
    srand((unsigned) time(&t));

    return(alphabet[rand() % 26]);
}

char receive_input(char letter)
{
    char answer = ' ';
    
    answer = (char)getch();

    return answer;
}

int assign_weights(int weights[26])
{
    char file_line[MAX_FILE_LINE];
    int last_ten[10];
    int total;
    int diff;
    char letter;
    int count = 0;

    FILE *fp;
    fp = fopen("result_log", "r");

    while(fgets(file_line, MAX_FILE_LINE, fp) != NULL)
    {
	read_log_line(file_line, last_ten, &total, &diff, &letter);
	weights[count] = 0;
	for(int i = 0; i < 10; i++) weights[count] += last_ten[i];
    }

    return 0;
}
