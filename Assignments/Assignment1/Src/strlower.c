/***************************************************************
* File Name     : strlower.c
* Description   : Application used for converting string to lowercase 
* Date          : 30.1.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
****************************************************************/

/**************************Includes*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "Util.h"

/***************************Macros******************************/

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
    int opt = 0;
    unsigned int local_Index = 0u;
    FILE *local_FilePtr = NULL;
    FILE *local_TmpFilePtr = NULL;
    char local_Char = 0;

    if(argc == 1)
    {
        app_usage();
    }
    else if (argc == 2)
    {
        while(argv[1][local_Index] != '\0')
        {
            if( Util_IsLowerCase(argv[1][local_Index]) == 1u )
            {
                printf( "%c", Util_ConvertToLowerCase(argv[1][local_Index]) );
            }
            else
            {
                printf( "%c", argv[1][local_Index] );
            }
            local_Index++;
        }
        
    }
    else
    {
        while( (opt = getopt(argc, argv, "hf:")) != -1)
        {
            switch(opt)
            {
                case 'h':
                {
                    app_usage();
                    break;
                }

                case 'f':
                {
                    local_FilePtr = fopen(optarg, "r");
                    if(local_FilePtr != NULL)
                    {
                        local_TmpFilePtr = fopen("./strlower.tmp", "w");
                        if(local_TmpFilePtr != NULL)
                        {                         
                            while( (local_Char = fgetc(local_FilePtr)) != EOF)
                            {
                                fputc( Util_ConvertToLowerCase(local_Char), local_TmpFilePtr);
                            }                             
                            fclose(local_TmpFilePtr);
                        }
                        else
                        {
                            printf("Error in openenig file ./strlower.tmp");
                            return -1;
                        }
                        
                        fclose(local_FilePtr);
                    }
                    else
                    {
                        printf("Error in openenig file %s", optarg);
                        return -1;
                    }

                    local_FilePtr = fopen(optarg, "w");
                    if(local_FilePtr != NULL)
                    {
                        local_TmpFilePtr = fopen("./strlower.tmp", "r");
                        if(local_TmpFilePtr != NULL)
                        {                         
                            while( (local_Char = fgetc(local_TmpFilePtr)) != EOF)
                            {
                                fputc( Util_ConvertToLowerCase(local_Char), local_FilePtr);
                            }                             
                            fclose(local_TmpFilePtr);
                        }
                        else
                        {
                            printf("Error in openenig file ./strlower.tmp");
                            return -1;
                        }
                        
                        fclose(local_FilePtr);
                    }
                    else
                    {
                        printf("Error in openenig file %s", optarg);
                        return -1;
                    }
                    remove("strlower.tmp");
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