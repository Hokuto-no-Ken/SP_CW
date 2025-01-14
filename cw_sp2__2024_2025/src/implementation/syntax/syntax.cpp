#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: syntax.cpp                  *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/config.h"
#include "../../include/syntax/syntax.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
//#include <unordered_map>
#include <string>
#include <set>

using namespace std;

Grammar grammar = {
    CONFIGURABLE_GRAMMAR
#if 0
    {
        {"labeled_point", 2, {"ident", "tokenCOLON"}}, // !!!!!
        {"goto_label", 2, {"tokenGOTO","ident"}},      // !!!!!
        {"program_name", 1, {"ident_terminal"}},
        {"value_type", 1, {T_DATA_TYPE_0}},
        {"other_declaration_ident", 2, {"tokenCOMMA", "ident"}},
        {"other_declaration_ident____iteration_after_one", 2, {"other_declaration_ident","other_declaration_ident____iteration_after_one", }},
        {"other_declaration_ident____iteration_after_one", 2, {"tokenCOMMA", "ident"}},
        {"value_type__ident", 2, {"value_type", "ident"}},
        {"declaration", 2, {"value_type__ident", "other_declaration_ident____iteration_after_one"}},
        {"declaration", 2, {"value_type", "ident"}},
        //
        {"unary_operator", 1, {T_NOT_0}},
        {"unary_operator", 1, {T_SUB_0}},
        {"unary_operator", 1, {T_ADD_0}},
        {"binary_operator", 1, {T_AND_0}},
        {"binary_operator", 1, {T_OR_0}},
        {"binary_operator", 1, {T_EQUAL_0}},
        {"binary_operator", 1, {T_NOT_EQUAL_0}},
        {"binary_operator", 1, {T_LESS_OR_EQUAL_0}},
        {"binary_operator", 1, {T_GREATER_OR_EQUAL_0}},
        {"binary_operator", 1, {T_ADD_0}},
        {"binary_operator", 1, {T_SUB_0}},
        {"binary_operator", 1, {T_MUL_0}},
        {"binary_operator", 1, {T_DIV_0}},
        {"binary_operator", 1, {T_MOD_0}},
        {"binary_action", 2, {"binary_operator","expression"}},
        //
        {"left_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},
        {"left_expression", 2, {"unary_operator","expression"}},
        {"left_expression", 1, {"ident_terminal"}},
        {"left_expression", 1, {"value_terminal"}},
        {"binary_action____iteration_after_two", 2, {"binary_action","binary_action____iteration_after_two"}},
        {"binary_action____iteration_after_two", 2, {"binary_action","binary_action"}},
        {"expression", 2, {"left_expression","binary_action____iteration_after_two"}},
        {"expression", 2, {"left_expression","binary_action"}},
        {"expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},
        {"expression", 2, {"unary_operator","expression"}},
        {"expression", 1, {"ident_terminal"}},
        {"expression", 1, {"value_terminal"}},
        //
        {"tokenGROUPEXPRESSIONBEGIN__expression", 2, {"tokenGROUPEXPRESSIONBEGIN","expression"}},
        {"group_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},
        //
        {"bind_right_to_left", 2, {"ident","rl_expression"}},
        {"bind_left_to_right", 2, {"lr_expression","ident"}},
        //
        {"body_for_true", 2, {"statement_in_while_body____iteration_after_two","tokenSEMICOLON"}},
        {"body_for_true", 2, {"statement_in_while_body","tokenSEMICOLON"}},
        {"body_for_true", 1, {T_SEMICOLON_0}},
        {"tokenELSE__statement_in_while_body", 2, {"tokenELSE","statement_in_while_body"}},
        {"tokenELSE__statement_in_while_body____iteration_after_two", 2, {"tokenELSE","statement_in_while_body____iteration_after_two"}},
        {"body_for_false", 2, {"tokenELSE__statement_in_while_body____iteration_after_two","tokenSEMICOLON"}},
        {"body_for_false", 2, {"tokenELSE__statement_in_while_body","tokenSEMICOLON"}},
        {"body_for_false", 2, {"tokenELSE","tokenSEMICOLON"}},
        {"tokenIF__tokenGROUPEXPRESSIONBEGIN", 2, {"tokenIF","tokenGROUPEXPRESSIONBEGIN"}},
        {"expression__tokenGROUPEXPRESSIONEND", 2, {"expression","tokenGROUPEXPRESSIONEND"}},
        {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN","expression__tokenGROUPEXPRESSIONEND"}},
        {"body_for_true__body_for_false", 2, {"body_for_true","body_for_false"}},
        {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},
        {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},
        //
        {"cycle_counter", 1, {"ident_terminal"}},
        {"rl_expression", 2, {"tokenRLBIND","expression"}},
        {"lr_expression", 2, {"expression","tokenLRBIND"}},
        {"cycle_counter_init", 2, {"cycle_counter","rl_expression"}},
        {"cycle_counter_init", 2, {"lr_expression","cycle_counter"}},
        {"cycle_counter_last_value", 1, {"value_terminal"}},
        {"cycle_body", 2, {"tokenDO","statement____iteration_after_two"}},
        {"cycle_body", 2, {"tokenDO","statement"}},
        {"tokenFOR__cycle_counter_init", 2, {"tokenFOR","cycle_counter_init"}},
        {"tokenTO__cycle_counter_last_value", 2, {"tokenTO","cycle_counter_last_value"}},
        {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value", 2, {"tokenFOR__cycle_counter_init","tokenTO__cycle_counter_last_value"}},
        {"cycle_body__tokenSEMICOLON", 2, {"cycle_body","tokenSEMICOLON"}},
        {"forto_cycle", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},
        //
        {"continue_while", 2, {"tokenCONTINUE","tokenWHILE"}},
        {"exit_while", 2, {"tokenEXIT","tokenWHILE"}},
        {"tokenWHILE__expression", 2, {"tokenWHILE","expression"}},
        {"tokenEND__tokenWHILE", 2, {"tokenEND","tokenWHILE"}},
        {"tokenWHILE__expression__statement_in_while_body", 2, {"tokenWHILE__expression","statement_in_while_body"}},
        {"tokenWHILE__expression__statement_in_while_body____iteration_after_two", 2, {"tokenWHILE__expression","statement_in_while_body____iteration_after_two"}},
        {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE "}},
        {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},
        {"while_cycle", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},
        //
        {"tokenUNTIL__expression", 2, {"tokenUNTIL","expression"}},
        {"tokenREPEAT__statement____iteration_after_two", 2, {"tokenREPEAT","statement____iteration_after_two"}},
        {"tokenREPEAT__statement", 2, {"tokenREPEAT","statement"}},
        {"repeat_until_cycle", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},
        {"repeat_until_cycle", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},
        {"repeat_until_cycle", 2, {"tokenREPEAT","tokenUNTIL__expression"}},
        //
        {"input__first_part", 2, {"tokenGET","tokenGROUPEXPRESSIONBEGIN"}},
        {"input__second_part", 2, {"ident","tokenGROUPEXPRESSIONEND"}},
        {"input", 2, {"input__first_part","input__second_part"}},
        //
        {"output__first_part", 2, {"tokenPUT","tokenGROUPEXPRESSIONBEGIN"}},
        {"output__second_part", 2, {"expression","tokenGROUPEXPRESSIONEND"}},
        {"output", 2, {"output__first_part","output__second_part"}},
        //
        {"statement", 2, {"ident","rl_expression"}},
        {"statement", 2, {"lr_expression","ident"}},
        {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},
        {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},
        {"statement", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},
        {"statement", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"}},
        {"statement", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},
        {"statement", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},
        {"statement", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},
        {"statement", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},
        {"statement", 2, {"tokenREPEAT","tokenUNTIL__expression"}},
        {"statement", 2, {"ident","tokenCOLON"}},
        {"statement", 2, {"tokenGOTO","ident"}},
        {"statement", 2, {"input__first_part","input__second_part"}},
        {"statement", 2, {"output__first_part","output__second_part"}},
        {"statement____iteration_after_two", 2, {"statement","statement____iteration_after_two"}},
        {"statement____iteration_after_two", 2, {"statement","statement"}},
        //
        { "statement_in_while_body", 2, {"ident","rl_expression"} },
        { "statement_in_while_body", 2, {"lr_expression","ident"} },
        { "statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"} },
        { "statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"} },
        { "statement_in_while_body", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"} },
        { "statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"} },
        { "statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"} },
        { "statement_in_while_body", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"} },
        { "statement_in_while_body", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"} },
        { "statement_in_while_body", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"} },
        { "statement_in_while_body", 2, {"tokenREPEAT","tokenUNTIL__expression"} },
        { "statement_in_while_body", 2, {"ident","tokenCOLON"} },
        { "statement_in_while_body", 2, {"tokenGOTO","ident"} },
        { "statement_in_while_body", 2, {"input__first_part","input__second_part"} },
        { "statement_in_while_body", 2, {"output__first_part","output__second_part"} },
        { "statement_in_while_body", 2, {"tokenCONTINUE","tokenWHILE"} },
        { "statement_in_while_body", 2, {"tokenEXIT","tokenWHILE"} },
        { "statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body____iteration_after_two"} },
        { "statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body"} },
        //
        {"tokenNAME__program_name", 2, {"tokenNAME","program_name"}},
        {"tokenSEMICOLON__tokenBODY", 2, {"tokenSEMICOLON","tokenBODY"}},
        {"tokenDATA__declaration", 2, {"tokenDATA","declaration"}},
        {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY", 2, {"tokenNAME__program_name","tokenSEMICOLON__tokenBODY"}},
        {"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA__declaration"}},
        {"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA"}},
        {"statement__tokenEND", 2, {"statement","tokenEND"}},
        {"statement____iteration_after_two__tokenEND", 2, {"statement____iteration_after_two","tokenEND"}},
        {"program____part2", 2, {"tokenSEMICOLON","statement____iteration_after_two__tokenEND"}},
        {"program____part2", 2, {"tokenSEMICOLON","statement__tokenEND"}},
        {"program____part2", 2, {"tokenSEMICOLON","tokenEND"}},
        {"program", 2, {"program____part1","program____part2"}},
        //
        {"tokenCOLON", 1, {T_COLON_0}},
        {"tokenGOTO", 1, {T_GOTO_0}},
        {"tokenINTEGER16", 1, {T_DATA_TYPE_0}},
        {"tokenCOMMA", 1, {T_COMA_0}},
        {"tokenNOT", 1, {T_NOT_0}},
        {"tokenAND", 1, {T_AND_0}},
        {"tokenOR", 1, {T_OR_0}},
        {"tokenEQUAL", 1, {T_EQUAL_0}},
        {"tokenNOTEQUAL", 1, {T_NOT_EQUAL_0}},
        {"tokenLESSOREQUAL", 1, {T_LESS_OR_EQUAL_0}},
        {"tokenGREATEROREQUAL", 1, {T_GREATER_OR_EQUAL_0}},
        {"tokenPLUS", 1, {T_ADD_0}},
        {"tokenMINUS", 1, {T_SUB_0}},
        {"tokenMUL", 1, {T_MUL_0}},
        {"tokenDIV", 1, {T_DIV_0}},
        {"tokenMOD", 1, {T_MOD_0}},
        {"tokenGROUPEXPRESSIONBEGIN", 1, {"("}},
        {"tokenGROUPEXPRESSIONEND", 1, {")"}},
        {"tokenRLBIND", 1, {T_RLBIND_0}},
        {"tokenLRBIND", 1, {T_LRBIND_0}},
        {"tokenELSE", 1, {T_ELSE_0}},
        {"tokenIF", 1, {T_IF_0}},
        {"tokenDO", 1, {T_DO_0}},
        {"tokenFOR", 1, {T_FOR_0}},
        {"tokenTO", 1, {T_TO_0}},
        {"tokenWHILE", 1, {T_WHILE_0}},
        {"tokenCONTINUE", 1, {T_CONTINUE_WHILE_0}},
        {"tokenEXIT", 1, {T_EXIT_WHILE_0}},
        {"tokenREPEAT", 1, {T_REPEAT_0}},
        {"tokenUNTIL", 1, {T_UNTIL_0}},
        {"tokenGET", 1, {T_INPUT_0}},
        {"tokenPUT", 1, {T_OUTPUT_0}},
        {"tokenNAME", 1, {T_NAME_0}},
        {"tokenBODY", 1, {T_BODY_0}},
        {"tokenDATA", 1, {T_DATA_0}},
        {"tokenEND", 1, {T_END_0}},
        {"tokenSEMICOLON", 1, {T_SEMICOLON_0}},
        //
        { "value", 1, {"value_terminal"} },
        //
        { "ident", 1, {"ident_terminal"} },
        //
//        { "label", 1, {"ident_terminal"} },
        //
        { "", 2, {"",""} }
    },
    176,
    "program"
#endif
};

Grammar originalGrammar = {
    ORIGINAL_GRAMMAR
#if 0
    {
        {"labeled_point", 2, {"ident", "tokenCOLON"}}, // !!!!!
        {"goto_label", 2, {"tokenGOTO","ident"}},      // !!!!!
        {"program_name", 1, {"ident_terminal"}},
        {"value_type", 1, {"integer16"}},
        {"other_declaration_ident", 2, {"tokenCOMMA", "ident"}},
        {"other_declaration_ident____iteration_after_one", 2, {"other_declaration_ident","other_declaration_ident____iteration_after_one", }},
        {"other_declaration_ident____iteration_after_one", 2, {"tokenCOMMA", "ident"}},
        {"value_type__ident", 2, {"value_type", "ident"}},
        {"declaration", 2, {"value_type__ident", "other_declaration_ident____iteration_after_one"}},
        {"declaration", 2, {"value_type", "ident"}},
        //
        {"unary_operator", 1, {"not"}},
        {"unary_operator", 1, {"sub"}},
        {"unary_operator", 1, {"add"}},
        {"binary_operator", 1, {"and"}},
        {"binary_operator", 1, {"or"}},
        {"binary_operator", 1, {"="}},
        {"binary_operator", 1, {"<>"}},
        {"binary_operator", 1, {"<"}},
        {"binary_operator", 1, {">"}},
        {"binary_operator", 1, {"add"}},
        {"binary_operator", 1, {"sub"}},
        {"binary_operator", 1, {"*"}},
        {"binary_operator", 1, {"/"}},
        {"binary_operator", 1, {"%"}},
        {"binary_action", 2, {"binary_operator","expression"}},
        //
        {"left_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},
        {"left_expression", 2, {"unary_operator","expression"}},
        {"left_expression", 1, {"ident_terminal"}},
        {"left_expression", 1, {"value_terminal"}},
        {"binary_action____iteration_after_two", 2, {"binary_action","binary_action____iteration_after_two"}},
        {"binary_action____iteration_after_two", 2, {"binary_action","binary_action"}},
        {"expression", 2, {"left_expression","binary_action____iteration_after_two"}},
        {"expression", 2, {"left_expression","binary_action"}},
        {"expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},
        {"expression", 2, {"unary_operator","expression"}},
        {"expression", 1, {"ident_terminal"}},
        {"expression", 1, {"value_terminal"}},
        //
        {"tokenGROUPEXPRESSIONBEGIN__expression", 2, {"tokenGROUPEXPRESSIONBEGIN","expression"}},
        {"group_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},
        //
        {"bind_right_to_left", 2, {"ident","rl_expression"}},
        {"bind_left_to_right", 2, {"lr_expression","ident"}},
        //
        {"body_for_true", 2, {"statement_in_while_body____iteration_after_two","tokenSEMICOLON"}},
        {"body_for_true", 2, {"statement_in_while_body","tokenSEMICOLON"}},
        {"body_for_true", 1, {";"}},
        {"tokenELSE__statement_in_while_body", 2, {"tokenELSE","statement_in_while_body"}},
        {"tokenELSE__statement_in_while_body____iteration_after_two", 2, {"tokenELSE","statement_in_while_body____iteration_after_two"}},
        {"body_for_false", 2, {"tokenELSE__statement_in_while_body____iteration_after_two","tokenSEMICOLON"}},
        {"body_for_false", 2, {"tokenELSE__statement_in_while_body","tokenSEMICOLON"}},
        {"body_for_false", 2, {"tokenELSE","tokenSEMICOLON"}},
        {"tokenIF__tokenGROUPEXPRESSIONBEGIN", 2, {"tokenIF","tokenGROUPEXPRESSIONBEGIN"}},
        {"expression__tokenGROUPEXPRESSIONEND", 2, {"expression","tokenGROUPEXPRESSIONEND"}},
        {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN","expression__tokenGROUPEXPRESSIONEND"}},
        {"body_for_true__body_for_false", 2, {"body_for_true","body_for_false"}},
        {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},
        {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},
        //
        {"cycle_counter", 1, {"ident_terminal"}},
        {"rl_expression", 2, {"tokenRLBIND","expression"}},
        {"lr_expression", 2, {"expression","tokenLRBIND"}},
        {"cycle_counter_init", 2, {"cycle_counter","rl_expression"}},
        {"cycle_counter_init", 2, {"lr_expression","cycle_counter"}},
        {"cycle_counter_last_value", 1, {"value_terminal"}},
        {"cycle_body", 2, {"tokenDO","statement____iteration_after_two"}},
        {"cycle_body", 2, {"tokenDO","statement"}},
        {"tokenFOR__cycle_counter_init", 2, {"tokenFOR","cycle_counter_init"}},
        {"tokenTO__cycle_counter_last_value", 2, {"tokenTO","cycle_counter_last_value"}},
        {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value", 2, {"tokenFOR__cycle_counter_init","tokenTO__cycle_counter_last_value"}},
        {"cycle_body__tokenSEMICOLON", 2, {"cycle_body","tokenSEMICOLON"}},
        {"forto_cycle", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},
        //
        {"continue_while", 2, {"tokenCONTINUE","tokenWHILE"}},
        {"exit_while", 2, {"tokenEXIT","tokenWHILE"}},
        {"tokenWHILE__expression", 2, {"tokenWHILE","expression"}},
        {"tokenEND__tokenWHILE", 2, {"tokenEND","tokenWHILE"}},
        {"tokenWHILE__expression__statement_in_while_body", 2, {"tokenWHILE__expression","statement_in_while_body"}},
        {"tokenWHILE__expression__statement_in_while_body____iteration_after_two", 2, {"tokenWHILE__expression","statement_in_while_body____iteration_after_two"}},
        {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE "}},
        {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},
        {"while_cycle", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},
        //
        {"tokenUNTIL__expression", 2, {"tokenUNTIL","expression"}},
        {"tokenREPEAT__statement____iteration_after_two", 2, {"tokenREPEAT","statement____iteration_after_two"}},
        {"tokenREPEAT__statement", 2, {"tokenREPEAT","statement"}},
        {"repeat_until_cycle", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},
        {"repeat_until_cycle", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},
        {"repeat_until_cycle", 2, {"tokenREPEAT","tokenUNTIL__expression"}},
        //
        {"input__first_part", 2, {"tokenGET","tokenGROUPEXPRESSIONBEGIN"}},
        {"input__second_part", 2, {"ident","tokenGROUPEXPRESSIONEND"}},
        {"input", 2, {"input__first_part","input__second_part"}},
        //
        {"output__first_part", 2, {"tokenPUT","tokenGROUPEXPRESSIONBEGIN"}},
        {"output__second_part", 2, {"expression","tokenGROUPEXPRESSIONEND"}},
        {"output", 2, {"output__first_part","output__second_part"}},
        //
        {"statement", 2, {"ident","rl_expression"}},
        {"statement", 2, {"lr_expression","ident"}},
        {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},
        {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},
        {"statement", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},
        {"statement", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"}},
        {"statement", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},
        {"statement", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},
        {"statement", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"}},
        {"statement", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"}},
        {"statement", 2, {"tokenREPEAT","tokenUNTIL__expression"}},
        {"statement", 2, {"ident","tokenCOLON"}},
        {"statement", 2, {"tokenGOTO","ident"}},
        {"statement", 2, {"input__first_part","input__second_part"}},
        {"statement", 2, {"output__first_part","output__second_part"}},
        {"statement____iteration_after_two", 2, {"statement","statement____iteration_after_two"}},
        {"statement____iteration_after_two", 2, {"statement","statement"}},
        //
        {"statement_in_while_body", 2, {"ident","rl_expression"} },
        {"statement_in_while_body", 2, {"lr_expression","ident"} },
        {"statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"} },
        {"statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"} },
        {"statement_in_while_body", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"} },
        {"statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"} },
        {"statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"} },
        {"statement_in_while_body", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"} },
        {"statement_in_while_body", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__expression"} },
        {"statement_in_while_body", 2, {"tokenREPEAT__statement","tokenUNTIL__expression"} },
        {"statement_in_while_body", 2, {"tokenREPEAT","tokenUNTIL__expression"} },
        {"statement_in_while_body", 2, {"ident","tokenCOLON"} },
        {"statement_in_while_body", 2, {"tokenGOTO","ident"} },
        {"statement_in_while_body", 2, {"input__first_part","input__second_part"} },
        {"statement_in_while_body", 2, {"output__first_part","output__second_part"} },
        {"statement_in_while_body", 2, {"tokenCONTINUE","tokenWHILE"} },
        {"statement_in_while_body", 2, {"tokenEXIT","tokenWHILE"} },
        {"statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body____iteration_after_two"} },
        {"statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body"} },
        //
        {"tokenNAME__program_name", 2, {"tokenNAME","program_name"}},
        {"tokenSEMICOLON__tokenBODY", 2, {"tokenSEMICOLON","tokenBODY"}},
        {"tokenDATA__declaration", 2, {"tokenDATA","declaration"}},
        {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY", 2, {"tokenNAME__program_name","tokenSEMICOLON__tokenBODY"}},
        {"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA__declaration"}},
        {"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA"}},
        {"statement__tokenEND", 2, {"statement","tokenEND"}},
        {"statement____iteration_after_two__tokenEND", 2, {"statement____iteration_after_two","tokenEND"}},
        {"program____part2", 2, {"tokenSEMICOLON","statement____iteration_after_two__tokenEND"}},
        {"program____part2", 2, {"tokenSEMICOLON","statement__tokenEND"}},
        {"program____part2", 2, {"tokenSEMICOLON","tokenEND"}},
        {"program", 2, {"program____part1","program____part2"}},
        //
        {"tokenCOLON", 1, {":"}},
        {"tokenGOTO", 1, {"goto"}},
        {"tokenINTEGER16", 1, {"integer16"}},
        {"tokenCOMMA", 1, {","}},
        {"tokenNOT", 1, {"not"}},
        {"tokenAND", 1, {"and"}},
        {"tokenOR", 1, {"or"}},
        {"tokenEQUAL", 1, {"="}},
        {"tokenNOTEQUAL", 1, {"<>"}},
        {"tokenLESSOREQUAL", 1, {"<"}},
        {"tokenGREATEROREQUAL", 1, {">"}},
        {"tokenPLUS", 1, {"add"}},
        {"tokenMINUS", 1, {"sub"}},
        {"tokenMUL", 1, {"*"}},
        {"tokenDIV", 1, {"/"}},
        {"tokenMOD", 1, {"%"}},
        {"tokenGROUPEXPRESSIONBEGIN", 1, {"("}},
        {"tokenGROUPEXPRESSIONEND", 1, {")"}},
        {"tokenRLBIND", 1, {"<-"}},
        {"tokenLRBIND", 1, {">>"}},
        {"tokenELSE", 1, {"else"}},
        {"tokenIF", 1, {"if"}},
        {"tokenDO", 1, {"do"}},
        {"tokenFOR", 1, {"for"}},
        {"tokenTO", 1, {"to"}},
        {"tokenWHILE", 1, {"while"}},
        {"tokenCONTINUE", 1, {"continue"}},
        {"tokenEXIT", 1, {"exit"}},
        {"tokenREPEAT", 1, {"repeat"}},
        {"tokenUNTIL", 1, {"until"}},
        {"tokenGET", 1, {"scan"}},
        {"tokenPUT", 1, {"print"}},
        {"tokenNAME", 1, {"program"}},
        {"tokenBODY", 1, {"start"}},
        {"tokenDATA", 1, {"var"}},
        {"tokenEND", 1, {"finish"}},
        {"tokenSEMICOLON", 1, {";"}},
        //
        { "value", 1, {"value_terminal"} },
        //
        { "ident", 1, {"ident_terminal"} },
        //
//        { "label", 1, {"ident_terminal"} },
        //
        { "", 2, {"",""} }
    },
    176,
    "program"
#endif
};


#define DEBUG_STATES

struct ASTNode {
    std::string value;
    bool isTerminal;
    std::vector<ASTNode*> children;

    ASTNode(const std::string& val, bool isTerminal) : isTerminal(isTerminal), value(val) {}
    ~ASTNode() {
        for (ASTNode* child : children) {
            delete child;
        }
    }
};

ASTNode* buildAST(const std::map<int, std::map<int, std::set<std::string>>>& parseInfoTable,
    Grammar* grammar,
    int start,
    int end,
    const std::string& symbol) {
    if (start > end) return nullptr;

    ASTNode* node = new ASTNode(symbol, false);

    for (const Rule& rule : grammar->rules) {
        if (rule.lhs != symbol) continue;

        if (rule.rhs_count == 1) {
            //if (parseInfoTable.at(start).at(end).count(rule.rhs[0])) {
            node->children.push_back(new ASTNode(rule.rhs[0], true));
            return node;
            //}
        }
        else if (rule.rhs_count == 2) {
            for (int split = start; split < end; ++split) {
                if (parseInfoTable.at(start).at(split).count(rule.rhs[0]) &&
                    parseInfoTable.at(split + 1).at(end).count(rule.rhs[1])) {
                    node->children.push_back(buildAST(parseInfoTable, grammar, start, split, rule.rhs[0]));
                    node->children.push_back(buildAST(parseInfoTable, grammar, split + 1, end, rule.rhs[1]));
                    return node;
                }
            }
        }
    }

    return nullptr;
}

void printAST(struct LexemInfo* lexemInfoTable, const ASTNode* node, int depth = 0) {
    static int lexemInfoTableIndexForPrintAST = 0; // ATTENTION: multithreading is not supported for this!
    if (!node) { 
        return; 
    }
    if (!depth) {
        lexemInfoTableIndexForPrintAST = 0;
    }

    for (unsigned int depthIndex = 0; depthIndex <= depth; ++depthIndex) {
        std::cout << "    " << "|";
    }

    std::cout << "--";
    if (node->isTerminal) {
        std::cout << "\"" << lexemInfoTable[lexemInfoTableIndexForPrintAST++].lexemStr << "\"";
    }   
    else {
        std::cout << node->value;
    }
    std::cout << "\n";

    for (const ASTNode* child : node->children) {
        printAST(lexemInfoTable, child, depth + 1);
    }
}

void printASTToFile(struct LexemInfo* lexemInfoTable, const ASTNode* node, std::ofstream& outFile, int depth = 0) {
    static int lexemInfoTableIndexForPrintAST = 0; // ATTENTION: multithreading is not supported for this!
    if (!node) {
        return;
    }
    if (!depth) {
        lexemInfoTableIndexForPrintAST = 0;
    }

    for (unsigned int depthIndex = 0; depthIndex <= depth; ++depthIndex) {
        outFile << "    |";
    }
    outFile << "--";

    if (node->isTerminal) {
        outFile << "\"" << lexemInfoTable[lexemInfoTableIndexForPrintAST++].lexemStr << "\"";
    }
    else {
        outFile << node->value;
    }
    outFile << "\n";

    for (const ASTNode* child : node->children) {
        printASTToFile(lexemInfoTable, child, outFile, depth + 1);
    }
}

void printAST__OLD_123(struct LexemInfo* lexemInfoTable, const ASTNode* node, int depth = 0) {
    static int lexemInfoTableIndexForPrintAST = 0; // ATTENTION: multithreading is not supported for this!
    if (!node) {
        return;
    }
    if (!depth) {
        lexemInfoTableIndexForPrintAST = 0;
    }
    for (unsigned int depthIndex = 0; depthIndex <= depth; ++depthIndex) {
        std::cout << "    " << "|";
    }
    std::cout << "--";
    if (node->isTerminal) {
        std::cout << "\"" << lexemInfoTable[lexemInfoTableIndexForPrintAST++].lexemStr << "\"";
    }
    else {
        std::cout << node->value;
    }
    std::cout << "\n";
    for (const ASTNode* child : node->children) {
        printAST(lexemInfoTable, child, depth + 1);
    }
}

void displayParseInfoTable(const map<int, map<int, set<string>>>& parseInfoTable) {
    constexpr int CELL_WIDTH = 128;

    cout << left << setw(CELL_WIDTH) << "[i\\j]";

    for (const auto& outerEntry : parseInfoTable) {
        cout << setw(CELL_WIDTH) << outerEntry.first;
    }
    cout << endl;

    for (const auto& outerEntry : parseInfoTable) {
        int i = outerEntry.first;
        cout << setw(CELL_WIDTH) << i;

        for (const auto& innerEntry : parseInfoTable) {
            int j = innerEntry.first;
            if (parseInfoTable.at(i).find(j) != parseInfoTable.at(i).end()) {
                const set<string>& rules = parseInfoTable.at(i).at(j);
                string cellContent;

                for (const string& rule : rules) {
                    cellContent += rule + ", ";
                }
                if (!cellContent.empty()) {
                    cellContent.pop_back();
                    cellContent.pop_back();
                }

                cout << setw(CELL_WIDTH) << cellContent;
            }
            else {
                cout << setw(CELL_WIDTH) << "sub";
            }
        }
        cout << endl;
    }
}

void saveParseInfoTableToFile(const map<int, map<int, set<string>>>& parseInfoTable, const string& filename) {
    constexpr int CELL_WIDTH = 128;

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    file << left << setw(CELL_WIDTH) << "[i\\j]";

    for (const auto& outerEntry : parseInfoTable) {
        file << setw(CELL_WIDTH) << outerEntry.first;
    }
    file << endl;

    for (const auto& outerEntry : parseInfoTable) {
        int i = outerEntry.first;
        file << setw(CELL_WIDTH) << i;

        for (const auto& innerEntry : parseInfoTable) {
            int j = innerEntry.first;
            if (parseInfoTable.at(i).find(j) != parseInfoTable.at(i).end()) {
                const set<string>& rules = parseInfoTable.at(i).at(j);
                string cellContent;

                for (const string& rule : rules) {
                    cellContent += rule + ", ";
                }
                if (!cellContent.empty()) {
                    cellContent.pop_back();
                    cellContent.pop_back();
                }

                file << setw(CELL_WIDTH) << cellContent;
            }
            else {
                file << setw(CELL_WIDTH) << "sub";
            }
        }
        file << endl;
    }

    file.close();
}

#define MAX_LEXEMS 256
//#define MAX_RULES 128
#define MAX_SYMBOLS 64

typedef struct {
    char symbols[MAX_SYMBOLS][MAX_TOKEN_SIZE];
    int count;
} SymbolSet;

typedef SymbolSet ParseInfoTable[MAX_LEXEMS][MAX_LEXEMS];

bool insertIntoSymbolSet(SymbolSet* set, const char* symbol) {
    for (int i = 0; i < set->count; ++i) {
        if (strcmp(set->symbols[i], symbol) == 0) {
            // symbol already exists
            return false; 
        }
    }
    strncpy(set->symbols[set->count], symbol, MAX_TOKEN_SIZE);
    set->symbols[set->count][MAX_TOKEN_SIZE - 1] = '\0';
    ++set->count;
    return true;
}

bool containsSymbolSet(const SymbolSet* set, const char* symbol) {
    for (int i = 0; i < set->count; ++i) {
        if (strcmp(set->symbols[i], symbol) == 0) {
            return true;
        }
    }
    return false;
}

// initialize with empty SymbolSets
ParseInfoTable parseInfoTable = { {{0}} };
bool cykAlgorithmImplementation(struct LexemInfo* lexemInfoTable, Grammar* grammar) {
    if (lexemInfoTable == NULL || grammar == NULL) {
        return false;
    }

#if defined(_DEBUG)
    printf("ATTENTION: for better performance, use Release mode!\r\n");
#endif

#ifndef DEBUG_STATES
    cout << "cykParse in progress.....[please wait]";
#else
    cout << "cykParse in progress.....[please wait]: ";
#endif

//    ParseInfoTable parseInfoTable = { {{0}} }; // Initialize with empty SymbolSets

    int lexemIndex = 0;
    for (--lexemIndex; lexemInfoTable[++lexemIndex].lexemStr[0];) {
#ifdef DEBUG_STATES
        printf("\rcykParse in progress.....[please wait]: %02d %16s", lexemIndex, lexemInfoTable[lexemIndex].lexemStr);
#endif

        // Iterate over the rules
        for (int xIndex = 0; xIndex < grammar->rule_count; ++xIndex) {
            Rule& rule = grammar->rules[xIndex];
            // If a terminal is found
            if (rule.rhs_count == 1 && (
                lexemInfoTable[lexemIndex].tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(rule.rhs[0], "ident_terminal")
                || lexemInfoTable[lexemIndex].tokenType == VALUE_LEXEME_TYPE && !strcmp(rule.rhs[0], "value_terminal")
                || !strncmp(rule.rhs[0], lexemInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)
                )) {
                insertIntoSymbolSet(&parseInfoTable[lexemIndex][lexemIndex], rule.lhs);
            }
        }
        for (int iIndex = lexemIndex; iIndex >= 0; --iIndex) {
            for (int kIndex = iIndex; kIndex <= lexemIndex; ++kIndex) {
                for (int xIndex = 0; xIndex < grammar->rule_count; ++xIndex) {
                    Rule& rule = grammar->rules[xIndex];
                    if (rule.rhs_count == 2
                        && containsSymbolSet(&parseInfoTable[iIndex][kIndex], rule.rhs[0])
                        && containsSymbolSet(&parseInfoTable[kIndex + 1][lexemIndex], rule.rhs[1])
                        ) {
                        insertIntoSymbolSet(&parseInfoTable[iIndex][lexemIndex], rule.lhs);
                    }
                }
            }
        }
    }

    cout << "\r" << "cykParse complete........[     ok    ]\n";

    return containsSymbolSet(&parseInfoTable[0][lexemIndex - 1], grammar->start_symbol);
}

#define MAX_STACK_DEPTH 256

bool recursiveDescentParserRuleWithDebug(const char* ruleName, int& lexemIndex, LexemInfo* lexemInfoTable, Grammar* grammar, int depth, const struct LexemInfo** unexpectedLexemfailedTerminal) {
    if (depth > MAX_STACK_DEPTH) {
        printf("Error: Maximum recursion depth reached.\n");
        return false;
    }
    char isError = false;
    for (int i = 0; i < grammar->rule_count; ++i) {
        Rule& rule = grammar->rules[i];
        if (strcmp(rule.lhs, ruleName) != 0) continue;

        int savedIndex = lexemIndex;
        if (rule.rhs_count == 1) {
            if (
                lexemInfoTable[lexemIndex].tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(rule.rhs[0], "ident_terminal")
                || lexemInfoTable[lexemIndex].tokenType == VALUE_LEXEME_TYPE && !strcmp(rule.rhs[0], "value_terminal")
                || !strncmp(rule.rhs[0], lexemInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)
                ) {
                ++lexemIndex;
                return true;
            }
            else {
                *unexpectedLexemfailedTerminal = lexemInfoTable + lexemIndex;
                if (0)printf("<< \"%s\" >>\n", rule.rhs[0]);
            }
        }
        else if (rule.rhs_count == 2) {
            if (recursiveDescentParserRuleWithDebug(rule.rhs[0], lexemIndex, lexemInfoTable, grammar, depth + 1, unexpectedLexemfailedTerminal) &&
                recursiveDescentParserRuleWithDebug(rule.rhs[1], lexemIndex, lexemInfoTable, grammar, depth + 1, unexpectedLexemfailedTerminal)) {
                return true;
            }
        }
        lexemIndex = savedIndex;
    }

    return false;
}

const LexemInfo* recursiveDescentParserWithDebug_(const char* ruleName, int& lexemIndex, LexemInfo* lexemInfoTable, Grammar* grammar, int depth, const struct LexemInfo* unexpectedUnknownLexemfailedTerminal) {
    if (depth > MAX_STACK_DEPTH) {
        printf("Error: Maximum recursion depth reached.\n");
        return unexpectedUnknownLexemfailedTerminal;
    }
    char isError = false;
    const LexemInfo* currUnexpectedLexemfailedTerminalPtr = nullptr, * returnUnexpectedLexemfailedTerminalPtr = nullptr;
    for (int i = 0; i < grammar->rule_count; ++i) {
        Rule& rule = grammar->rules[i];
        if (strcmp(rule.lhs, ruleName) != 0) continue;

        int savedIndex = lexemIndex;
        if (rule.rhs_count == 1) {
            if (
                lexemInfoTable[lexemIndex].tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(rule.rhs[0], "ident_terminal")
                || lexemInfoTable[lexemIndex].tokenType == VALUE_LEXEME_TYPE && !strcmp(rule.rhs[0], "value_terminal")
                || !strncmp(rule.rhs[0], lexemInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)
                ) {
                ++lexemIndex;
                return nullptr;
            }
            else {              
                currUnexpectedLexemfailedTerminalPtr = lexemInfoTable + lexemIndex;
            }
        }
        else if (rule.rhs_count == 2) {
            if (nullptr == (returnUnexpectedLexemfailedTerminalPtr = recursiveDescentParserWithDebug_(rule.rhs[0], lexemIndex, lexemInfoTable, grammar, depth + 1, unexpectedUnknownLexemfailedTerminal))  
                && nullptr == (returnUnexpectedLexemfailedTerminalPtr = recursiveDescentParserWithDebug_(rule.rhs[1], lexemIndex, lexemInfoTable, grammar, depth + 1, unexpectedUnknownLexemfailedTerminal))) {
                return nullptr;
            }
        }
        lexemIndex = savedIndex;
    }

    if (returnUnexpectedLexemfailedTerminalPtr != nullptr && returnUnexpectedLexemfailedTerminalPtr != unexpectedUnknownLexemfailedTerminal
        &&( returnUnexpectedLexemfailedTerminalPtr->tokenType == IDENTIFIER_LEXEME_TYPE
            || returnUnexpectedLexemfailedTerminalPtr->tokenType == VALUE_LEXEME_TYPE
            || returnUnexpectedLexemfailedTerminalPtr->tokenType == KEYWORD_LEXEME_TYPE
        )) {
        return returnUnexpectedLexemfailedTerminalPtr;
    }

    if (currUnexpectedLexemfailedTerminalPtr != nullptr) {
        return currUnexpectedLexemfailedTerminalPtr;
    }

    if(returnUnexpectedLexemfailedTerminalPtr != nullptr){
        return returnUnexpectedLexemfailedTerminalPtr;
    }

    return unexpectedUnknownLexemfailedTerminal;
}

//

bool syntaxAnalyze(LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode) {
    bool cykAlgorithmImplementationReturnValue = false;
    if (syntaxlAnalyzeMode == SYNTAX_ANALYZE_BY_CYK_ALGORITHM) {
        cykAlgorithmImplementationReturnValue = cykAlgorithmImplementation(lexemesInfoTable, grammar);
        printf("cykAlgorithmImplementation return \"%s\".\r\n", cykAlgorithmImplementationReturnValue ? "true" : "false");  
        if (cykAlgorithmImplementationReturnValue) {
            return true;
        }
    }

    if (cykAlgorithmImplementationReturnValue == false || syntaxlAnalyzeMode == SYNTAX_ANALYZE_BY_RECURSIVE_DESCENT) {
        int lexemIndex = 0;
        const struct LexemInfo* unexpectedLexemfailedTerminal = nullptr;

        if (recursiveDescentParserRuleWithDebug(grammar->start_symbol, lexemIndex, lexemInfoTable, grammar, 0, &unexpectedLexemfailedTerminal)) {
            if (lexemInfoTable[lexemIndex].lexemStr[0] == '\0') {
                printf("Parse successful.\n");
                printf("%d.\n", lexemIndex);
                return true;
            }
            else {
                printf("Parse failed: Extra tokens remain.\n");
                return false;
            }
        }
        else {
            if (unexpectedLexemfailedTerminal) {
                printf("Parse failed.\r\n");
                printf("    (The predicted terminal does not match the expected one.\r\n    Possible unexpected terminal \"%s\" on line %lld at position %lld\r\n    ..., but this is not certain.)\r\n", unexpectedLexemfailedTerminal->lexemStr, unexpectedLexemfailedTerminal->row, unexpectedLexemfailedTerminal->col);
            }
            else {
                printf("Parse failed: unexpected terminal.\r\n");
            }
            return false;
        }
        return false;
    }

    return false;
}

bool syntaxlAnalyze_(LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode) {
    bool cykAlgorithmImplementationReturnValue = false;
    if (syntaxlAnalyzeMode == SYNTAX_ANALYZE_BY_CYK_ALGORITHM) {
        bool cykAlgorithmImplementationReturnValue = cykAlgorithmImplementation(lexemesInfoTable, grammar);

        printf("cykAlgorithmImplementation return \"%s\".\r\n", cykAlgorithmImplementationReturnValue ? "true" : "false");
    }

    if (cykAlgorithmImplementationReturnValue && syntaxlAnalyzeMode == SYNTAX_ANALYZE_BY_RECURSIVE_DESCENT) {
        int lexemIndex = 0;
        const struct LexemInfo unexpectedUnknownLexemfailedTerminal("unknown", 0, 0, 0, ~0, ~0); //
        const struct LexemInfo* returnUnexpectedLexemfailedTerminal = nullptr;

        if (nullptr == (returnUnexpectedLexemfailedTerminal = recursiveDescentParserWithDebug_(grammar->start_symbol, lexemIndex, lexemInfoTable, grammar, 0, &unexpectedUnknownLexemfailedTerminal))) {
            if (lexemInfoTable[lexemIndex].lexemStr[0] == '\0') {
                printf("Parse successful.\n");
                printf("%d.\n", lexemIndex);
                return true;
            }
            else {
                printf("Parse failed: Extra tokens remain.\n");
                return false;
            }
        }
        else {
            if (returnUnexpectedLexemfailedTerminal->lexemStr[1]) {
                printf("Parse failed.\r\n");
                printf("    (The predicted terminal does not match the expected one.\r\n    Possible unexpected terminal \"%s\" on line %lld at position %lld\r\n    ..., but this is not certain.)\r\n", returnUnexpectedLexemfailedTerminal->lexemStr, returnUnexpectedLexemfailedTerminal->row, returnUnexpectedLexemfailedTerminal->col);
            }
            else {
                printf("Parse failed: unexpected terminal.\r\n");
            }
            return false;
        }
        return false;
    }

    return false;
}


// OLD //
bool cykAlgorithmImplementationByCPPMap(struct LexemInfo* lexemInfoTable, Grammar* grammar) {
    if (lexemInfoTable == NULL || grammar == NULL) {
        return false;
    }

#if defined(_DEBUG)
    printf("ATTENTION: for better performance, use Release mode!\r\n");
#endif

#ifndef DEBUG_STATES
    cout << "cykParse in progress.....[please wait]";
#else
    cout << "cykParse in progress.....[please wait]: ";
#endif

    map<int, map<int, set<string>>> parseInfoTable;

    int lexemIndex = 0;
    for (--lexemIndex; lexemInfoTable[++lexemIndex].lexemStr[0];) {
#ifdef DEBUG_STATES
        printf("\rcykParse in progress.....[please wait]: %02d %16s", lexemIndex, lexemInfoTable[lexemIndex].lexemStr);
#endif

        // Iterate over the rules
        for (int xIndex = 0; xIndex < grammar->rule_count; ++xIndex) {
            string&& lhs = grammar->rules[xIndex].lhs;
            Rule& rule = grammar->rules[xIndex];
            // If a terminal is found
            if (rule.rhs_count == 1 && (
                lexemInfoTable[lexemIndex].tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(rule.rhs[0], "ident_terminal")
                || lexemInfoTable[lexemIndex].tokenType == VALUE_LEXEME_TYPE && !strcmp(rule.rhs[0], "value_terminal")
                || !strncmp(rule.rhs[0], lexemInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)
                )) {
                parseInfoTable[lexemIndex][lexemIndex].insert(lhs);
            }
        }
        for (int iIndex = lexemIndex; iIndex >= 0; --iIndex) {
            for (int kIndex = iIndex; kIndex <= lexemIndex; ++kIndex) {
                for (int xIndex = 0; xIndex < grammar->rule_count; ++xIndex) {
                    string&& lhs = grammar->rules[xIndex].lhs;
                    Rule& rule = grammar->rules[xIndex];
                    if (rule.rhs_count == 2
                        && parseInfoTable[iIndex][kIndex].find(rule.rhs[0]) != parseInfoTable[iIndex][kIndex].end()
                        && parseInfoTable[kIndex + 1][lexemIndex].find(rule.rhs[1]) != parseInfoTable[kIndex + 1][lexemIndex].end()
                        ) {
                        parseInfoTable[iIndex][lexemIndex].insert(lhs);
                    }
                }
            }
        }
    }

    cout << "\r" << "cykParse complete........[     ok    ]\n";

    if (parseInfoTable[0][lexemIndex - 1].find(grammar->start_symbol) == parseInfoTable[0][lexemIndex - 1].end()) {
        return false;
    }

//    parseByRecursiveDescent_(lexemInfoTable, grammar);
    //    displayParseInfoTable(parseInfoTable);
    //    saveParseInfoTableToFile(parseInfoTable, "parseInfoTable.txt");

    ASTNode* astRoot = buildAST(parseInfoTable, grammar, 0, lexemIndex - 1, grammar->start_symbol);
    if (astRoot) {
        std::cout << "Abstract Syntax Tree:\n";
        printAST(lexemInfoTable, astRoot);
        delete astRoot; // Не забуваємо звільняти пам'ять
    }
    else {
        std::cout << "Failed to build AST.\n";
    }

    //return parseInfoTable[0][lexemIndex - 1].find(grammar->start_symbol) != parseInfoTable[0][lexemIndex - 1].end(); // return !!parseInfoTable[0][lexemIndex - 1].size();
    return true;
}

#if 0
bool parseByRecursiveDescent(LexemInfo* lexemInfoTable, Grammar* grammar) {
    int lexemIndex = 0;
    const struct LexemInfo* unexpectedLexemfailedTerminal = nullptr;

    if (recursiveDescentParserRuleWithDebug(grammar->start_symbol, lexemIndex, lexemInfoTable, grammar, 0, &unexpectedLexemfailedTerminal)) {
        if (lexemInfoTable[lexemIndex].lexemStr[0] == '\0') {
            printf("Parse successful.\n");
            printf("%d.\n", lexemIndex);
            return true;
        }
        else {
            printf("Parse failed: Extra tokens remain.\n");
            exit(0);
        }
    }
    else {
        if (unexpectedLexemfailedTerminal) {
            printf("Parse failed in line.\r\n");
            printf("    (The predicted terminal does not match the expected one.\r\n    Possible unexpected terminal \"%s\" on line %lld at position %lld\r\n    ..., but this is not certain.)\r\n", unexpectedLexemfailedTerminal->lexemStr, unexpectedLexemfailedTerminal->row, unexpectedLexemfailedTerminal->col);
        }
        else {
            printf("Parse failed: unexpected terminal.\r\n");
        }
        exit(0);
    }
    return false;
}
bool parseByRecursiveDescent_(LexemInfo* lexemInfoTable, Grammar* grammar) {
    int lexemIndex = 0;
    const struct LexemInfo unexpectedUnknownLexemfailedTerminal("unknown", 0, 0, 0, ~0, ~0); //
    const struct LexemInfo* returnUnexpectedLexemfailedTerminal = nullptr;

    if (nullptr == (returnUnexpectedLexemfailedTerminal = recursiveDescentParserWithDebug_(grammar->start_symbol, lexemIndex, lexemInfoTable, grammar, 0, &unexpectedUnknownLexemfailedTerminal))) {
        if (lexemInfoTable[lexemIndex].lexemStr[0] == '\0') {
            printf("Parse successful.\n");
            printf("%d.\n", lexemIndex);
            return true;
        }
        else {
            printf("Parse failed: Extra tokens remain.\n");
            exit(0);
        }
    }
    else {
        if (returnUnexpectedLexemfailedTerminal->lexemStr[1]) {
            printf("Parse failed.\r\n");
            printf("    (The predicted terminal does not match the expected one.\r\n    Possible unexpected terminal \"%s\" on line %lld at position %lld\r\n    ..., but this is not certain.)\r\n", returnUnexpectedLexemfailedTerminal->lexemStr, returnUnexpectedLexemfailedTerminal->row, returnUnexpectedLexemfailedTerminal->col);
        }
        else {
            printf("Parse failed: unexpected terminal.\r\n");
        }
        exit(0);
    }
    return false;
}
#endif
