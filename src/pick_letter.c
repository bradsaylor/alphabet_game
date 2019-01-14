#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "pick_letter.h"
#include "log.h"

//Weighting scheme parameter macros
#define N 0.3
#define M 0.5

char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

/******************************************
HELPER FUNCTIONS
 ******************************************/

int calc_weights(char *file_name, float *letter_weights)
{
    FILE *fp;
    fp = fopen(file_name, "r");
    
    int results[10];
    int sum_results;
    char file_line[100];
    char letter;
    int total;
    int diff;
    int count = 0;

    //skip header content
    fgets(file_line, 100, fp);
    fgets(file_line, 100, fp);    
	
    while(fgets(file_line, 100, fp))
    {
	sum_results = 0;
	sscanf(file_line, LOG_FORMAT,
	       &letter, &total, &diff,
	       &results[0], &results[1], &results[2], &results[3],
	       &results[4], &results[5], &results[6], &results[7],
	       &results[8], &results[9]);

	for(int i = 0; i < 10; i++)
	{
//	    printf("%d\n", results[i]);
	    sum_results += results[i];
	}
	letter_weights[count] = (float)sum_results;
//	printf("%c: %.2f\n", letter, letter_weights[count]);
	count++;
    }

    return 0;
}

int transform_weights(float *letter_weights)
{

        for(int i = 0; i < 26; i++)
    {
	letter_weights[i] -= 11;
	letter_weights[i] *= -1;
	letter_weights[i] *= N;
	letter_weights[i] += M;
	letter_weights[i] *= 10;
//	printf("%c:\t%.1f\n",  alphabet[i], letter_weights[i]);
    }

    return 0;
}

int build_selection_space(float *letter_weights, float *selection_space)
{

    //build selection space array from letter weights
    selection_space[0] = letter_weights[0];
//    printf("%c:\t%.1f\n", alphabet[0], selection_space[0]);

    for(int count = 1; count < 26; count++)
    {
	selection_space[count] = letter_weights[count] + selection_space[count - 1];
//	printf("%c:\t%.1f\n", alphabet[count], selection_space[count]);
    }

    return 0;
}

char choose_a_letter(float *selection_space)
{
//    printf("\n\n%d\n\n", (int)(selection_space[25]));
    int choice = rand() % (int)(selection_space[25]);

    for(int count = 0; count < 26; count++)
    {
	if(choice < selection_space[count]) return (alphabet[count]);
    }

    printf("\n\n******THERE WAS A PROBLEM CHOOSING THE LETTER*******\n");
    printf("choice: %d\n", choice);
    
    return 0;
}
