#define _CRT_SECURE_NO_WARNINGS  // for using sscanf in VS
/************************************************************
* N.Kozak // Lviv'2024 // example lexical analysis by regex *
*                         file: cw.cpp                      *
*                                                           *
*************************************************************/
//#define USE_PREDEFINED_PARAMETERS // enable this define for use predefined value
//#pragma comment(linker, "/STACK:516777216")
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include <fstream>
#include <iostream>
#include <algorithm>//
#include <iterator>
#include <regex>

#include "src/include/def.h"
#include "src/include/config.h"

#include "src/include/cli/cli.h"
bool reSetDefaultInputFileName_ = 
strcpy(parameters[INPUT_FILENAME_PARAMETER], "../test_programs/file1.z10")
!= NULL;
#include "src/include/lexica/lexica.h"

#include "src/include/syntax/syntax.h"
#include "src/include/semantix/semantix.h"
#include "src/include/preparer/preparer.h"
#include "src/include/generator/generator.h"

struct LexemInfo lexemesInfoTableTemp[MAX_WORD_COUNT]; // = { { "", 0, 0, 0 } };
struct LexemInfo* lastLexemInfoInTableTemp = lexemesInfoTableTemp; // first for begin

unsigned char new_code[8 * 1024 * 1024] = { '\0' };
int main(int argc, char* argv[]) {

#if defined(_DEBUG) || !defined(_WIN32) || !defined(_M_IX86)
		printf("Please, switch to mode VS + x86 + Release.\r\n");
		//(void)getchar();
		//return 0;
#endif

#ifdef	USE_PREDEFINED_PARAMETERS
	mode = DEFAULT_MODE;
	char text[MAX_TEXT_SIZE] = PREDEFINED_TEXT;
#else
	comandLineParser(argc, argv, &mode, parameters);
	char* text;
	size_t sourceSize = loadSource(&text, parameters[INPUT_FILENAME_PARAMETER]);
	if (!sourceSize) {
		printf("Press Enter to exit . . .");
		(void)getchar();
		return 0;
	}
#endif

	if (!(mode & LEXICAL_ANALISIS_MODE)) {
		printf("NO SUPORTED MODE ...\r\n");
		printf("Press Enter to exit . . .");
		(void)getchar();
		return 0;
	}

	if (mode & DEBUG_MODE) {
		printf("Original source:\r\n");
		printf("-------------------------------------------------------------------\r\n");
		printf("%s\r\n", text);
		printf("-------------------------------------------------------------------\r\n\r\n");
	}

	int commentRemoverResult = commentRemover(text, "!!", "\n");
	if (commentRemoverResult) {
		printf("Comment remover return %d\r\n", commentRemoverResult);
		printf("Press Enter to exit . . .");
		(void)getchar();
		return 0;
	}
	if (mode & DEBUG_MODE) {
		printf("Source after comment removing:\r\n");
		printf("-------------------------------------------------------------------\r\n");
		printf("%s\r\n", text);
		printf("-------------------------------------------------------------------\r\n\r\n");
	}

	struct LexemInfo ifBadLexemeInfo = tokenize(text, &lastLexemInfoInTable, identifierIdsTable, lexicalAnalyze);

	if (ifBadLexemeInfo.tokenType == UNEXPEXTED_LEXEME_TYPE) {
		UNEXPEXTED_LEXEME_TYPE;
		ifBadLexemeInfo.tokenType;
		printf("Lexical analysis detected unexpected lexeme\r\n");
		printLexemes(&ifBadLexemeInfo, 1);
		printf("Press Enter to exit . . .");
		(void)getchar();
		return 0;
	}
	if (mode & DEBUG_MODE) {
		printLexemes(lexemesInfoTable, 0);
	}
	else {
		printf("Lexical analysis complete success\r\n");
	}

	if (!syntaxAnalyze(lexemesInfoTable, &grammar, DEFAULT_SYNTAX_ANAlYZE_MODE)) {
		return 0;
	}

	if (checkingInternalCollisionInDeclarations() != SUCCESS_STATE) {
		return 0;
	}
	(void)checkingVariableInitialization();            // TODO: implement this
	(void)checkingCollisionInDeclarationsByKeyWords(); // TODO: implement this

	lastLexemInfoInTable = lexemesInfoTable;
	makePrepare(lexemesInfoTable, &lastLexemInfoInTable, &lastLexemInfoInTableTemp);
	printLexemes(lexemesInfoTableTemp, 0);

	extern void reconstruct_file(const char* output_file);
	extern unsigned long long int reconstruct_image(unsigned char* byteImage);
	extern void write_image_to_file(const char* output_file, unsigned char* byteImage, unsigned long long int imageSize);
	unsigned long long int imageSize = reconstruct_image(new_code);
	unsigned char* currBytePtr = getCodeBytePtr(new_code);

	lastLexemInfoInTableTemp = lexemesInfoTableTemp;
//	struct LexemInfo* lastLexemInfoInTableTemp_ = lexemesInfoTableTemp; // first for begin
	makeCode(&lastLexemInfoInTableTemp, currBytePtr);
	//printf("\r\n;CODE:\r\n");
	//viewCode(outCode, 160/*GENERATED_TEXT_SIZE*/, 16);
	//printf("\r\n;ENDCODE;\r\n");

	write_image_to_file("out.exe", new_code, imageSize);

	printf("Press Enter to exit . . .");
	(void)getchar();

#ifndef	USE_PREDEFINED_PARAMETERS
	free(text);
#endif

	return 0;
}