/***************************************************************
* File Name     : Util.h
* Description   : Utilities Implementation Header
* Date          : 31.1.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
****************************************************************/

/**************************Includes*****************************/
#include <stdint.h>

/***************************Macros******************************/

/**************************Typedefs*****************************/

/************************global-variables***********************/

/*********************functions-prototypes**********************/

/******************functions-implementations*********************/
uint8_t Util_IsDigit(uint8_t param_char);
uint8_t Util_IsLowerCase(uint8_t param_char);
uint8_t Util_IsUpperCase(uint8_t param_char);
uint8_t Util_ConvertToUpperCase(uint8_t param_char);
uint8_t Util_ConvertToLowerCase(uint8_t param_char);