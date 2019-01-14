#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int make_log(FILE *fp);
int calc_weights(FILE *fp, float *letter_weights);
int build_selection_space(float *letter_weights, float *selection_space);
char choose_a_letter(float *selection_space);

//Weighting scheme parameter macros
#define N 0.3
#define M 0.5

char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

int main()
{
    FILE *fp;

    //generate log file
    fp = fopen("log_file.txt", "w");
    make_log(fp);
    fclose(fp);

    //cacluate weigthts
    fp = fopen("log_file.txt", "r");
    float letter_weights[26];
    calc_weights(fp, letter_weights);

    //process letter weights
    for(int i = 0; i < 26; i++)
    {
	letter_weights[i] -= 11;
	letter_weights[i] *= -1;
	letter_weights[i] *= N;
	letter_weights[i] += M;
	letter_weights[i] *= 10;
//	printf("%c:\t%.1f\n",  alphabet[i], letter_weights[i]);
    }

    //build selection space
    float selection_space[26];
    build_selection_space(letter_weights, selection_space);

    //pick a letter

    //seed rand()
    time_t t;
    srand((unsigned) time(&t));    
    char choice;

    choice = choose_a_letter(selection_space);
    printf("the choice was %c\n", choice);

    return 0;
}



/******************************************
HELPER FUNCTIONS
 ******************************************/


int make_log(FILE *fp)
{
    // make alphabet game log file cycling
    // through possible results... ie
    // from 0 to 10 "1's" with associated
    // number of "-1's"

    int num_ones;

    for(int i = 0; i < 26; i++)
    {
	fprintf(fp, "%c, ", alphabet[i]);
	num_ones = i%11;
	for(int j = 0; j < num_ones; j++)
	{
	    fprintf(fp, "1, ");
	}
	for(int k = 0; k < (10 - num_ones); k++)
	{
	    fprintf(fp, "-1, ");
	}
	fprintf(fp, "\n");
	
    }


    return 0;    
}

int calc_weights(FILE *fp, float *letter_weights)
{
    int results[10];
    int sum_results;
    char file_line[100];
    char letter;
    int count = 0;
	
    while(fgets(file_line, 100, fp))
    {
	sum_results = 0;
	sscanf(file_line, "%c, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \n",
	       &letter, &results[0], &results[1], &results[2], &results[3],
	       &results[4], &results[5], &results[6], &results[7],
	       &results[8], &results[9]);

	for(int i = 0; i < 10; i++)
	{
	    sum_results += results[i];
	}
	letter_weights[count] = (float)sum_results;
//	printf("%c: %d\n", letter, letter_weights[count]);
	count++;
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
    int choice = rand() % (int)(selection_space[25]);

    for(int count = 0; count < 26; count++)
    {
	if(choice < selection_space[count]) return (alphabet[count]);
    }

    printf("\n\n******THERE WAS A PROBLEM CHOOSING THE LETTER*******\n");
    printf("choice: %d\n", choice);
    
    return 0;
}

