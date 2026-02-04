/***************************************************************
* File Name     : strsub.c
* Description   : Source file for Extracting substring
* Date          : 2.2.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
****************************************************************/

/**************************Includes*****************************/
#include "Util.h"
#include "stdio.h"
#include "stdlib.h"
#include "getopt.h"

/***************************Macros******************************/

/**************************Typedefs*****************************/

/************************global-variables***********************/

/*********************functions-prototypes**********************/
void app_usage(void);

/******************functions-implementations*********************/
void app_usage(void)
{
    printf("This is strsub application, used for Extracting Substring\n"
           "[Usage]\n"
           "strsub \"string1\" -s Start_Index -e End_Index : Extract Substring [Start_Index:End_Index].\n"
           "strsub \"string1\" -n NUM_CHARS : Extract Substring [0:NUM_CHARS-1].\n"
           "strsub \"string1\" -l NUM_CHARS : Extract Substring [LEN-NUM_CHARS+1:LEN].\n");
}



int main(int argc, char *argv[])
{
    int32_t opt = 0;
    uint32_t local_Index = 0u;  
    uint32_t local_Length = 0u;
    uint32_t local_StartIndex = 0u;
    uint32_t local_EndIndex = 0u;
    bool local_AllDataAcquired = 0u;
    bool local_StartAcquired = 0u;
    bool local_EndAcquired = 0u;
    bool local_LenAcquired = 0u;   
    int8_t* local_DataPtr = NULL;

    if(argc == 1)
    {
        app_usage();
    }
    else
    {
        local_Length = strlen(argv[1]);
        local_DataPtr = argv[1];

        while( (opt = getopt(argc, argv, "hs:e:n:l:")) != -1)
        {
            switch(opt)
            {
                case 'h':
                {
                    app_usage();
                    break;
                }

                case 's':
                {                    
                    local_StartIndex = atoi(optarg);              
                    if(local_StartIndex < local_Length)
                    {
                        local_StartAcquired = 1u;
                    }
                    break;
                }
                
                case 'e':
                {                    
                    local_EndIndex = atoi(optarg)-1;          
                    if(local_EndIndex < local_Length)
                    {
                        local_EndAcquired = 1u;
                    }
                    break;
                }

                case 'n':
                {                                    
                    local_StartIndex = 0u;   
                    local_EndIndex = local_StartIndex + atoi(optarg) - 1;
                    if(local_EndIndex < local_Length)
                    {
                        local_LenAcquired = 1u;
                    }
                    break;
                }

                case 'l':
                {           
                    local_StartIndex = local_Length - atoi(optarg);   
                    local_EndIndex = local_Length-1;
                    if( (local_EndIndex < local_Length) && (local_StartIndex < local_Length) )
                    {
                        local_LenAcquired = 1u;
                    }

                    break;
                }

                default:
                    printf("Wrong Option Passed %c", opt);
                    break;
            }
        }

        if( ( (local_StartAcquired == 1u) && (local_EndAcquired == 1u) ) || (local_LenAcquired == 1u) )
        {            
            for(local_Index = local_StartIndex; local_Index<= local_EndIndex; local_Index++)
            {
                printf("%c",local_DataPtr[local_Index]);
            }
        }
        else
        {
        }
    }

    return 0;
}
