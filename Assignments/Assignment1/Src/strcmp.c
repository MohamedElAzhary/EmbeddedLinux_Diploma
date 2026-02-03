/***************************************************************
* File Name     : stcmp.c
* Description   : Application used for strings comparison
* Date          : 3.2.2026
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
    printf("This is strcmp application, used for comparing strings\n"
           "[Usage]\n"
           "strcmp \"string1\" \"string2\"       : Compare Strings - case sensitive.\n"
           "strcmp -i \"string1\" \"string2\"    : Compare Strings - case insensitive.\n");
}


int main(int argc, char *argv[])
{
    int32_t opt = 0;
    uint32_t local_Index = 0u;  

    if(argc == 1)
    {
        app_usage();
    }
    else if (argc == 3)
    {
        if(true == Util_CompareStrings(argv[1] , argv[2], true))
        {
            printf("%s\n", "Equal");
        }
        else
        {
            printf("%s\n", "Not equal");
        }
    }
    else
    {
        while( (opt = getopt(argc, argv, "hi:")) != -1)
        {
            switch(opt)
            {
                case 'h':
                {
                    app_usage();
                    break;
                }

                case 'i':
                {        
                    if(true == Util_CompareStrings(optarg , argv[optind], false))
                    {
                        printf("%s\n", "Equal");
                    }
                    else
                    {
                        printf("%s\n", "Not equal");
                    }
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
