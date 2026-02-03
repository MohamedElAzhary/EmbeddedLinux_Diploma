/***************************************************************
* File Name     : strcat.c
* Description   : Source file for concatenating strings
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
    printf("This is strcat application, used for concatenating strings\n"
           "[Usage]\n"
           "strcat \"string1\" \"string2\"       : Concatenate Strings into 1 string.\n"
           "strcat -s \" \" \"string1\" \"string2\"    : Concatenate Strings into 1 string separated by char.\n");
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
        if(true == Util_CatStrings(argv[1], argv[2], false))
        {
            printf("%s\n", Util_GetReversedBufferAddress());
        }
    }
    else
    {
        while( (opt = getopt(argc, argv, "hs:")) != -1)
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
                    printf("%s\n", optarg);
                    printf("%s\n", argv[optind]);
                    if(true == Util_CatStrings(optarg, argv[optind], true))
                    {
                        printf("%s\n", Util_GetReversedBufferAddress());
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
