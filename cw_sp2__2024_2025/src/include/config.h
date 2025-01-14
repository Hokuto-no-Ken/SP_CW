#include "../include/def.h"
#define LEXICAL_ANALISIS_MODE 1
#define SEMANTIC_ANALISIS_MODE 2
#define FULL_COMPILER_MODE 4

#define DEBUG_MODE 512

#define DEFAULT_MODE (LEXICAL_ANALISIS_MODE | DEBUG_MODE)

// coca cola
#define TOKENS_RE         ";|<-|>>|\\+|-|\\*|,|=|<>|:|\\(|\\)|<=|>=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]"
#define KEYWORDS_RE       ";|<-|>>|\\+|-|\\*|,|=|<>|:|\\(|\\)|program|var|start|finish|exit|continue|print|scan|if|else|for|to|downto|do|while|repeat|until|goto|\\/|\\%|<|>|not|and|or|integer16|add|sub"
#define IDENTIFIERS_RE    "[a-z][A-Z][A-Z][A-Z][A-Z][A-Z]"
#define UNSIGNEDVALUES_RE "0|[1-9][0-9]*"


// first column of the cw term paper option
#define PROGRAM_FORMAT \
{"tokenNAME__program_name", 2, {"tokenNAME","program_name"}},\
{"tokenSEMICOLON__tokenBODY", 2, {"tokenSEMICOLON","tokenBODY"}},\
{"tokenDATA__declaration", 2, {"tokenDATA","declaration"}},\
{"tokenNAME__program_name__tokenSEMICOLON__tokenBODY", 2, {"tokenNAME__program_name","tokenSEMICOLON__tokenBODY"}},\
{"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA__declaration"}},\
{"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA"}},\
{"statement__tokenEND", 2, {"statement","tokenEND"}},\
{"statement____iteration_after_two__tokenEND", 2, {"statement____iteration_after_two","tokenEND"}},\
{"program____part2", 2, {"tokenSEMICOLON","statement____iteration_after_two__tokenEND"}},\
{"program____part2", 2, {"tokenSEMICOLON","statement__tokenEND"}},\
{"program____part2", 2, {"tokenSEMICOLON","tokenEND"}},\
{"program", 2, {"program____part1","program____part2"}}, 


#define T_NAME_0 "program"
#define T_NAME_1 ""
#define T_NAME_2 ""
#define T_NAME_3 ""
#define T_BODY_0 "start"
#define T_BODY_1 ""
#define T_BODY_2 ""
#define T_BODY_3 ""
#define T_DATA_0 "var"
#define T_DATA_1 ""
#define T_DATA_2 ""
#define T_DATA_3 ""
#define T_DATA_TYPE_0 "integer16"
#define T_DATA_TYPE_1 ""
#define T_DATA_TYPE_2 ""
#define T_DATA_TYPE_3 ""
//
#define T_BITWISE_NOT_0 "~"
#define T_BITWISE_NOT_1 ""
#define T_BITWISE_NOT_2 ""
#define T_BITWISE_NOT_3 ""
#define T_BITWISE_AND_0 "&"
#define T_BITWISE_AND_1 ""
#define T_BITWISE_AND_2 ""
#define T_BITWISE_AND_3 ""
#define T_BITWISE_OR_0 "|"
#define T_BITWISE_OR_1 ""
#define T_BITWISE_OR_2 ""
#define T_BITWISE_OR_3 ""
#define T_NOT_0 "not"
#define T_NOT_1 ""
#define T_NOT_2 ""
#define T_NOT_3 ""
#define T_AND_0 "and"
#define T_AND_1 ""
#define T_AND_2 ""
#define T_AND_3 ""
#define T_OR_0 "or"
#define T_OR_1 ""
#define T_OR_2 ""
#define T_OR_3 ""
//
#define T_EQUAL_0 "="
#define T_EQUAL_1 ""
#define T_EQUAL_2 ""
#define T_EQUAL_3 ""
#define T_NOT_EQUAL_0 "<>"
#define T_NOT_EQUAL_1 ""
#define T_NOT_EQUAL_2 ""
#define T_NOT_EQUAL_3 ""
#define T_LESS_0 "<"
#define T_LESS_1 ""
#define T_LESS_2 ""
#define T_LESS_3 ""
#define T_GREATER_0 ">"
#define T_GREATER_1 ""
#define T_GREATER_2 ""
#define T_GREATER_3 ""
#define T_LESS_OR_EQUAL_0 "<"
#define T_LESS_OR_EQUAL_1 ""
#define T_LESS_OR_EQUAL_2 ""
#define T_LESS_OR_EQUAL_3 ""
#define T_GREATER_OR_EQUAL_0 ">"
#define T_GREATER_OR_EQUAL_1 ""
#define T_GREATER_OR_EQUAL_2 ""
#define T_GREATER_OR_EQUAL_3 ""
//
#define T_ADD_0 "add"
#define T_ADD_1 ""
#define T_ADD_2 ""
#define T_ADD_3 ""
#define T_SUB_0 "sub"
#define T_SUB_1 ""
#define T_SUB_2 ""
#define T_SUB_3 ""
#define T_MUL_0 "*"
#define T_MUL_1 ""
#define T_MUL_2 ""
#define T_MUL_3 ""
#define T_DIV_0 "/"
#define T_DIV_1 ""
#define T_DIV_2 ""
#define T_DIV_3 ""
#define T_MOD_0 "%"
#define T_MOD_1 ""
#define T_MOD_2 ""
#define T_MOD_3 ""
//
#define T_BIND_RIGHT_TO_LEFT_0 "<-"
#define T_BIND_RIGHT_TO_LEFT_1 ""
#define T_BIND_RIGHT_TO_LEFT_2 ""
#define T_BIND_RIGHT_TO_LEFT_3 ""
#define T_BIND_LEFT_TO_RIGHT_0 ">>"
#define T_BIND_LEFT_TO_RIGHT_1 ""
#define T_BIND_LEFT_TO_RIGHT_2 ""
#define T_BIND_LEFT_TO_RIGHT_3 ""
//
#define T_COMA_0 ","
#define T_COMA_1 ""
#define T_COMA_2 ""
#define T_COMA_3 ""
#define T_COLON_0 ":"
#define T_COLON_1 ""
#define T_COLON_2 ""
#define T_COLON_3 ""
#define T_GOTO_0 "goto"
#define T_GOTO_1 ""
#define T_GOTO_2 ""
#define T_GOTO_3 ""
//
#define T_IF_0 "if"
#define T_IF_1 "("
#define T_IF_2 ""
#define T_IF_3 ""
#define T_THEN_0 ")"
#define T_THEN_1 ""
#define T_THEN_2 ""
#define T_THEN_3 ""
#define T_ELSE_0 "else"
#define T_ELSE_1 ""
#define T_ELSE_2 ""
#define T_ELSE_3 ""
//
#define T_FOR_0 "for"
#define T_FOR_1 ""
#define T_FOR_2 ""
#define T_FOR_3 ""
#define T_TO_0 "to"
#define T_TO_1 ""
#define T_TO_2 ""
#define T_TO_3 ""
#define T_DOWNTO_0 "downto"
#define T_DOWNTO_1 ""
#define T_DOWNTO_2 ""
#define T_DOWNTO_3 ""
#define T_DO_0 "do"
#define T_DO_1 ""
#define T_DO_2 ""
#define T_DO_3 ""
//
#define T_WHILE_0 "while"
#define T_WHILE_1 ""
#define T_WHILE_2 ""
#define T_WHILE_3 ""
#define T_CONTINUE_WHILE_0 "continue"
#define T_CONTINUE_WHILE_1 "while"
#define T_CONTINUE_WHILE_2 ""
#define T_CONTINUE_WHILE_3 ""
#define T_EXIT_WHILE_0 "exit"
#define T_EXIT_WHILE_1 "while" 
#define T_EXIT_WHILE_2 "" 
#define T_EXIT_WHILE_3 ""
#define T_END_WHILE_0 "finish"
#define T_END_WHILE_1 "while"
#define T_END_WHILE_2 ""
#define T_END_WHILE_3 ""
//
#define T_REPEAT_0 "repeat"
#define T_REPEAT_1 ""
#define T_REPEAT_2 ""
#define T_REPEAT_3 ""
#define T_UNTIL_0 "until"
#define T_UNTIL_1 ""
#define T_UNTIL_2 ""
#define T_UNTIL_3 ""
//
#define T_INPUT_0 "scan"
#define T_INPUT_1 ""
#define T_INPUT_2 ""
#define T_INPUT_3 ""
#define T_OUTPUT_0 "print"
#define T_OUTPUT_1 ""
#define T_OUTPUT_2 ""
#define T_OUTPUT_3 ""
//
#define T_RLBIND_0 "<-"
#define T_RLBIND_1 ""
#define T_RLBIND_2 ""
#define T_RLBIND_3 ""
#define T_LRBIND_0 ">>"
#define T_LRBIND_1 ""
#define T_LRBIND_2 ""
#define T_LRBIND_3 ""
//
#define T_SEMICOLON_0 ";"
#define T_SEMICOLON_1 ""
#define T_SEMICOLON_2 ""
#define T_SEMICOLON_3 ""
//
#define T_BEGIN_0 "BEGIN"
#define T_BEGIN_1 ""
#define T_BEGIN_2 ""
#define T_BEGIN_3 ""
#define T_END_0 "finish"
#define T_END_1 ""
#define T_END_2 ""
#define T_END_3 ""
//
#define T_NULL_STATEMENT_0 "NULL"
#define T_NULL_STATEMENT_1 "STATEMENT"
#define T_NULL_STATEMENT_2 ""
#define T_NULL_STATEMENT_3 ""


#ifndef TOKEN_STRUCT_NAME_
#define TOKEN_STRUCT_NAME_
DECLENUM(TokenStructName,
	MULTI_TOKEN_BITWISE_NOT,
	MULTI_TOKEN_BITWISE_AND,
	MULTI_TOKEN_BITWISE_OR,
	MULTI_TOKEN_NOT,
	MULTI_TOKEN_AND,
	MULTI_TOKEN_OR,

	MULTI_TOKEN_EQUAL,
	MULTI_TOKEN_NOT_EQUAL,
	MULTI_TOKEN_LESS,
	MULTI_TOKEN_GREATER,
	MULTI_TOKEN_LESS_OR_EQUAL,
	MULTI_TOKEN_GREATER_OR_EQUAL,

	MULTI_TOKEN_ADD,
	MULTI_TOKEN_SUB,
	MULTI_TOKEN_MUL,
	MULTI_TOKEN_DIV,
	MULTI_TOKEN_MOD,

	MULTI_TOKEN_BIND_RIGHT_TO_LEFT,
	MULTI_TOKEN_BIND_LEFT_TO_RIGHT,

	MULTI_TOKEN_COLON,
	MULTI_TOKEN_GOTO,

	MULTI_TOKEN_IF,
	//	MULTI_TOKEN_IF_, // don't change this!
	MULTI_TOKEN_THEN,
	//	MULTI_TOKEN_THEN_, // don't change this!
	MULTI_TOKEN_ELSE,

	MULTI_TOKEN_FOR,
	MULTI_TOKEN_TO,
	MULTI_TOKEN_DOWNTO,
	MULTI_TOKEN_DO,

	//
	MULTI_TOKEN_WHILE,
	/*while special statement*/MULTI_TOKEN_CONTINUE_WHILE,
	/*while special statement*/MULTI_TOKEN_EXIT_WHILE,
	MULTI_TOKEN_END_WHILE,
	//

	//
	MULTI_TOKEN_REPEAT,
	MULTI_TOKEN_UNTIL,
	//

	//
	MULTI_TOKEN_INPUT,
	MULTI_TOKEN_OUTPUT,
	//

	//
	MULTI_TOKEN_RLBIND,
	MULTI_TOKEN_LRBIND,
	//

	MULTI_TOKEN_SEMICOLON,

	MULTI_TOKEN_BEGIN,
	MULTI_TOKEN_END,

	//

	MULTI_TOKEN_NULL_STATEMENT
);

//#define PROCESS_TOKENS(...) HANDLE_TOKENS(__VA_ARGS__)
//#define TOKENS_FOR_MULTI_TOKEN(A, B, C, D) A, B, C, D
//#define TOKENS_FOR_MULTI_TOKEN_BITWISE_NOT TOKENS_FOR_MULTI_TOKEN("~", "", "", "")
#define INIT_TOKEN_STRUCT_NAME() static void intitTokenStruct(){\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BITWISE_NOT)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BITWISE_AND)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BITWISE_OR)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, NOT)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, AND)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, OR)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, EQUAL)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, NOT_EQUAL)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LESS)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, GREATER)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LESS_OR_EQUAL)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, GREATER_OR_EQUAL)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, ADD)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, SUB)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, MUL)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, DIV)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, MOD)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BIND_RIGHT_TO_LEFT)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BIND_LEFT_TO_RIGHT)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, COLON)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, GOTO)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, IF)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, THEN)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, ELSE)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, FOR)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, TO)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, DOWNTO)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, DO)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, WHILE)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, CONTINUE_WHILE)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, EXIT_WHILE)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, END_WHILE)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, REPEAT)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, UNTIL)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, INPUT)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, OUTPUT)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, RLBIND)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LRBIND)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, SEMICOLON)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BEGIN)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, END)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, NULL_STATEMENT)\
} char intitTokenStruct_ = (intitTokenStruct(), 0);
#define MAX_TOKEN_STRUCT_ELEMENT_COUNT GET_ENUM_SIZE(TokenStructName)
#define MAX_TOKEN_STRUCT_ELEMENT_PART_COUNT 4
#endif

extern char* tokenStruct[MAX_TOKEN_STRUCT_ELEMENT_COUNT][MAX_TOKEN_STRUCT_ELEMENT_PART_COUNT];

#define CONFIGURABLE_GRAMMAR {\
        {"labeled_point", 2, {"ident", "tokenCOLON"}},\
        {"goto_label", 2, {"tokenGOTO","ident"}},\
        {"program_name", 1, {"ident_terminal"}},\
        {"value_type", 1, {T_DATA_TYPE_0}},\
        {"other_declaration_ident", 2, {"tokenCOMMA", "ident"}},\
        {"other_declaration_ident____iteration_after_one", 2, {"other_declaration_ident","other_declaration_ident____iteration_after_one"}},\
        {"other_declaration_ident____iteration_after_one", 2, {"tokenCOMMA", "ident"}},\
        {"value_type__ident", 2, {"value_type", "ident"}},\
        {"declaration", 2, {"value_type__ident", "other_declaration_ident____iteration_after_one"}},\
        {"declaration", 2, {"value_type", "ident"}},\
\
        {"unary_operator", 1, {T_NOT_0}},\
        {"unary_operator", 1, {T_SUB_0}},\
        {"unary_operator", 1, {T_ADD_0}},\
        {"binary_operator", 1, {T_AND_0}},\
        {"binary_operator", 1, {T_OR_0}},\
        {"binary_operator", 1, {T_EQUAL_0}},\
        {"binary_operator", 1, {T_NOT_EQUAL_0}},\
        {"binary_operator", 1, {T_LESS_OR_EQUAL_0}},\
        {"binary_operator", 1, {T_GREATER_OR_EQUAL_0}},\
        {"binary_operator", 1, {T_ADD_0}},\
        {"binary_operator", 1, {T_SUB_0}},\
        {"binary_operator", 1, {T_MUL_0}},\
        {"binary_operator", 1, {T_DIV_0}},\
        {"binary_operator", 1, {T_MOD_0}},\
        {"binary_action", 2, {"binary_operator","expression"}},\
\
        {"left_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},\
        {"left_expression", 2, {"unary_operator","expression"}},\
        {"left_expression", 1, {"ident_terminal"}},\
        {"left_expression", 1, {"value_terminal"}},\
        {"binary_action____iteration_after_two", 2, {"binary_action","binary_action____iteration_after_two"}},\
        {"binary_action____iteration_after_two", 2, {"binary_action","binary_action"}},\
        {"expression", 2, {"left_expression","binary_action____iteration_after_two"}},\
        {"expression", 2, {"left_expression","binary_action"}},\
        {"expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},\
        {"expression", 2, {"unary_operator","expression"}},\
        {"expression", 1, {"ident_terminal"}},\
        {"expression", 1, {"value_terminal"}},\
\
        {"tokenGROUPEXPRESSIONBEGIN__expression", 2, {"tokenGROUPEXPRESSIONBEGIN","expression"}},\
        {"group_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},\
\
        {"bind_right_to_left", 2, {"ident","rl_expression"}},\
        {"bind_left_to_right", 2, {"lr_expression","ident"}},\
\
        {"body_for_true", 2, {"statement_in_while_body____iteration_after_two","tokenSEMICOLON"}},\
        {"body_for_true", 2, {"statement_in_while_body","tokenSEMICOLON"}},\
        {"body_for_true", 1, {T_SEMICOLON_0}},\
        {"tokenELSE__statement_in_while_body", 2, {"tokenELSE","statement_in_while_body"}},\
        {"tokenELSE__statement_in_while_body____iteration_after_two", 2, {"tokenELSE","statement_in_while_body____iteration_after_two"}},\
        {"body_for_false", 2, {"tokenELSE__statement_in_while_body____iteration_after_two","tokenSEMICOLON"}},\
        {"body_for_false", 2, {"tokenELSE__statement_in_while_body","tokenSEMICOLON"}},\
        {"body_for_false", 2, {"tokenELSE","tokenSEMICOLON"}},\
        {"tokenIF__tokenGROUPEXPRESSIONBEGIN", 2, {"tokenIF","tokenGROUPEXPRESSIONBEGIN"}},\
        {"expression__tokenGROUPEXPRESSIONEND", 2, {"expression","tokenGROUPEXPRESSIONEND"}},\
        {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN","expression__tokenGROUPEXPRESSIONEND"}},\
        {"body_for_true__body_for_false", 2, {"body_for_true","body_for_false"}},\
        {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},\
        {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},\
\
        {"cycle_counter", 1, {"ident_terminal"}},\
        {"rl_expression", 2, {"tokenRLBIND","expression"}},\
        {"lr_expression", 2, {"expression","tokenLRBIND"}},\
        {"cycle_counter_init", 2, {"cycle_counter","rl_expression"}},\
        {"cycle_counter_init", 2, {"lr_expression","cycle_counter"}},\
        {"cycle_counter_last_value", 1, {"value_terminal"}},\
        {"cycle_body", 2, {"tokenDO","statement____iteration_after_two"}},\
        {"cycle_body", 2, {"tokenDO","statement"}},\
        {"tokenFOR__cycle_counter_init", 2, {"tokenFOR","cycle_counter_init"}},\
        {"tokenTO__cycle_counter_last_value", 2, {"tokenTO","cycle_counter_last_value"}},\
        {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value", 2, {"tokenFOR__cycle_counter_init","tokenTO__cycle_counter_last_value"}},\
        {"cycle_body__tokenSEMICOLON", 2, {"cycle_body","tokenSEMICOLON"}},\
        {"forto_cycle", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},\
\
        {"continue_while", 2, {"tokenCONTINUE","tokenWHILE"}},\
        {"exit_while", 2, {"tokenEXIT","tokenWHILE"}},\
        {"tokenWHILE__expression", 2, {"tokenWHILE","expression"}},\
        {"tokenEND__tokenWHILE", 2, {"tokenEND","tokenWHILE"}},\
        {"tokenWHILE__expression__statement_in_while_body", 2, {"tokenWHILE__expression","statement_in_while_body"}},\
        {"tokenWHILE__expression__statement_in_while_body____iteration_after_two", 2, {"tokenWHILE__expression","statement_in_while_body____iteration_after_two"}},\
        {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"}},\
        {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},\
        {"while_cycle", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},\
\
        {"tokenUNTIL__expression", 2, {"tokenUNTIL","expression"}},\
        {"tokenREPEAT__statement____iteration_after_two", 2, {"tokenREPEAT","statement____iteration_after_two"}},\
        {"tokenREPEAT__statement", 2, {"tokenREPEAT","statement"}},\
        {"repeat_until_cycle", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},\
        {"repeat_until_cycle", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},\
        {"repeat_until_cycle", 2, {"tokenREPEAT","tokenUNTIL__expression"}},\
\
        {"input__first_part", 2, {"tokenGET","tokenGROUPEXPRESSIONBEGIN"}},\
        {"input__second_part", 2, {"ident","tokenGROUPEXPRESSIONEND"}},\
        {"input", 2, {"input__first_part","input__second_part"}},\
\
        {"output__first_part", 2, {"tokenPUT","tokenGROUPEXPRESSIONBEGIN"}},\
        {"output__second_part", 2, {"expression","tokenGROUPEXPRESSIONEND"}},\
        {"output", 2, {"output__first_part","output__second_part"}},\
\
        {"statement", 2, {"ident","rl_expression"}},\
        {"statement", 2, {"lr_expression","ident"}},\
        {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},\
        {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},\
        {"statement", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},\
        {"statement", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"}},\
        {"statement", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},\
        {"statement", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},\
        {"statement", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},\
        {"statement", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},\
        {"statement", 2, {"tokenREPEAT","tokenUNTIL__expression"}},\
        {"statement", 2, {"ident","tokenCOLON"}},\
        {"statement", 2, {"tokenGOTO","ident"}},\
        {"statement", 2, {"input__first_part","input__second_part"}},\
        {"statement", 2, {"output__first_part","output__second_part"}},\
        {"statement____iteration_after_two", 2, {"statement","statement____iteration_after_two"}},\
        {"statement____iteration_after_two", 2, {"statement","statement"}},\
\
        { "statement_in_while_body", 2, {"ident","rl_expression"}},\
        { "statement_in_while_body", 2, {"lr_expression","ident"}},\
        { "statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},\
        { "statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},\
        { "statement_in_while_body", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},\
        { "statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"}},\
        { "statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},\
        { "statement_in_while_body", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},\
        { "statement_in_while_body", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},\
        { "statement_in_while_body", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},\
        { "statement_in_while_body", 2, {"tokenREPEAT","tokenUNTIL__expression"}},\
        { "statement_in_while_body", 2, {"ident","tokenCOLON"}},\
        { "statement_in_while_body", 2, {"tokenGOTO","ident"}},\
        { "statement_in_while_body", 2, {"input__first_part","input__second_part"}},\
        { "statement_in_while_body", 2, {"output__first_part","output__second_part"}},\
        { "statement_in_while_body", 2, {"tokenCONTINUE","tokenWHILE"}},\
        { "statement_in_while_body", 2, {"tokenEXIT","tokenWHILE"}},\
        { "statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body____iteration_after_two"}},\
        { "statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body"}},\
\
        PROGRAM_FORMAT\
\
        {"tokenCOLON", 1, {T_COLON_0}},\
        {"tokenGOTO", 1, {T_GOTO_0}},\
        {"tokenINTEGER16", 1, {T_DATA_TYPE_0}},\
        {"tokenCOMMA", 1, {T_COMA_0}},\
        {"tokenNOT", 1, {T_NOT_0}},\
        {"tokenAND", 1, {T_AND_0}},\
        {"tokenOR", 1, {T_OR_0}},\
        {"tokenEQUAL", 1, {T_EQUAL_0}},\
        {"tokenNOTEQUAL", 1, {T_NOT_EQUAL_0}},\
        {"tokenLESSOREQUAL", 1, {T_LESS_OR_EQUAL_0}},\
        {"tokenGREATEROREQUAL", 1, {T_GREATER_OR_EQUAL_0}},\
        {"tokenPLUS", 1, {T_ADD_0}},\
        {"tokenMINUS", 1, {T_SUB_0}},\
        {"tokenMUL", 1, {T_MUL_0}},\
        {"tokenDIV", 1, {T_DIV_0}},\
        {"tokenMOD", 1, {T_MOD_0}},\
        {"tokenGROUPEXPRESSIONBEGIN", 1, {"("}},\
        {"tokenGROUPEXPRESSIONEND", 1, {")"}},\
        {"tokenRLBIND", 1, {T_RLBIND_0}},\
        {"tokenLRBIND", 1, {T_LRBIND_0}},\
        {"tokenELSE", 1, {T_ELSE_0}},\
        {"tokenIF", 1, {T_IF_0}},\
        {"tokenDO", 1, {T_DO_0}},\
        {"tokenFOR", 1, {T_FOR_0}},\
        {"tokenTO", 1, {T_TO_0}},\
        {"tokenWHILE", 1, {T_WHILE_0}},\
        {"tokenCONTINUE", 1, {T_CONTINUE_WHILE_0}},\
        {"tokenEXIT", 1, {T_EXIT_WHILE_0}},\
        {"tokenREPEAT", 1, {T_REPEAT_0}},\
        {"tokenUNTIL", 1, {T_UNTIL_0}},\
        {"tokenGET", 1, {T_INPUT_0}},\
        {"tokenPUT", 1, {T_OUTPUT_0}},\
        {"tokenNAME", 1, {T_NAME_0}},\
        {"tokenBODY", 1, {T_BODY_0}},\
        {"tokenDATA", 1, {T_DATA_0}},\
        {"tokenEND", 1, {T_END_0}},\
        {"tokenSEMICOLON", 1, {T_SEMICOLON_0}},\
\
        {"value", 1, {"value_terminal"}},\
\
        {"ident", 1, {"ident_terminal"}},\
\
        {"", 2, {"",""}}\
},\
176,\
"program"

#define ORIGINAL_GRAMMAR {\
    {"labeled_point", 2, {"ident", "tokenCOLON"}},\
    {"goto_label", 2, {"tokenGOTO","ident"}},\
    {"program_name", 1, {"ident_terminal"}},\
    {"value_type", 1, {"integer16"}},\
    {"other_declaration_ident", 2, {"tokenCOMMA", "ident"}},\
    {"other_declaration_ident____iteration_after_one", 2, {"other_declaration_ident","other_declaration_ident____iteration_after_one"}},\
    {"other_declaration_ident____iteration_after_one", 2, {"tokenCOMMA", "ident"}},\
    {"value_type__ident", 2, {"value_type", "ident"}},\
    {"declaration", 2, {"value_type__ident", "other_declaration_ident____iteration_after_one"}},\
    {"declaration", 2, {"value_type", "ident"}},\
\
    {"unary_operator", 1, {"not"}},\
    {"unary_operator", 1, {"sub"}},\
    {"unary_operator", 1, {"add"}},\
    {"binary_operator", 1, {"and"}},\
    {"binary_operator", 1, {"or"}},\
    {"binary_operator", 1, {"="}},\
    {"binary_operator", 1, {"<>"}},\
    {"binary_operator", 1, {"<"}},\
    {"binary_operator", 1, {">"}},\
    {"binary_operator", 1, {"add"}},\
    {"binary_operator", 1, {"sub"}},\
    {"binary_operator", 1, {"*"}},\
    {"binary_operator", 1, {"/"}},\
    {"binary_operator", 1, {"%"}},\
    {"binary_action", 2, {"binary_operator","expression"}},\
\
    {"left_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},\
    {"left_expression", 2, {"unary_operator","expression"}},\
    {"left_expression", 1, {"ident_terminal"}},\
    {"left_expression", 1, {"value_terminal"}},\
    {"binary_action____iteration_after_two", 2, {"binary_action","binary_action____iteration_after_two"}},\
    {"binary_action____iteration_after_two", 2, {"binary_action","binary_action"}},\
    {"expression", 2, {"left_expression","binary_action____iteration_after_two"}},\
    {"expression", 2, {"left_expression","binary_action"}},\
    {"expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},\
    {"expression", 2, {"unary_operator","expression"}},\
    {"expression", 1, {"ident_terminal"}},\
    {"expression", 1, {"value_terminal"}},\
\
    {"tokenGROUPEXPRESSIONBEGIN__expression", 2, {"tokenGROUPEXPRESSIONBEGIN","expression"}},\
    {"group_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},\
\
    {"bind_right_to_left", 2, {"ident","rl_expression"}},\
    {"bind_left_to_right", 2, {"lr_expression","ident"}},\
\
    {"body_for_true", 2, {"statement_in_while_body____iteration_after_two","tokenSEMICOLON"}},\
    {"body_for_true", 2, {"statement_in_while_body","tokenSEMICOLON"}},\
    {"body_for_true", 1, {";"}},\
    {"tokenELSE__statement_in_while_body", 2, {"tokenELSE","statement_in_while_body"}},\
    {"tokenELSE__statement_in_while_body____iteration_after_two", 2, {"tokenELSE","statement_in_while_body____iteration_after_two"}},\
    {"body_for_false", 2, {"tokenELSE__statement_in_while_body____iteration_after_two","tokenSEMICOLON"}},\
    {"body_for_false", 2, {"tokenELSE__statement_in_while_body","tokenSEMICOLON"}},\
    {"body_for_false", 2, {"tokenELSE","tokenSEMICOLON"}},\
    {"tokenIF__tokenGROUPEXPRESSIONBEGIN", 2, {"tokenIF","tokenGROUPEXPRESSIONBEGIN"}},\
    {"expression__tokenGROUPEXPRESSIONEND", 2, {"expression","tokenGROUPEXPRESSIONEND"}},\
    {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN","expression__tokenGROUPEXPRESSIONEND"}},\
    {"body_for_true__body_for_false", 2, {"body_for_true","body_for_false"}},\
    {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},\
    {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},\
\
    {"cycle_counter", 1, {"ident_terminal"}},\
    {"rl_expression", 2, {"tokenRLBIND","expression"}},\
    {"lr_expression", 2, {"expression","tokenLRBIND"}},\
    {"cycle_counter_init", 2, {"cycle_counter","rl_expression"}},\
    {"cycle_counter_init", 2, {"lr_expression","cycle_counter"}},\
    {"cycle_counter_last_value", 1, {"value_terminal"}},\
    {"cycle_body", 2, {"tokenDO","statement____iteration_after_two"}},\
    {"cycle_body", 2, {"tokenDO","statement"}},\
    {"tokenFOR__cycle_counter_init", 2, {"tokenFOR","cycle_counter_init"}},\
    {"tokenTO__cycle_counter_last_value", 2, {"tokenTO","cycle_counter_last_value"}},\
    {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value", 2, {"tokenFOR__cycle_counter_init","tokenTO__cycle_counter_last_value"}},\
    {"cycle_body__tokenSEMICOLON", 2, {"cycle_body","tokenSEMICOLON"}},\
    {"forto_cycle", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},\
\
    {"continue_while", 2, {"tokenCONTINUE","tokenWHILE"}},\
    {"exit_while", 2, {"tokenEXIT","tokenWHILE"}},\
    {"tokenWHILE__expression", 2, {"tokenWHILE","expression"}},\
    {"tokenEND__tokenWHILE", 2, {"tokenEND","tokenWHILE"}},\
    {"tokenWHILE__expression__statement_in_while_body", 2, {"tokenWHILE__expression","statement_in_while_body"}},\
    {"tokenWHILE__expression__statement_in_while_body____iteration_after_two", 2, {"tokenWHILE__expression","statement_in_while_body____iteration_after_two"}},\
    {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"}},\
    {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},\
    {"while_cycle", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},\
\
    {"tokenUNTIL__expression", 2, {"tokenUNTIL","expression"}},\
    {"tokenREPEAT__statement____iteration_after_two", 2, {"tokenREPEAT","statement____iteration_after_two"}},\
    {"tokenREPEAT__statement", 2, {"tokenREPEAT","statement"}},\
    {"repeat_until_cycle", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},\
    {"repeat_until_cycle", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},\
    {"repeat_until_cycle", 2, {"tokenREPEAT","tokenUNTIL__expression"}},\
 \
    {"input__first_part", 2, {"tokenGET","tokenGROUPEXPRESSIONBEGIN"}},\
    {"input__second_part", 2, {"ident","tokenGROUPEXPRESSIONEND"}},\
    {"input", 2, {"input__first_part","input__second_part"}},\
\
    {"output__first_part", 2, {"tokenPUT","tokenGROUPEXPRESSIONBEGIN"}},\
    {"output__second_part", 2, {"expression","tokenGROUPEXPRESSIONEND"}},\
    {"output", 2, {"output__first_part","output__second_part"}},\
\
    {"statement", 2, {"ident","rl_expression"}},\
    {"statement", 2, {"lr_expression","ident"}},\
    {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},\
    {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},\
    {"statement", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},\
    {"statement", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"}},\
    {"statement", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},\
    {"statement", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},\
    {"statement", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},\
    {"statement", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},\
    {"statement", 2, {"tokenREPEAT","tokenUNTIL__expression"}},\
    {"statement", 2, {"ident","tokenCOLON"}},\
    {"statement", 2, {"tokenGOTO","ident"}},\
    {"statement", 2, {"input__first_part","input__second_part"}},\
    {"statement", 2, {"output__first_part","output__second_part"}},\
    {"statement____iteration_after_two", 2, {"statement","statement____iteration_after_two"}},\
    {"statement____iteration_after_two", 2, {"statement","statement"}},\
\
    {"statement_in_while_body", 2, {"ident","rl_expression"}},\
    {"statement_in_while_body", 2, {"lr_expression","ident"}},\
    {"statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},\
    {"statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},\
    {"statement_in_while_body", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},\
    {"statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"}},\
    {"statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},\
    {"statement_in_while_body", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},\
    {"statement_in_while_body", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},\
    {"statement_in_while_body", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},\
    {"statement_in_while_body", 2, {"tokenREPEAT","tokenUNTIL__expression"}},\
    {"statement_in_while_body", 2, {"ident","tokenCOLON"}},\
    {"statement_in_while_body", 2, {"tokenGOTO","ident"}},\
    {"statement_in_while_body", 2, {"input__first_part","input__second_part"}},\
    {"statement_in_while_body", 2, {"output__first_part","output__second_part"}},\
    {"statement_in_while_body", 2, {"tokenCONTINUE","tokenWHILE"}},\
    {"statement_in_while_body", 2, {"tokenEXIT","tokenWHILE"}},\
    {"statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body____iteration_after_two"}},\
    {"statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body"}},\
\
    {"tokenNAME__program_name", 2, {"tokenNAME","program_name"}},\
    {"tokenSEMICOLON__tokenBODY", 2, {"tokenSEMICOLON","tokenBODY"}},\
    {"tokenDATA__declaration", 2, {"tokenDATA","declaration"}},\
    {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY", 2, {"tokenNAME__program_name","tokenSEMICOLON__tokenBODY"}},\
    {"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA__declaration"}},\
    {"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA"}},\
    {"statement__tokenEND", 2, {"statement","tokenEND"}},\
    {"statement____iteration_after_two__tokenEND", 2, {"statement____iteration_after_two","tokenEND"}},\
    {"program____part2", 2, {"tokenSEMICOLON","statement____iteration_after_two__tokenEND"}},\
    {"program____part2", 2, {"tokenSEMICOLON","statement__tokenEND"}},\
    {"program____part2", 2, {"tokenSEMICOLON","tokenEND"}},\
    {"program", 2, {"program____part1","program____part2"}},\
\
    {"tokenCOLON", 1, {":"}},\
    {"tokenGOTO", 1, {"goto"}},\
    {"tokenINTEGER16", 1, {"integer16"}},\
    {"tokenCOMMA", 1, {","}},\
    {"tokenNOT", 1, {"not"}},\
    {"tokenAND", 1, {"and"}},\
    {"tokenOR", 1, {"or"}},\
    {"tokenEQUAL", 1, {"="}},\
    {"tokenNOTEQUAL", 1, {"<>"}},\
    {"tokenLESSOREQUAL", 1, {"<"}},\
    {"tokenGREATEROREQUAL", 1, {">"}},\
    {"tokenPLUS", 1, {"add"}},\
    {"tokenMINUS", 1, {"sub"}},\
    {"tokenMUL", 1, {"*"}},\
    {"tokenDIV", 1, {"/"}},\
    {"tokenMOD", 1, {"%"}},\
    {"tokenGROUPEXPRESSIONBEGIN", 1, {"("}},\
    {"tokenGROUPEXPRESSIONEND", 1, {")"}},\
    {"tokenRLBIND", 1, {"<-"}},\
    {"tokenLRBIND", 1, {">>"}},\
    {"tokenELSE", 1, {"else"}},\
    {"tokenIF", 1, {"if"}},\
    {"tokenDO", 1, {"do"}},\
    {"tokenFOR", 1, {"for"}},\
    {"tokenTO", 1, {"to"}},\
    {"tokenWHILE", 1, {"while"}},\
    {"tokenCONTINUE", 1, {"continue"}},\
    {"tokenEXIT", 1, {"exit"}},\
    {"tokenREPEAT", 1, {"repeat"}},\
    {"tokenUNTIL", 1, {"until"}},\
    {"tokenGET", 1, {"scan"}},\
    {"tokenPUT", 1, {"print"}},\
    {"tokenNAME", 1, {"program"}},\
    {"tokenBODY", 1, {"start"}},\
    {"tokenDATA", 1, {"var"}},\
    {"tokenEND", 1, {"finish"}},\
    {"tokenSEMICOLON", 1, {";"}},\
\
    {"value", 1, {"value_terminal"}},\
\
    {"ident", 1, {"ident_terminal"}},\
\
    {"", 2, {"",""}}\
\
},\
176,\
"program"