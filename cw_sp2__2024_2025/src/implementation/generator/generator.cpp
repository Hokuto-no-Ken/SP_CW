#define _CRT_SECURE_NO_WARNINGS
// TODO: CHANGE BY fRESET() TO END
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: generator.cpp               *
*                                                  (draft!) *
*************************************************************/

//#define IDENTIFIER_LEXEME_TYPE 2
//#define VALUE_LEXEME_TYPE 4
//#define VALUE_SIZE 4

#ifndef __cplusplus
#define bool int
#define false 0
#define true 1
#endif

#include "../../../src/include/def.h"
#include "../../../src/include/config.h"
#include "../../../src/include/generator/generator.h"
#include "../../../src/include/lexica/lexica.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG_MODE_BY_ASSEMBLY
//#define C_CODER_MODE                   0x01
//#define ASSEMBLY_X86_WIN32_CODER_MODE  0x02
//#define OBJECT_X86_WIN32_CODER_MODE    0x04
//#define MACHINE_CODER_MODE             0x08
//
//unsigned char generatorMode = MACHINE_CODER_MODE;

#define MAX_TEXT_SIZE 8192
#define MAX_GENERATED_TEXT_SIZE (MAX_TEXT_SIZE * 6)
#define GENERATED_TEXT_SIZE_ 32768
#define GENERATED_TEXT_SIZE (MAX_TEXT_SIZE % MAX_GENERATED_TEXT_SIZE)


#define SUCCESS_STATE 0



#define MAX_OUTTEXT_SIZE (8*8192*1024)
unsigned char outText[MAX_OUTTEXT_SIZE] = ""; // !!!
#define MAX_TEXT_SIZE 8192
#define MAX_WORD_COUNT (MAX_TEXT_SIZE / 5)
#define MAX_LEXEM_SIZE 1024

#if 0

#define CODEGEN_DATA_TYPE int

#define START_DATA_OFFSET 512
#define OUT_DATA_OFFSET (START_DATA_OFFSET + 512)

#define M1 1024
#define M2 1024

//unsigned long long int dataOffsetMinusCodeOffset = 0x00003000;
unsigned long long int dataOffsetMinusCodeOffset = 0x00004000;

//unsigned long long int codeOffset = 0x000004AF;
//unsigned long long int baseOperationOffset = codeOffset + 49;// 0x00000031;
unsigned long long int baseOperationOffset = 0x000004AF;
unsigned long long int putProcOffset = 0x0000001B;
unsigned long long int getProcOffset = 0x00000044;

//unsigned long long int startCodeSize = 64 - 14; // 50 // -1

#endif

struct LabelOffsetInfo {
	char labelStr[MAX_LEXEM_SIZE];
	unsigned char* labelBytePtr;
	// TODO: ...
};
struct LabelOffsetInfo labelsOffsetInfoTable[MAX_WORD_COUNT] = { { "", NULL/*, 0, 0*/ } };
struct LabelOffsetInfo* lastLabelOffsetInfoInTable = labelsOffsetInfoTable; // first for begin

struct GotoPositionInfo { // TODO: by Index
	char labelStr[MAX_LEXEM_SIZE];
	unsigned char* gotoInstructionPositionPtr;
	// TODO: ...
};
struct GotoPositionInfo gotoPositionsInfoTable[MAX_WORD_COUNT] = { { "", NULL/*, 0, 0*/ } }; // TODO: by Index
struct GotoPositionInfo* lastGotoPositionInfoInTable = gotoPositionsInfoTable; // first for begin

////////////////////////////////

//#include "src/include/generator/generator.h"

unsigned char generatorMode = MACHINE_CODER_MODE;

char* tokenStruct[MAX_TOKEN_STRUCT_ELEMENT_COUNT][MAX_TOKEN_STRUCT_ELEMENT_PART_COUNT] = { NULL };

#if 0
static void intitTokenStruct__OLD() {
	//SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, MULTI_TOKEN_BITWISE_NOT, ("~"), (""), (""), (""))
	//
	//	a12345_ptr = a12345;
	//
	tokenStruct[MULTI_TOKEN_BITWISE_NOT][0] = (char*)"~";
	tokenStruct[MULTI_TOKEN_BITWISE_AND][0] = (char*)"&";
	tokenStruct[MULTI_TOKEN_BITWISE_OR][0] = (char*)"|";
	tokenStruct[MULTI_TOKEN_NOT][0] = (char*)"not";
	tokenStruct[MULTI_TOKEN_AND][0] = (char*)"and";
	tokenStruct[MULTI_TOKEN_OR][0] = (char*)"or";

	tokenStruct[MULTI_TOKEN_EQUAL][0] = (char*)"=";
	tokenStruct[MULTI_TOKEN_NOT_EQUAL][0] = (char*)"<>";
	tokenStruct[MULTI_TOKEN_LESS][0] = (char*)"<";
	tokenStruct[MULTI_TOKEN_GREATER][0] = (char*)">";
	tokenStruct[MULTI_TOKEN_LESS_OR_EQUAL][0] = (char*)"<";
	tokenStruct[MULTI_TOKEN_GREATER_OR_EQUAL][0] = (char*)">";

	tokenStruct[MULTI_TOKEN_ADD][0] = (char*)"add";
	tokenStruct[MULTI_TOKEN_SUB][0] = (char*)"sub";
	tokenStruct[MULTI_TOKEN_MUL][0] = (char*)"*";
	tokenStruct[MULTI_TOKEN_DIV][0] = (char*)"/";
	tokenStruct[MULTI_TOKEN_MOD][0] = (char*)"%";

	tokenStruct[MULTI_TOKEN_BIND_RIGHT_TO_LEFT][0] = (char*)"<-";
	tokenStruct[MULTI_TOKEN_BIND_LEFT_TO_RIGHT][0] = (char*)">>";

	tokenStruct[MULTI_TOKEN_COLON][0] = (char*)":";
	tokenStruct[MULTI_TOKEN_GOTO][0] = (char*)"goto";

	tokenStruct[MULTI_TOKEN_IF][0] = (char*)"if"; tokenStruct[MULTI_TOKEN_IF][1] = (char*)"(";
	//	tokenStruct[MULTI_TOKEN_IF_][0] = (char*)"if"; // don't change this!
	tokenStruct[MULTI_TOKEN_THEN][0] = (char*)")";
	//	tokenStruct[MULTI_TOKEN_THEN_][0] = (char*)"NULL"; tokenStruct[MULTI_TOKEN_IF][1] = (char*)"STATEMENT"; // don't change this!
	tokenStruct[MULTI_TOKEN_ELSE][0] = (char*)"else";


	tokenStruct[MULTI_TOKEN_FOR][0] = (char*)"for";
	tokenStruct[MULTI_TOKEN_TO][0] = (char*)"to";
	tokenStruct[MULTI_TOKEN_DOWNTO][0] = (char*)"downto";
	tokenStruct[MULTI_TOKEN_DO][0] = (char*)"do"; // tokenStruct[MULTI_TOKEN_DO][1] = (char*)":";

	//
	tokenStruct[MULTI_TOKEN_WHILE][0] = (char*)"while";
	tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0] = (char*)"continue"; tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][1] = (char*)"while";
	tokenStruct[MULTI_TOKEN_EXIT_WHILE][0] = (char*)"exit"; tokenStruct[MULTI_TOKEN_EXIT_WHILE][1] = (char*)"while";
	tokenStruct[MULTI_TOKEN_END_WHILE][0] = (char*)"finish"; tokenStruct[MULTI_TOKEN_END_WHILE][1] = (char*)"while";
	//

	//
	tokenStruct[MULTI_TOKEN_REPEAT][0] = (char*)"repeat";
	tokenStruct[MULTI_TOKEN_UNTIL][0] = (char*)"until";
	//

	//
	tokenStruct[MULTI_TOKEN_INPUT][0] = (char*)"scan";
	tokenStruct[MULTI_TOKEN_OUTPUT][0] = (char*)"print";
	//

	//
	tokenStruct[MULTI_TOKEN_RLBIND][0] = (char*)"<-";
	tokenStruct[MULTI_TOKEN_LRBIND][0] = (char*)">>";
	//

	tokenStruct[MULTI_TOKEN_SEMICOLON][0] = (char*)";";

	tokenStruct[MULTI_TOKEN_BEGIN][0] = (char*)"BEGIN";
	tokenStruct[MULTI_TOKEN_END][0] = (char*)"finish";

	tokenStruct[MULTI_TOKEN_NULL_STATEMENT][0] = (char*)"NULL"; tokenStruct[MULTI_TOKEN_NULL_STATEMENT][1] = (char*)"STATEMENT";
	//	NULL_STATEMENT null_statement
	//		null statement
		//return 0;
}
//char intitTokenStruct_ = (intitTokenStruct__OLD(), 0);
#endif
INIT_TOKEN_STRUCT_NAME(0);

unsigned char detectMultiToken(struct LexemInfo* lexemInfoTable, enum TokenStructName tokenStructName) {
	if (lexemInfoTable == NULL) {
		return false;
	}

	if (!strncmp(lexemInfoTable[0].lexemStr, tokenStruct[tokenStructName][0], MAX_LEXEM_SIZE)
		&& (tokenStruct[tokenStructName][1] == NULL || tokenStruct[tokenStructName][1][0] == '\0' || !strncmp(lexemInfoTable[1].lexemStr, tokenStruct[tokenStructName][1], MAX_LEXEM_SIZE))
		&& (tokenStruct[tokenStructName][2] == NULL || tokenStruct[tokenStructName][2][0] == '\0' || !strncmp(lexemInfoTable[2].lexemStr, tokenStruct[tokenStructName][2], MAX_LEXEM_SIZE))
		&& (tokenStruct[tokenStructName][3] == NULL || tokenStruct[tokenStructName][3][0] == '\0' || !strncmp(lexemInfoTable[3].lexemStr, tokenStruct[tokenStructName][3], MAX_LEXEM_SIZE))) {

		return !!(tokenStruct[tokenStructName][0] != NULL && tokenStruct[tokenStructName][0][0] != '\0')
			 + !!(tokenStruct[tokenStructName][1] != NULL && tokenStruct[tokenStructName][1][0] != '\0')
			 + !!(tokenStruct[tokenStructName][2] != NULL && tokenStruct[tokenStructName][2][0] != '\0')
			 + !!(tokenStruct[tokenStructName][3] != NULL && tokenStruct[tokenStructName][3][0] != '\0')
			;
	}
	else {
		return 0;
	}
}

unsigned char createMultiToken(struct LexemInfo** lexemInfoTable, enum TokenStructName tokenStructName) {
	if (lexemInfoTable == NULL || *lexemInfoTable == NULL) {
		return false;
	}

	if (tokenStruct[tokenStructName][0] != NULL && tokenStruct[tokenStructName][0][0] != '\0') {
		strncpy(lexemInfoTable[0][0].lexemStr, tokenStruct[tokenStructName][0], MAX_LEXEM_SIZE);
		lexemInfoTable[0][0].lexemId = 0;
		lexemInfoTable[0][0].tokenType = 0;
		lexemInfoTable[0][0].ifvalue = 0;
		lexemInfoTable[0][0].row = ~0;
		lexemInfoTable[0][0].col = ~0;

		++* lexemInfoTable;
	}
	else {
		return 0;
	}
	if (tokenStruct[tokenStructName][1] != NULL && tokenStruct[tokenStructName][1][0] != '\0') {
		strncpy((*lexemInfoTable)->lexemStr, tokenStruct[tokenStructName][1], MAX_LEXEM_SIZE);
		lexemInfoTable[0][0].lexemId = 0;
		lexemInfoTable[0][0].tokenType = 0;
		lexemInfoTable[0][0].ifvalue = 0;
		lexemInfoTable[0][0].row = ~0;
		lexemInfoTable[0][0].col = ~0;
		++* lexemInfoTable;
	}
	else {
		return 1;
	}
	if (tokenStruct[tokenStructName][2] != NULL && tokenStruct[tokenStructName][2][0] != '\0') {
		strncpy((*lexemInfoTable)->lexemStr, tokenStruct[tokenStructName][2], MAX_LEXEM_SIZE);
		lexemInfoTable[0][0].lexemId = 0;
		lexemInfoTable[0][0].tokenType = 0;
		lexemInfoTable[0][0].ifvalue = 0;
		lexemInfoTable[0][0].row = ~0;
		lexemInfoTable[0][0].col = ~0;
		++* lexemInfoTable;
	}
	else {
		return 2;
	}
	if (tokenStruct[tokenStructName][3] != NULL && tokenStruct[tokenStructName][3][0] != '\0') {
		strncpy((*lexemInfoTable)->lexemStr, tokenStruct[tokenStructName][3], MAX_LEXEM_SIZE);
		lexemInfoTable[0][0].lexemId = 0;
		lexemInfoTable[0][0].tokenType = 0;
		lexemInfoTable[0][0].ifvalue = 0;
		lexemInfoTable[0][0].row = ~0;
		lexemInfoTable[0][0].col = ~0;
		++* lexemInfoTable;
	}
	else {
		return 3;
	}

	return 4;
}


//#define MAX_ACCESSORY_STACK_SIZE 128
struct NonContainedLexemInfo lexemInfoTransformationTempStack[MAX_ACCESSORY_STACK_SIZE];
unsigned long long int lexemInfoTransformationTempStackSize = 0;

//


unsigned long long int getVariableOffset(char* identifierStr) {
	for (unsigned long long int index = 0; identifierIdsTable[index][0] != '\0'; ++index) {
		if (!strncmp(identifierIdsTable[index], identifierStr, MAX_LEXEM_SIZE)) {
			return START_DATA_OFFSET + sizeof(CODEGEN_DATA_TYPE) * index;
		}
	}

	return OUT_DATA_OFFSET;
}
//

	//0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 , 0x20 ,
unsigned char* outBytes2Code(unsigned char* currBytePtr, unsigned char* fragmentFirstBytePtr, unsigned long long int bytesCout) {
	for (; bytesCout--; *currBytePtr++ = *fragmentFirstBytePtr++);
	return currBytePtr;
}

unsigned char* makeEndProgramCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	const unsigned char code__xor_eax_eax[] = { 0x33, 0xC0 };
	const unsigned char code__ret[] = { 0xC3 };

	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__xor_eax_eax, 2);
	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__ret, 1);

#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf("\r\n");
	//printf("imul ebp, 4\r\n");
	//printf("add esp, ebp\r\n");
	//printf("xor ebp, ebp;\r\n");

	printf("    xor eax, eax\r\n");
	printf("    ret\r\n");

	printf("\r\n\r\n");

	printf("end start\r\n");

	printf("\r\n\r\n");

#endif

	return currBytePtr;
}

unsigned char* makeTitle(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {

#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf(".686\r\n");
	printf(".model flat, stdcall\r\n");
	printf("option casemap : none\r\n");
#endif

	return currBytePtr;
}

unsigned char* makeDependenciesDeclaration(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {

#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf("\r\n");
	printf("GetStdHandle proto STDCALL, nStdHandle : DWORD\r\n");
	printf("ExitProcess proto STDCALL, uExitCode : DWORD\r\n");
	printf(";MessageBoxA PROTO hwnd : DWORD, lpText : DWORD, lpCaption : DWORD, uType : DWORD\r\n");
	printf("ReadConsoleA proto STDCALL, hConsoleInput : DWORD, lpBuffer : DWORD, nNumberOfCharsToRead : DWORD, lpNumberOfCharsRead : DWORD, lpReserved : DWORD\r\n");
	printf("WriteConsoleA proto STDCALL, hConsoleOutput : DWORD, lpBuffert : DWORD, nNumberOfCharsToWrite : DWORD, lpNumberOfCharsWritten : DWORD, lpReserved : DWORD\r\n");
	printf("wsprintfA PROTO C : VARARG\r\n");
	printf("\r\n");
	printf("GetConsoleMode PROTO STDCALL, hConsoleHandle:DWORD, lpMode : DWORD\r\n");
	printf("\r\n");
	printf("SetConsoleMode PROTO STDCALL, hConsoleHandle:DWORD, dwMode : DWORD\r\n");
	printf("\r\n");
	printf("ENABLE_LINE_INPUT EQU 0002h\r\n");
	printf("ENABLE_ECHO_INPUT EQU 0004h\r\n");
#endif

	return currBytePtr;
}

unsigned char* makeDataSection(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf("\r\n");
	printf(".data\r\n");
	printf("    data_start db 8192 dup (0)\r\n");
	printf("    ;title_msg db \"Output:\", 0\r\n");
	printf("    valueTemp_msg db 256 dup(0)\r\n");
	printf("    valueTemp_fmt db \"%%d\", 10, 13, 0\r\n");
	printf("    ;NumberOfCharsWritten dd 0\r\n");
	printf("    hConsoleInput dd 0\r\n");
	printf("    hConsoleOutput dd 0\r\n");
	printf("    buffer db 128 dup(0)\r\n");
	printf("    readOutCount dd ?\r\n");
#endif

	return currBytePtr;
}

unsigned char* makeBeginProgramCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf("\r\n");
	printf(".code\r\n");
	printf("start:\r\n");
#endif

	return currBytePtr;
}

unsigned char* makeInitCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	//	unsigned char code__call_NexInstructionLabel[]          = { 0xE8, 0x00, 0x00, 0x00, 0x00 };      
	//	                                                                                                 
	//	unsigned char code__pop_esi[]                           = { 0x5E };                              
	//	unsigned char code__sub_esi_5[]                         = { 0x83, 0xEE, 0x05 };                  
	//	unsigned char code__mov_edi_esi[]                       = { 0x8B, 0xFE };                        
	//	unsigned char code__add_edi_dataOffsetMinusCodeOffset[] = { 0xE8, 0xC7, 0x00, 0x00, 0x00, 0x00 }; 
	//	//unsigned char code__xor_ebp_ebp[]                       = { 0x33, 0xED };                     
	//	unsigned char code__mov_ecx_edi[]                       = { 0x8B, 0xCF };                       
	//	unsigned char code__add_ecx_512[]                       = { 0x81, 0xC1, 0x00, 0x02, 0x00, 0x00 };
	//	unsigned char code__jmp_initConsole[] = { 0xEB, 0x7C };
	//
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__call_NexInstructionLabel, 5);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_esi, 1);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_esi_5, 3);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_edi_esi, 2);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_edi_dataOffsetMinusCodeOffset, 6);
	//	*(unsigned int *)(currBytePtr - 4) = dataOffsetMinusCodeOffset;
	//	//currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__xor_ebp_ebp, 2);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ecx_edi, 2);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ecx_512, 6);

#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf("\r\n");
	printf("    db 0E8h, 00h, 00h, 00h, 00h; call NexInstruction\r\n");
	printf(";NexInstruction:\r\n");
	printf("    pop esi\r\n");
	printf("    sub esi, 5\r\n");
	printf("    mov edi, esi\r\n");//printf("    mov edi, offset data_start\r\n");
	printf("    add edi, 0%08Xh\r\n", (int)dataOffsetMinusCodeOffset);
	//printf("    xor ebp, ebp\r\n");
	printf("    mov ecx, edi\r\n");
	printf("    add ecx, 512\r\n");
	printf("    jmp initConsole\r\n");

	printf("    putProc PROC\r\n");
	printf("        push eax\r\n");
	printf("        push offset valueTemp_fmt\r\n");
	printf("        push offset valueTemp_msg\r\n");
	printf("        call wsprintfA\r\n");
	printf("        add esp, 12\r\n");
	printf("\r\n");
	printf("        ;push 40h\r\n");
	printf("        ;push offset title_msg\r\n");
	printf("        ;push offset valueTemp_msg;\r\n");
	printf("        ;push 0\r\n");
	printf("        ;call MessageBoxA\r\n");
	printf("\r\n");
	printf("        push 0\r\n");
	printf("        push 0; offset NumberOfCharsWritten\r\n");
	printf("        push eax; NumberOfCharsToWrite\r\n");
	printf("        push offset valueTemp_msg\r\n");
	printf("        push hConsoleOutput\r\n");
	printf("        call WriteConsoleA\r\n");
	printf("\r\n");
	printf("        ret\r\n");
	printf("    putProc ENDP\r\n");

	printf("\r\n\r\n");

	//printf("    getProc PROC\r\n");
	//printf("        push eax\r\n");
	//printf("        push offset valueTemp_fmt\r\n");
	//printf("        push offset valueTemp_msg\r\n");
	//printf("        call wsprintfA\r\n");
	//printf("        add esp, 12\r\n");
	//printf("\r\n");
	//printf("        push 40h\r\n");
	//printf("        push offset title_msg\r\n");
	//printf("        push offset valueTemp_msg;\r\n");
	//printf("        push 0\r\n");
	//printf("        call MessageBoxA\r\n");
	//printf("\r\n");
	//printf("        ret\r\n");
	//printf("    getProc ENDP\r\n");

	printf("    getProc PROC\r\n");
	printf("        push ebp\r\n");
	printf("        mov ebp, esp\r\n");
	printf("\r\n");
	printf("        push 0\r\n");
	printf("        push offset readOutCount\r\n");
	printf("        push 15\r\n");
	printf("        push offset buffer + 1\r\n");
	printf("        push hConsoleInput\r\n");
	printf("        call ReadConsoleA\r\n");
	printf("\r\n");
	printf("        lea esi, offset buffer\r\n");
	printf("        add esi, readOutCount\r\n");
	printf("        sub esi, 2\r\n");
	printf("        call string_to_int\r\n");
	printf("\r\n");
	printf("        mov esp, ebp\r\n");
	printf("        pop ebp\r\n");
	printf("        ret\r\n");
	printf("    getProc ENDP\r\n");

	printf("\r\n");

	printf("    string_to_int PROC\r\n");
	printf("    ;  input: ESI - string\r\n");
	printf("    ; output: EAX - value\r\n");
	printf("        xor eax, eax\r\n");
	printf("        mov ebx, 1\r\n");
	printf("        xor ecx, ecx\r\n");
	printf("\r\n");
	printf("convert_loop :\r\n");
	printf("        movzx ecx, byte ptr[esi]\r\n");
	printf("        test ecx, ecx\r\n");
	printf("        jz done\r\n");
	printf("        sub ecx, '0'\r\n");
	printf("        imul ecx, ebx\r\n");
	printf("        add eax, ecx\r\n");
	printf("        imul ebx, ebx, 10\r\n");
	printf("        dec esi\r\n");
	printf("        jmp convert_loop\r\n");
	printf("\r\n");
	printf("done:\r\n");
	printf("        ret\r\n");
	printf("    string_to_int ENDP\r\n");

	printf("\r\n");

	printf("    initConsole:\r\n");
	printf("    push -10\r\n");
	printf("    call GetStdHandle\r\n");
	printf("    mov hConsoleInput, eax\r\n");
	printf("    push -11\r\n");
	printf("    call GetStdHandle\r\n");
	printf("    mov hConsoleOutput, eax\r\n");
	printf("    \r\n");
	printf("    ;push ecx\r\n");
	printf("    ;push ebx\r\n");
	printf("    ;push esi\r\n");
	printf("    ;push edi\r\n");
	printf("    ;push offset mode\r\n");
	printf("    ;push hConsoleInput\r\n");
	printf("    ;call GetConsoleMode\r\n");
	printf("    ;mov ebx, eax\r\n");
	printf("    ;or ebx, ENABLE_LINE_INPUT \r\n");
	printf("    ;or ebx, ENABLE_ECHO_INPUT\r\n");
	printf("    ;push ebx\r\n");
	printf("    ;push hConsoleInput\r\n");
	printf("    ;call SetConsoleMode\r\n");
	printf("    ;pop edi\r\n");
	printf("    ;pop esi\r\n");
	printf("    ;pop ebx\r\n");
	printf("    ;pop ecx\r\n");

#endif

	return currBytePtr;
}

//
#include "../../../src/include/preparer/preparer.h"
//
//
#include "../../../src/include/generator/bitwise_not.h"
#include "../../../src/include/generator/bitwise_and.h"
#include "../../../src/include/generator/bitwise_or.h"
#include "../../../src/include/generator/not.h"
#include "../../../src/include/generator/and.h"
#include "../../../src/include/generator/or.h"
//		  
#include "../../../src/include/generator/add.h"
#include "../../../src/include/generator/sub.h"
#include "../../../src/include/generator/mul.h"
#include "../../../src/include/generator/div.h"
#include "../../../src/include/generator/mod.h" 
//
#include "../../../src/include/generator/null_statement.h"
#include "../../../src/include/generator/operand.h"
#include "../../../src/include/generator/input.h"
#include "../../../src/include/generator/output.h"
#include "../../../src/include/generator/equal.h"
#include "../../../src/include/generator/not_equal.h"
#include "../../../src/include/generator/less.h"
#include "../../../src/include/generator/greater.h"
#include "../../../src/include/generator/less_or_equal.h"
#include "../../../src/include/generator/greater_or_equal.h"
#include "../../../src/include/generator/rlbind.h"
#include "../../../src/include/generator/lrbind.h"
#include "../../../src/include/generator/goto_label.h"
#include "../../../src/include/generator/if_then.h"
#include "../../../src/include/generator/else.h"
#include "../../../src/include/generator/for.h"
#include "../../../src/include/generator/while.h"
#include "../../../src/include/generator/repeat_until.h"
//		  
#include "../../../src/include/generator/semicolon.h"
//

unsigned char* initMake(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	return currBytePtr;
//	for (; (*lastLexemInfoInTable)->lexemStr[0] && strncmp((*lastLexemInfoInTable)->lexemStr, "start", MAX_LEXEM_SIZE); ++ * lastLexemInfoInTable);
//	for (; (*lastLexemInfoInTable)->lexemStr[0] && strncmp((*lastLexemInfoInTable)->lexemStr, ";", MAX_LEXEM_SIZE); ++ * lastLexemInfoInTable);
//	return currBytePtr;
}

unsigned char* makeSaveHWStack(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	const unsigned char code__mov_ebp_esp[] = { 0x8B, 0xEC };

	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ebp_esp, 2);

#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf("\r\n");
	printf("    ;hw stack save(save esp)\r\n");
	printf("    mov ebp, esp\r\n");

#endif

	return currBytePtr;
}

unsigned char* makeResetHWStack(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	const unsigned char code__mov_esp_ebp[] = { 0x8B, 0xE5 };

	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_esp_ebp, 2);

#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf("\r\n");
	printf("    ;hw stack reset(restore esp)\r\n");
	printf("    mov esp, ebp\r\n");

#endif

	return currBytePtr;
}

unsigned char* noMake(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	if (!strncmp((*lastLexemInfoInTable)->lexemStr, T_NAME_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_DATA_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_BODY_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_DATA_TYPE_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_COMA_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_END_0, MAX_LEXEM_SIZE)
		) {

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* createPattern() {

	return NULL;
}

unsigned char* getCodeBytePtr(unsigned char* baseBytePtr) {

	return baseBytePtr + baseOperationOffset;
}

void makeCode(struct LexemInfo** lastLexemInfoInTable/*TODO:...*/, unsigned char* currBytePtr) { // TODO:...
	currBytePtr = makeTitle(lastLexemInfoInTable, currBytePtr);
	currBytePtr = makeDependenciesDeclaration(lastLexemInfoInTable, currBytePtr);

	currBytePtr = makeDataSection(lastLexemInfoInTable, currBytePtr);

	currBytePtr = makeBeginProgramCode(lastLexemInfoInTable, currBytePtr);
	lexemInfoTransformationTempStackSize = 0;
	currBytePtr = makeInitCode(lastLexemInfoInTable, currBytePtr);
	currBytePtr = initMake(lastLexemInfoInTable, currBytePtr);
	currBytePtr = makeSaveHWStack(lastLexemInfoInTable, currBytePtr);
	for (struct LexemInfo* lastLexemInfoInTable_; lastLexemInfoInTable_ = *lastLexemInfoInTable, (*lastLexemInfoInTable)->lexemStr[0] != '\0';) {

		LABEL_GOTO_LABELE_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//
		IF_THEN_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		ELSE_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		//

		//currBytePtr = makeForCycleCode(lastLexemInfoInTable, currBytePtr);
		//currBytePtr = makeToOrDowntoCycleCode(lastLexemInfoInTable, currBytePtr);
		//currBytePtr = makeDoCycleCode(lastLexemInfoInTable, currBytePtr);
		//currBytePtr = makeSemicolonAfterForCycleCode(lastLexemInfoInTable, currBytePtr);
		FOR_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//
		WHILE_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		//

		//
		REPEAT_UNTIL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		//

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeValueCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeIdentifierCode(lastLexemInfoInTable, currBytePtr);
		OPERAND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeNotCode(lastLexemInfoInTable, currBytePtr);
		BITWISE_NOT_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		BITWISE_AND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		BITWISE_OR_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		NOT_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		AND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		OR_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		EQUAL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		NOT_EQUAL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		LESS_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		GREATER_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		LESS_OR_EQUAL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		GREATER_OR_EQUAL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeAddCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeSubCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeMulCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeDivCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeModCode(lastLexemInfoInTable, currBytePtr);
		ADD_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		SUB_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		MUL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		DIV_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		MOD_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeRightToLeftBindCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeLeftToRightBindCode(lastLexemInfoInTable, currBytePtr);
		INPUT_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		OUTPUT_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeGetCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makePutCode(lastLexemInfoInTable, currBytePtr);
		RLBIND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		LRBIND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		///* (1) Ignore phase*/if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeSemicolonAfterNonContextCode(lastLexemInfoInTable, currBytePtr);
		///* (2) Ignore phase*/if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeSemicolonIgnoreContextCode(lastLexemInfoInTable, currBytePtr);
		NON_CONTEXT_SEMICOLON_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		NON_CONTEXT_NULL_STATEMENT(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		if (lastLexemInfoInTable_ == *lastLexemInfoInTable) {
			currBytePtr = noMake(lastLexemInfoInTable, currBytePtr);
		}

		if (lastLexemInfoInTable_ == *lastLexemInfoInTable) {
			printf("\r\nError in the code generator! \"%s\" - unexpected token!\r\n", (*lastLexemInfoInTable)->lexemStr);
			exit(0);
		}

	}

	currBytePtr = makeResetHWStack(lastLexemInfoInTable, currBytePtr);
	currBytePtr = makeEndProgramCode(lastLexemInfoInTable, currBytePtr);
}

unsigned char outCode[GENERATED_TEXT_SIZE] = { '\0' };
void viewCode(unsigned char* outCodePtr, size_t outCodePrintSize, unsigned char align) {
	printf("\r\n;            +0x0 +0x1 +0x2 +0x3 +0x4 +0x5 +0x6 +0x7 +0x8 +0x9 +0xA +0xB +0xC +0xD +0xE +0xF ");
	printf("\r\n;0x00000000: ");
	size_t outCodePrintIndex = outCodePrintSize - 1;
	for (size_t index = 0; index <= outCodePrintIndex;) {
		printf("0x%02X ", outCodePtr[index]);
		if (!(++index % align)) {
			size_t indexMinus16 = index - align;
			do {
				//printf("0x%02X ", outCodePtr[index]);
				if (outCodePtr[indexMinus16] >= 32 && outCodePtr[indexMinus16] <= 126) {
					printf("%c", outCodePtr[indexMinus16]);
				}
				else {
					printf(" ");
					//printf("%2c", 32);
				}
			} while (++indexMinus16 % align);

			printf("\r\n;0x%08X: ", (unsigned int)index);
		}
	}
}