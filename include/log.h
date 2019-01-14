#ifndef _LOG_H_
#define _LOG_H_

/*****************************************************************
INTERFACE DECLARATIONS
 *****************************************************************/

//FUNCTION DECLARATIONS
int log_result(int result, char letter, char answer);
int read_log_line(char *file_line, int *last_ten,
		  int *total, int *diff, char *letter);
int generate_report();

//MACROS
#define LOG_FORMAT "%c: %d: %d: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n"
#define MAX_FILE_LINE 60
#define LOG_FILE "result_log"

#endif //_LOG_H_
