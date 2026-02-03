/***************************************************************
* File Name     : Util.c
* Description   : Utilities Implementation
* Date          : 31.1.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
****************************************************************/

/**************************Includes*****************************/
#include "Util.h"
#include "stdio.h"

/***************************Macros******************************/
#define UTIL_MAX_BUFFER_SIZE     (255U)

/**************************Typedefs*****************************/

/************************global-variables***********************/
static uint8_t global_ReveresedArray[UTIL_MAX_BUFFER_SIZE] = {0u};

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

uint8_t Util_IsLetter(uint8_t param_char)
{
    uint8_t local_RetValue = 0u;

    if( ('a' <= param_char) && (param_char <= 'z') )
    {
        local_RetValue = 1u;
    }
    else if( ('A' <= param_char) && (param_char <= 'Z') )
    {
        local_RetValue = 1u;
    }
    else
    {
        // Do Nothing
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

int8_t Util_ConvertToUpperCase(int8_t param_char)
{
    int8_t local_Char = param_char;
    if(Util_IsLowerCase(param_char))
    {
        local_Char = param_char - ('a' - 'A'); 
    }
    return local_Char;
}

int8_t Util_ConvertToLowerCase(int8_t param_char)
{
    int8_t local_Char = param_char;
    if(Util_IsUpperCase(param_char))
    {
        local_Char = param_char + ('a' - 'A'); 
    }
    return local_Char;
}


bool Util_FillReversedArray(uint8_t* param_ArrayPtr, uint32_t param_ArraySize)
{
    uint32_t local_Index = param_ArraySize;
    bool local_RetValue = true;
    if( (param_ArraySize <= UTIL_MAX_BUFFER_SIZE) && (param_ArrayPtr != NULL) )
    {
        memset(global_ReveresedArray, 0u, UTIL_MAX_BUFFER_SIZE);

        for(local_Index=param_ArraySize; local_Index > 0u; local_Index--)
        {
            global_ReveresedArray[param_ArraySize-local_Index] = param_ArrayPtr[local_Index-1];
        }    
    }
    else
    {
        local_RetValue = false;
    }

    return local_RetValue;
}

bool Util_FillReversedString(uint8_t* param_StringPtr)
{
    uint32_t local_Index = 0u, local_StringLen = 0u;
    bool local_RetValue = true;

    if(param_StringPtr != NULL)
    {      
        local_StringLen = strlen((const char*)param_StringPtr);

        if( local_StringLen < UTIL_MAX_BUFFER_SIZE )
        {
            memset(global_ReveresedArray, 0u, UTIL_MAX_BUFFER_SIZE);

            for(local_Index=local_StringLen; local_Index > 0u; local_Index--)
            {
                global_ReveresedArray[local_StringLen-local_Index] = param_StringPtr[local_Index-1];
            }

            // Terminate the String
            global_ReveresedArray[local_StringLen] = '\0';

        }
        else
        {
            local_RetValue = false;
        }
    }
    else
    {
        local_RetValue = false;
    }

    return local_RetValue;
}

uint8_t* Util_GetReversedBufferAddress(void)
{
    return global_ReveresedArray;
}

bool Util_FillReversedStringTokensArray(uint8_t* param_StringPtr, int8_t param_Seperator)
{
    uint32_t local_Index = 0u, local_DestIndex = 0u, local_SourceArrayLen = 0u, local_StrLen = 0u;
    uint32_t local_StIndex = 0u, local_EndIndex = 0u;
    bool local_RetValue = true;
    bool local_Dec_Ignore_Cond = false;

    if(param_StringPtr != NULL)
    {      
        memset(global_ReveresedArray, 0u, UTIL_MAX_BUFFER_SIZE);
        local_SourceArrayLen = strlen((const char*)param_StringPtr) + 1u;

        local_Index = local_SourceArrayLen - 1u;
        local_DestIndex = 0u;

        while(0 <= local_Index)
        {
            local_Dec_Ignore_Cond = (param_StringPtr[local_Index] == '\0') || ((param_StringPtr[local_Index] != param_Seperator) && (local_Index != 0u) );
            if(local_Dec_Ignore_Cond)
            {
                if(0 < local_Index)
                {
                    local_Index--;
                }
                else
                {
                    break;
                }
            }
            else if( (param_StringPtr[local_Index] == param_Seperator) )
            {
                local_StIndex = local_Index + 1;
                local_EndIndex = local_StIndex;
                if( (param_StringPtr[local_StIndex] != param_Seperator) && (param_StringPtr[local_StIndex] != '\0') )
                {
                    while( (param_StringPtr[local_EndIndex] != param_Seperator) && (param_StringPtr[local_EndIndex] != '\0') )
                    {
                        local_EndIndex++;
                    }

                    local_StrLen = local_EndIndex  - local_StIndex + 1u;

                    if( (local_EndIndex < local_SourceArrayLen) && ( (local_DestIndex + local_StrLen - 1u) < UTIL_MAX_BUFFER_SIZE ) )
                    {
                        memcpy((uint8_t*) &global_ReveresedArray[local_DestIndex], (uint8_t*) &param_StringPtr[local_StIndex], local_StrLen);                

                        if(global_ReveresedArray[(local_DestIndex + local_StrLen - 1u)] == '\0')
                        {
                            global_ReveresedArray[(local_DestIndex + local_StrLen - 1u)] = param_Seperator;
                        }

                        local_DestIndex = local_DestIndex + local_StrLen;
                    }
                    else
                    {
                        local_RetValue = false;
                    } 
                }

                if(0 < local_Index)
                {
                    local_Index--;
                }
                else
                {
                    break;
                }
            }
            else if( (param_StringPtr[local_Index] != param_Seperator) && (local_Index == 0u) )
            {
                local_StIndex = local_Index;
                local_EndIndex = local_StIndex;
                if( (param_StringPtr[local_StIndex] != param_Seperator) && (param_StringPtr[local_StIndex] != '\0') )
                {
                    while( (param_StringPtr[local_EndIndex] != param_Seperator) && (param_StringPtr[local_EndIndex] != '\0') )
                    {
                        local_EndIndex++;
                    }

                    local_StrLen = local_EndIndex  - local_StIndex + 1u;

                    if( (local_EndIndex < local_SourceArrayLen) && ( (local_DestIndex + local_StrLen - 1u) < UTIL_MAX_BUFFER_SIZE ) )
                    {
                        memcpy((uint8_t*) &global_ReveresedArray[local_DestIndex], (uint8_t*) &param_StringPtr[local_StIndex], local_StrLen);                

                        local_DestIndex = local_DestIndex + local_StrLen;
                        if(global_ReveresedArray[(local_DestIndex - 1u)] == param_Seperator)
                        {
                            global_ReveresedArray[(local_DestIndex - 1u)] = '\0';
                        }

                    }
                    else
                    {
                        local_RetValue = false;
                    } 
                }

                if(0 < local_Index)
                {
                    local_Index--;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if(0 < local_Index)
                {
                    local_Index--;
                }
                else
                {
                    break;
                }
            }
        }
    }
    else
    {
        local_RetValue = false;
    }  
    
    global_ReveresedArray[UTIL_MAX_BUFFER_SIZE - 1U] = '\0';

    return local_RetValue;
}

bool Util_CatStrings(uint8_t* param_Str1, uint8_t* param_Str2, bool param_AddSpaceSeperator)
{
    bool local_RetValue = true;
    uint32_t local_Str1Len = strlen(param_Str1);
    uint32_t local_Str2Len = strlen(param_Str2);
    uint32_t local_DestIndex = 0u;
    uint32_t local_TotalLength = 0u;

    memset(global_ReveresedArray, 0u, UTIL_MAX_BUFFER_SIZE);

    if( (param_Str1 != NULL) && (param_Str2 != NULL) )
    {
        if(local_Str1Len + 1 <= UTIL_MAX_BUFFER_SIZE)
        {
            memcpy((uint8_t*) &global_ReveresedArray[local_DestIndex], (uint8_t*) param_Str1, local_Str1Len);  
            local_DestIndex = local_DestIndex + local_Str1Len;

            local_TotalLength = local_Str1Len;

            if(true == param_AddSpaceSeperator)
            {
                local_TotalLength = local_TotalLength + 1u;  
                if(local_TotalLength <= UTIL_MAX_BUFFER_SIZE )
                {
                    global_ReveresedArray[local_DestIndex] = ' ';
                    local_DestIndex = local_DestIndex + 1u;           
                }
            }

            local_TotalLength = local_TotalLength + local_Str2Len + 1;
            if(local_TotalLength <= UTIL_MAX_BUFFER_SIZE)
            {
                memcpy((uint8_t*) &global_ReveresedArray[local_DestIndex], (uint8_t*) param_Str2, local_Str2Len);                
            }
            else
            {
                local_RetValue = false;
            }
        }
        else
        {
            local_RetValue = false;
        }
    }
    else
    {
        local_RetValue = false;
    }

    return local_RetValue;
}

bool Util_CompareStrings(int8_t* param_Str1, int8_t* param_Str2, bool param_IsCaseSensitive)
{
    bool local_RetValue = true;
    uint32_t local_Index = 0u;
    int32_t local_CmpValue = 0;
    uint32_t local_Str1Len = 0u;
    uint32_t local_Str2Len = 0u;

    if( (param_Str1 != NULL) && (param_Str2 != NULL) )
    {
        local_Str1Len = strlen(param_Str1);
        local_Str2Len = strlen(param_Str2);
        if( (local_Str1Len == local_Str2Len) )
        {
            if(param_IsCaseSensitive == true)
            {
                local_CmpValue = strcmp(param_Str1, param_Str2);
                if(local_CmpValue != 0)
                {
                    local_RetValue = false;
                }
            }
            else
            {
                while(local_Index < local_Str1Len)
                {
                    if(Util_ConvertToLowerCase(param_Str1[local_Index]) != Util_ConvertToLowerCase(param_Str2[local_Index]) )
                    {
                        local_RetValue = false;
                        break;
                    }
                    local_Index++;
                }
            }
        }
        else
        {
            local_RetValue = false;
        }
    }
    else
    {
        local_RetValue = false;
    }

    return local_RetValue;
}