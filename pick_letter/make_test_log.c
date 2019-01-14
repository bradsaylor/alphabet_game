#include <stdio.h>

int make_log(FILE *fp);

char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

int main()
{
    FILE *fp;
    fp = fopen("result_log", "w");
    make_log(fp);
    
    return 0;
}

int make_log(FILE *fp)
{
    // make alphabet game log file cycling
    // through possible results... ie
    // from 0 to 10 "1's" with associated
    // number of "-1's"

    int num_ones;

    fprintf(fp, "LETTER: TOTAL: DIFF: LAST 10\n\n");

    for(int i = 0; i < 26; i++)
    {
	fprintf(fp, "%c: 0: 0: ", alphabet[i]);
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


