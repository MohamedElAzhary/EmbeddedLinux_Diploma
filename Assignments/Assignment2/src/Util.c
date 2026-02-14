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
#include "stdlib.h"
#include "string.h"

/***************************Macros******************************/
#define UTIL_MAX_BUFFER_SIZE     (255U)

/* Text Styles */
#define STYLE_RESET       "\033[0m"
#define STYLE_BOLD        "\033[1m"
#define STYLE_DIM         "\033[2m"
#define STYLE_ITALIC      "\033[3m"
#define STYLE_UNDERLINE   "\033[4m"
#define STYLE_BLINK       "\033[5m"
#define STYLE_REVERSE     "\033[7m"
#define STYLE_STRIKE      "\033[9m"

/* Foreground (Text) Colors */
#define FG_BLACK          "\033[30m"
#define FG_RED            "\033[31m"
#define FG_GREEN          "\033[32m"
#define FG_YELLOW         "\033[33m"
#define FG_BLUE           "\033[34m"
#define FG_MAGENTA        "\033[35m"
#define FG_CYAN           "\033[36m"
#define FG_WHITE          "\033[37m"

/* Background Colors */
#define BG_BLACK          "\033[40m"
#define BG_RED            "\033[41m"
#define BG_GREEN          "\033[42m"
#define BG_YELLOW         "\033[43m"
#define BG_BLUE           "\033[44m"
#define BG_MAGENTA        "\033[45m"
#define BG_CYAN           "\033[46m"
#define BG_WHITE          "\033[47m"

/* Screen Manipulation */
#define SCREEN_CLEAR      "\033[2J"
#define CURSOR_HOME       "\033[H"
#define LINE_CLEAR        "\033[K"

/**************************Typedefs*****************************/

/************************global-variables***********************/
static uint8_t global_ReveresedArray[UTIL_MAX_BUFFER_SIZE] = {0u};
static char *global_BG_Color = "";
static char *global_FG_Color = FG_WHITE;
static char *global_Style = "";

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

bool Util_IsValidString(const int8_t* param_StrPtr)
{
    bool local_RetValue = true;

    if( (param_StrPtr == NULL) || (param_StrPtr[0] == '\0') )
    {
        local_RetValue = false;
    }
    
    return local_RetValue;
}

void Util_ModPrintf(char* param_msg)
{
    printf("%s%s%s%s%s", 
        global_BG_Color, 
        global_FG_Color, 
        global_Style,
        param_msg,
        STYLE_RESET
    );
}


void Util_EditSettings(void)
{   
    int local_FG_Color = 0;
    int local_BG_Color = 0;
    int local_Style = 0;
    int local_ReturnError = 0;
    char buff[20];

    Util_ModPrintf("[1] Red [2] Green [3] White [0] Exit\n"
        "Choose your Desired Font Color:");

    fgets(buff, 20, stdin);
    local_FG_Color = atoi(buff);
    switch (local_FG_Color)
    {
        case 1:
            global_FG_Color = FG_RED;
            Util_ModPrintf("Red Text Color Selected\n");
            break;
        case 2:
            global_FG_Color = FG_GREEN;
            Util_ModPrintf("Green Text Color Selected\n");
            break;
        case 3:
            global_FG_Color = FG_WHITE;
            Util_ModPrintf("White Text Color Selected\n");
            break;
        default:
            local_ReturnError = 1;
            break;
    }

    if(local_ReturnError == 0)
    {
        Util_ModPrintf("[1] Red [2] Green [3] White [0] Exit\n"
            "Choose your Desired Background Color:");
            
        fgets(buff, 20, stdin);
        local_BG_Color = atoi(buff);

        switch (local_BG_Color)
        {
            case 1:
                global_BG_Color = BG_RED;
                Util_ModPrintf("Red Background Color Selected\n");
                break;
            case 2:
                global_BG_Color = BG_GREEN;
                Util_ModPrintf("Green Background Color Selected\n");
                break;
            case 3:
                global_BG_Color = BG_WHITE;
                Util_ModPrintf("White Background Color Selected\n");
                break;
            default:
                local_ReturnError = 1;
                break;
        }
    }

    if(local_ReturnError == 0)
    {
        Util_ModPrintf("[1] Bold [2] Italic [3] Underlined [0] Exit\n"
            "Choose your Desired Text Style:");

        fgets(buff, 20, stdin);
        local_Style = atoi(buff);
        switch (local_Style)
        {
            case 1:
                global_Style = STYLE_BOLD;
                Util_ModPrintf("Bold Text Style Selected\n");
                break;
            case 2:
                global_Style = STYLE_ITALIC;
                Util_ModPrintf("Italic Text Style Selected\n");
                break;
            case 3:
                global_Style = STYLE_UNDERLINE;
                Util_ModPrintf("Underlined Text Style Selected\n");
                break;
            default:
                local_ReturnError = 1;
                break;
        }
    }

    
    if(local_ReturnError == 0)
    {
        Util_ModPrintf("Settings Updated\n");
    }

}
