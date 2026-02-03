/***************************************************************
* File Name     : strrev.c
* Description   : Source file for sttrev that reverses a string
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
#define MAX_STRING_SIZE     (255U)

/**************************Typedefs*****************************/

/************************global-variables***********************/

/*********************functions-prototypes**********************/
void app_usage(void);

/******************functions-implementations*********************/
void app_usage(void)
{
    printf("This is strlower application, used for converting string to lowercase\n"
           "[Usage]\n"
           "strlower [string]     : Returns string in lowercase.\n"
           "strlower -f [FILE]    : Convert file contents to lowercase.\n");
}



int main(int argc, char *argv[])
{
    int32_t opt = 0;
    uint32_t local_Index = 0u;
    uint32_t local_StringSize = 0u;
    

    if(argc == 1)
    {
        app_usage();
    }
    else if (argc == 2)
    {
        Util_FillReversedString(argv[1]);
        printf("%s\n",Util_GetReversedBufferAddress());
    }
    else
    {
        while( (opt = getopt(argc, argv, "hw:")) != -1)
        {
            switch(opt)
            {
                case 'h':
                {
                    app_usage();
                    break;
                }

                case 'w':
                {
                    Util_FillReversedStringTokensArray(optarg);
                    printf("%s\n",Util_GetReversedBufferAddress());
                    break;
                }
                
                default:
                    printf("Wrong Option Passed %c", opt);
                    break;
            }
        }
    }

    return 0;
}
