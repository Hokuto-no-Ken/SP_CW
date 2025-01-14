#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: cw_lex.h                    *
*                                                  (draft!) *
*************************************************************/

#define MAX_PARAMETERS_SIZE 4096
#define PARAMETERS_COUNT 4
#define INPUT_FILENAME_PARAMETER 0

#include "../../../src/include/def.h"
#include "../../../src/include/config.h"
#include "../../../src/include/generator/generator.h"
#include "../../../src/include/lexica/lexica.h"
//#include "stdio.h"
//#include "stdlib.h"
//#include "string.h"

#define DEFAULT_INPUT_FILENAME "file44.z10" // TODO: move!

#define PREDEFINED_TEXT \
	"name MN\r\n" \
	"data\r\n" \
	"    #*argumentValue*#\r\n" \
	"    long int AV\r\n" \
	"    #*resultValue*#\r\n" \
	"    long int RV\r\n" \
	";\r\n" \
	"\r\n" \
	"body\r\n" \
	"    RV << 1; #*resultValue = 1; *#\r\n" \
	"\r\n" \
	"    #*input*#\r\n" \
	"	 get AV; #*scanf(\"%d\", &argumentValue); *#\r\n" \
	"\r\n" \
	"    #*compute*#\r\n" \
	"	 CL: #*label for cycle*#\r\n" \
	"    if AV == 0 goto EL #*for (; argumentValue; --argumentValue)*#\r\n" \
	"        RV << RV ** AV; #*resultValue *= argumentValue; *#\r\n" \
	"        AV << AV -- 1; \r\n" \
	"    goto CL\r\n" \
	"    EL: #*label for end cycle*#\r\n" \
	"\r\n" \
	"    #*output*#\r\n" \
	"    put RV; #*printf(\"%d\", resultValue); *#\r\n" \
	"end" \

extern unsigned int mode;
extern char parameters[PARAMETERS_COUNT][MAX_PARAMETERS_SIZE];

void comandLineParser(int argc, char* argv[], unsigned int* mode, char(*parameters)[MAX_PARAMETERS_SIZE]);
// after using this function use free(void *) function to release text buffer
size_t loadSource(char** text, char* fileName);