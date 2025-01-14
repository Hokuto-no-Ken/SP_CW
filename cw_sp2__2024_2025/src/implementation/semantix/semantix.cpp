#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: semantix.h                  *
*                                                  (draft!) *
*************************************************************/

#include "../../include/semantix/semantix.h"
#include "stdio.h"
#include "string.h"
//
//#define COLLISION_II_STATE 128
//#define COLLISION_LL_STATE 129
//#define COLLISION_IL_STATE 130
//#define COLLISION_I_STATE  132
//#define COLLISION_L_STATE  133
//
//#define NO_IMPLEMENT_CODE_STATE 256

int checkingInternalCollisionInDeclarations(/*TODO: add arg*/) {
	for (unsigned int index = 0; identifierIdsTable[index][0] != '\0'; ++index) {
		char isDeclaredIdentifier = 0;
		char isDeclaredIdentifierCollision = 0;
		unsigned int lexemIndex = 0;
		for (; strncmp(lexemesInfoTable[lexemIndex].lexemStr, ";", MAX_LEXEM_SIZE) && lexemesInfoTable[lexemIndex].lexemStr[0] != '\0'; ++lexemIndex) {
			if (lexemesInfoTable[lexemIndex].tokenType == IDENTIFIER_LEXEME_TYPE) {
				if (!strncmp(identifierIdsTable[index], lexemesInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)) {
					if (isDeclaredIdentifier) {
						isDeclaredIdentifierCollision = 1;
					}
					isDeclaredIdentifier = 1;
				}
			}
		}
		++lexemIndex;
		for (; strncmp(lexemesInfoTable[lexemIndex].lexemStr, ";", MAX_LEXEM_SIZE) && lexemesInfoTable[lexemIndex].lexemStr[0] != '\0'; ++lexemIndex) {
			if (lexemesInfoTable[lexemIndex].tokenType == IDENTIFIER_LEXEME_TYPE) {
				if (!strncmp(identifierIdsTable[index], lexemesInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)) {
					if (isDeclaredIdentifier) {
						isDeclaredIdentifierCollision = 1;
					}
					isDeclaredIdentifier = 1;
				}
			}
		}

		char isLabel = 0;
		char isDeclaredLabel = 0;
		char isDeclaredLabelCollision = 0;
		for (unsigned int lexemIndex = 0; lexemesInfoTable[lexemIndex].lexemStr[0] != '\0'; ++lexemIndex) {
			if (lexemesInfoTable[lexemIndex].tokenType != IDENTIFIER_LEXEME_TYPE || strncmp(identifierIdsTable[index], lexemesInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)) {
				continue;
			}
			if (lexemesInfoTable[lexemIndex + 1].lexemStr[0] == ':') {
				if (isDeclaredLabel) {
					isDeclaredLabelCollision = 1;
				}
				isLabel = 1;
				isDeclaredLabel = 1;
			}
			if (lexemIndex && !strncmp(lexemesInfoTable[lexemIndex - 1].lexemStr, "goto", MAX_LEXEM_SIZE)) {
				isLabel = 1;
			}
		}

		if (isDeclaredIdentifierCollision) {
			printf("Collision(identifier/identifier): %s\r\n", identifierIdsTable[index]);
			return COLLISION_II_STATE;
		}
		if (isDeclaredLabelCollision) {
			printf("Collision(label/label): %s\r\n", identifierIdsTable[index]);
			return COLLISION_LL_STATE;
		}
		if (isDeclaredIdentifier && isLabel) {
			printf("Collision(identifier/label): %s\r\n", identifierIdsTable[index]);
			return COLLISION_IL_STATE;
		}
		else if (!isDeclaredIdentifier && !isLabel && !isDeclaredLabel) {
			printf("Undeclared identifier: %s\r\n", identifierIdsTable[index]);
			return COLLISION_I_STATE;
		}
		else if (isLabel && !isDeclaredLabel) {
			printf("Undeclared label: %s\r\n", identifierIdsTable[index]);
			return COLLISION_L_STATE;
		}
	}

	printf("Declaration verification was successful!\r\n");
	return SUCCESS_STATE;
}

int checkingVariableInitialization(/*TODO: add args*/) {
	//TODO: implement this

	printf("\r\nTODO: implent \"int checkingVariableInitialization(/*TODO: add args*/)\"\r\n\r\n");
	return NO_IMPLEMENT_CODE_STATE;
}

int checkingCollisionInDeclarationsByKeyWords(/*TODO: add args*/) {
	//TODO: implement this

	printf("\r\nTODO: implent \"int checkingCollisionInDeclarationsByKeyWords(/*TODO: add args*/)\"\r\n\r\n");
	return NO_IMPLEMENT_CODE_STATE;
}