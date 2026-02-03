/***************************************************************
* File Name     : Util.h
* Description   : Utilities Implementation Header
* Date          : 31.1.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
****************************************************************/

/**************************Includes*****************************/
#include "stdint.h"
#include "string.h"
#include "stdbool.h"

/***************************Macros******************************/

/**************************Typedefs*****************************/

/************************global-variables***********************/

/*********************functions-prototypes**********************/

/******************functions-implementations*********************/
uint8_t Util_IsDigit(uint8_t param_char);
uint8_t Util_IsLetter(uint8_t param_char);
uint8_t Util_IsLowerCase(uint8_t param_char);
uint8_t Util_IsUpperCase(uint8_t param_char);
int8_t Util_ConvertToUpperCase(int8_t param_char);
int8_t Util_ConvertToLowerCase(int8_t param_char);
bool Util_FillReversedArray(uint8_t* param_ArrayPtr, uint32_t param_ArraySize);
bool Util_FillReversedString(uint8_t* param_StringPtr);
uint8_t* Util_GetReversedBufferAddress(void);
bool Util_FillReversedStringTokensArray(uint8_t* param_StringPtr, int8_t param_Seperator);
bool Util_CatStrings(uint8_t* param_Str1, uint8_t* param_Str2, bool param_AddSpaceSeperator);
bool Util_CompareStrings(int8_t* param_Str1, int8_t* param_Str2, bool param_IsCaseSensitive);