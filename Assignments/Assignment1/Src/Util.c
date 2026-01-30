/***************************************************************
* File Name     : Util.c
* Description   : Utilities Implementation
* Date          : 31.1.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
****************************************************************/

/**************************Includes*****************************/
#include "Util.h"

/***************************Macros******************************/

/**************************Typedefs*****************************/

/************************global-variables***********************/

/*********************functions-prototypes**********************/

/******************functions-implementations*********************/
uint8_t Util_IsDigit(uint8_t param_char)
{
    uint8_t local_RetValue = 0u;
    if( ('0' <= param_char) && (param_char <= '9') )
    {
        local_RetValue = 1u;
    }
    return local_RetValue;
}

uint8_t Util_IsLowerCase(uint8_t param_char)
{
    uint8_t local_RetValue = 0u;
    if( ('a' <= param_char) && (param_char <= 'z') )
    {
        local_RetValue = 1u;
    }
    return local_RetValue;
}
uint8_t Util_IsUpperCase(uint8_t param_char)
{
    uint8_t local_RetValue = 0u;
    if( ('A' <= param_char) && (param_char <= 'Z') )
    {
        local_RetValue = 1u;
    }
    return local_RetValue;
}

uint8_t Util_ConvertToUpperCase(uint8_t param_char)
{
    uint8_t local_Char = param_char;
    if(Util_IsLowerCase(param_char))
    {
        local_Char = param_char - ('a' - 'A'); 
    }
    return local_Char;
}

uint8_t Util_ConvertToLowerCase(uint8_t param_char)
{
    uint8_t local_Char = param_char;
    if(Util_IsUpperCase(param_char))
    {
        local_Char = param_char + ('a' - 'A'); 
    }
    return local_Char;
}