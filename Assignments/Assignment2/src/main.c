/*********************
* File Name     : main.c
* Description   : Main source file
* Date          : 09.02.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
**********************/

/*********Includes**********/
#include "main.h"

/**********Macros***********/

/*********Typedefs**********/

/*********global-variables********/
bool Shell_global_DebugEnabled = false;
bool Shell_global_DeepInspectionEnabled = false;

/********functions-prototypes*******/
void app_usage(void);

/*******functions-implementations********/
void app_usage(void)
{
    printf("Welcome To Azhary Shell\n\n"
            "[USAGE]\n"
            "\t./azharyshell [OPTION 1] .. [OPTION N] CMD\n\n"
            "[Example]\n"
            "\t./azharyshell -h : Displays help page\n"
            "\t./azharyshell echo Hello World! : This will print Hello World!\n\n"
            "[OPTIONS]\n"
            "\t-d : Displays Debug Information [Developers Only]\n"
            "\t-i : Displays Level 2 Debug Information [Developers Only]\n"
            "\t-h : Displays Help Message\n\n"
            "[SUPPORTED FEATURES]\n"
            "\tAUTO-COMPLETE : Click Tab to autocomplete your installed command name\n"
            "\tBROWSE-HISOTRY : Click on Up/Down Keyboard Arrows to browse command history\n\n"
            "[BUILT-IN CMDS]\n"
            "\texit : Exits shell\n"
            "\teditshell : Takes user input interactively to edit shell settings\n"
            "\tcd [DIR_PATH] : Change current directory to be DIR directory found in DIR_PATH\n"
            "\n"
    );
}

void app_showBanner(void)
{          
    printf(
        "    _     ______   _    _    ______   __  ____  _   _ _____ _     _\n"
        "   / \\   |__  / | | |  / \\  |  _ \\ \\ / / / ___|| | | | ____| |   | |\n"
        "  / _ \\    / /| |_| | / _ \\ | |_) \\ V /  \\___ \\| |_| |  _| | |   | |\n"
        " / ___ \\  / /_|  _  |/ ___ \\|  _ < | |    ___) |  _  | |___| |___| |___ \n"
        "/_/   \\_\\/____|_| |_/_/   \\_\\_| \\_\\|_|   |____/|_| |_|_____|_____|_____|\n\n");                                                                                                              
}

int main(int argc, char** argv)
{
    
    int local_opt = 0;

    app_showBanner();

    while( (local_opt = getopt(argc, argv, "hdi")) != -1)
    {
        switch(local_opt)
        {
            case 'h':
            {
                app_usage();
                Shell_SetExit();
                break;
            }

            case 'd':
            {
                Shell_global_DebugEnabled = true;
                break;
            }

            case 'i':
            {
                Shell_global_DeepInspectionEnabled = true;                
                break;
            }
            
            default:
            {
                printf("Wrong Option Passed %c", optopt);
                Shell_SetExit();
                break;
            }
        }
    }

    if( !Shell_GetExit() )
    {
        if(true == Shell_EngineInit())
        {
            while( !Shell_GetExit() )
            {
                Shell_EngineMain();
            }            
        }
        
        Shell_EngineExitActions();
    }

    return 0;
}



