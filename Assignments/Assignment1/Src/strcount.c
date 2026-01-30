/***************************************************************
* File Name     : strcount.c
* Description   : Application used for characters and words 
*                 counting in a string
* Date          : 30.1.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
****************************************************************/

/**************************Includes*****************************/
#include <stdio.h>
#include <string.h>
#include <getopt.h>

/***************************Macros******************************/

/**************************Typedefs*****************************/

/************************global-variables***********************/

/*********************functions-prototypes**********************/
void app_usage(void);

/******************functions-implementations*********************/
void app_usage(void)
{
    printf("This is strcount application, you can use it to count\n"
           "characters in string or count words in a string\n"
           "[Usage]\n"
           "strcount [string]       : Returns number of characters in string \n"
           "strcount -w [string]    : Returns number of words in string \n");
}

int main(int argc, char *argv[])
{
    int opt = 0;
    unsigned int local_Index = 0u, local_Count = 0u;
    char* local_Token;

    if(argc == 1)
    {
        app_usage();
    }
    else if (argc == 2)
    {
        while(argv[1][local_Index++] != '\0')
        {
            local_Count++;
        }
        printf("%d", local_Count);
    }
    else
    {
        while( (opt = getopt(argc, argv, "hw:c:")) != -1)
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
                    local_Token = strtok(optarg, " ");                               
                    while (local_Token != NULL)
                    {
                        local_Count++;
                        local_Token = strtok(NULL, " "); 
                    }
                    printf("%d", local_Count);
                    break;
                }

                case 'c':
                {
                    while(optarg[local_Index++] != '\0')
                    {
                        local_Count++;
                    }
                    printf("%d", local_Count);
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