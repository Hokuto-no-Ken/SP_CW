#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: cw_lex.cpp                  *
*                                                  (draft!) *
*************************************************************/

#include "../../../src/include/cli/cli.h"

#include "../../../src/include/def.h"
#include "../../../src/include/config.h"
#include "../../../src/include/generator/generator.h"
#include "../../../src/include/lexica/lexica.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//#define DEFAULT_INPUT_FILENAME "file44.cwl"
//
//#define PREDEFINED_TEXT \
//	"name MN\r\n" \
//	"data\r\n" \
//	"    #*argumentValue*#\r\n" \
//	"    long int AV\r\n" \
//	"    #*resultValue*#\r\n" \
//	"    long int RV\r\n" \
//	";\r\n" \
//	"\r\n" \
//	"body\r\n" \
//	"    RV << 1; #*resultValue = 1; *#\r\n" \
//	"\r\n" \
//	"    #*input*#\r\n" \
//	"	 get AV; #*scanf(\"%d\", &argumentValue); *#\r\n" \
//	"\r\n" \
//	"    #*compute*#\r\n" \
//	"	 CL: #*label for cycle*#\r\n" \
//	"    if AV == 0 goto EL #*for (; argumentValue; --argumentValue)*#\r\n" \
//	"        RV << RV ** AV; #*resultValue *= argumentValue; *#\r\n" \
//	"        AV << AV -- 1; \r\n" \
//	"    goto CL\r\n" \
//	"    EL: #*label for end cycle*#\r\n" \
//	"\r\n" \
//	"    #*output*#\r\n" \
//	"    put RV; #*printf(\"%d\", resultValue); *#\r\n" \
//	"end" \

unsigned int mode = 0;
char parameters[PARAMETERS_COUNT][MAX_PARAMETERS_SIZE] = { "" };

void comandLineParser(int argc, char* argv[], unsigned int* mode, char(*parameters)[MAX_PARAMETERS_SIZE]) {
	char useDefaultModes = 1;
	*mode = 0;
	for (int index = 1; index < argc; ++index) {
		if (!strcmp(argv[index], "-lex")) {
			*mode |= LEXICAL_ANALISIS_MODE;
			useDefaultModes = 0;
			continue;
		}
		else if (!strcmp(argv[index], "-d")) {
			*mode |= DEBUG_MODE;
			useDefaultModes = 0;
			continue;
		}

		// other keys
		// TODO:...

		// input file name
		strncpy(parameters[INPUT_FILENAME_PARAMETER], argv[index], MAX_PARAMETERS_SIZE);
	}

	// default input file name, if not entered manually
	if (parameters[INPUT_FILENAME_PARAMETER][0] == '\0') {
		strcpy(parameters[INPUT_FILENAME_PARAMETER], DEFAULT_INPUT_FILENAME);
		printf("Input file name not setted. Used default input file name \"file1.z10\"\r\n\r\n");
	}

	// default mode, if not entered manually
	if (useDefaultModes) {
		*mode = DEFAULT_MODE;
		printf("Used default mode\r\n\r\n");
	}

	return;
}

// after using this function use free(void *) function to release text buffer
size_t loadSource(char** text, char* fileName) {
	if (!fileName) {
		printf("No input file name\r\n");
		return 0;
	}

	FILE* file = fopen(fileName, "rb");

	if (file == NULL) {
		printf("File not loaded\r\n");
		return 0;
	}

	fseek(file, 0, SEEK_END);
	long fileSize_ = ftell(file);
	if (fileSize_ >= MAX_TEXT_SIZE) {
		printf("the file(%ld bytes) is larger than %d bytes\r\n", fileSize_, MAX_TEXT_SIZE);
		fclose(file);
		exit(2); // TODO: ...
		//return 0;
	}
	size_t fileSize = fileSize_;
	rewind(file);

	if (!text) {
		printf("Load source error\r\n");
		return 0;
	}
	*text = (char*)malloc(sizeof(char) * (fileSize + 1));
	if (*text == NULL) {
		fputs("Memory error", stderr);
		fclose(file);
		exit(2); // TODO: ...
		//return 0;
	}

	size_t result = fread(*text, sizeof(char), fileSize, file);
	if (result != fileSize) {
		fputs("Reading error", stderr);
		fclose(file);
		exit(3); // TODO: ...
		//return 0;
	}
	(*text)[fileSize] = '\0';

	fclose(file);

	return fileSize;
}