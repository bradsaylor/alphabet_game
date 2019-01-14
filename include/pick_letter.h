#ifndef PICK_LETTER_H_
#define PICK_LETTER_H__

#include <stdio.h>

/*****************************************************************
FUNCTION DECLARATIONS
 *****************************************************************/
int calc_weights(char *file_name, float *letter_weights);
int process_weights();
int build_selection_space(float *letter_weights, float *selection_space);
char choose_a_letter(float *selection_space);


#endif //PICK_LETTER_H_
