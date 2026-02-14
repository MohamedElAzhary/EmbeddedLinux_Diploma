/*********************
* File Name     : engine.c
* Description   : Execution Engine responsible for Process Management
*               : and built in commands
* Date          : 09.02.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
**********************/

/*********Includes**********/
#include "engine.h"
#include "stdlib.h"
#include "stdbool.h"
#include "getopt.h"
#include "unistd.h"
#include "dirent.h"
#include "stdio.h"
#include "sys/wait.h"
#include "stdint.h"
#include "Util.h"
#include "readline/readline.h"
#include "readline/history.h"

/**********Macros***********/
#define SHELL_MAX_USER_INPUT_LEN_BYTES  (300U)
#define SHELL_MAX_TOKENS_LEN_BYTES      (20U)

/*********Typedefs**********/

/*********global-variables********/
bool Shell_global_ExitRequested_bool = false;

extern bool Shell_global_DebugEnabled;
extern bool Shell_global_DeepInspectionEnabled;

__pid_t Shell_global_PPID = 0;
__pid_t Shell_global_CPID = 0;
int8_t* Shell_global_BuiltInCmds[] = {"exit", "editshell"};

// Address of Array of Strings
int8_t** shell_global_CmdCache = NULL; 
int32_t shell_global_CmdCacheCMDSNumber = 0u;

/********functions-prototypes*******/
int32_t Shell_Exec(int8_t** param_argv);
bool Shell_IsBuiltInCmd(int8_t* param_line);
bool Shell_ExecBuiltInCmd(int8_t* param_line);
bool Shell_InitCMDCache(void);
int32_t Shell_CmpStrings(const void *param_Str1Ptr, const void *param_Str2Ptr);
int8_t* Shell_GetCMD(const int8_t* param_Str, int32_t state);
int8_t** Shell_Completion(const char *text, int start, int end);

/*******functions-implementations********/
bool Shell_GetExit(void)
{
    return Shell_global_ExitRequested_bool;
}

void Shell_SetExit(void)
{
    Shell_global_ExitRequested_bool = true;
}

void Shell_EngineMain(void)
{
    //int8_t shell_local_UserInput[SHELL_MAX_USER_INPUT_LEN_BYTES] = {'\0'};
    int8_t* shell_local_UserInput;
    int8_t* shell_local_saveptr;
    //int8_t* shell_local_TokensArray[SHELL_MAX_TOKENS_LEN_BYTES]  = {NULL};
    int8_t** shell_local_TokensArray;
    int32_t shell_local_TokenId = 0u;
    fflush(stdout);
    //Util_ModPrintf("AzharyShell:😀 ");
    //memset(shell_local_UserInput, '\0', SHELL_MAX_USER_INPUT_LEN_BYTES);
    //fgets(shell_local_UserInput, SHELL_MAX_USER_INPUT_LEN_BYTES, stdin);
    
    shell_local_UserInput = readline("AzharyShell: 😀 ");
    shell_local_TokensArray = (int8_t**) calloc( (strlen(shell_local_UserInput)+1), sizeof(int8_t*) );

    if(shell_local_UserInput != NULL)
    {
        add_history(shell_local_UserInput);
    }

    // Remove New Line Char from Input
    //shell_local_UserInput[strlen(shell_local_UserInput)-1] = '\0';

    if(Shell_global_DebugEnabled)
    {
        printf("User Input: %s, User Input Size: %ld\n", shell_local_UserInput, (strlen(shell_local_UserInput)+1) );
    }
    
    if(( shell_local_TokensArray != NULL ) && (shell_local_UserInput != NULL) )
    {
        if(shell_local_UserInput[0] != '\0')
        {
            shell_local_TokensArray[shell_local_TokenId] = strtok_r(shell_local_UserInput, " ", (char **) &shell_local_saveptr); 
            while(shell_local_TokensArray[shell_local_TokenId] != NULL)
            {
                shell_local_TokensArray[++shell_local_TokenId] = strtok_r(NULL, " ", (char **) &shell_local_saveptr); 
            }

            if( Shell_IsBuiltInCmd(shell_local_TokensArray[0]) )
            {
                // Command is Built-In     
                if(Shell_global_DebugEnabled)
                {
                    printf("BuiltIn CMD Detected: %s\n", shell_local_TokensArray[0]);
                }       
                if(false == Shell_ExecBuiltInCmd(shell_local_TokensArray[0]) )
                {
                    printf("Failed to Execute Build-In CMD:%s \n", shell_local_TokensArray[0]);
                }
            }
            else
            {
                if(Shell_global_DebugEnabled)
                {
                    printf("Non-BuiltIn CMD Detected: %s\n", shell_local_TokensArray[0]);
                }  
                // Command is Not Built-In
                if( -1 == Shell_Exec(shell_local_TokensArray) )
                {
                    Shell_global_ExitRequested_bool = true;
                }
            }
        }
        free(shell_local_UserInput);
        free(shell_local_TokensArray);
    }
}

int32_t Shell_Exec(int8_t** param_argv)
{    
    int32_t local_RetValue = 0;
    int32_t Shell_local_CPID_Status = 0;
    Shell_global_PPID = getpid();
    __pid_t Shell_local_PID = fork();

    if(Shell_local_PID > 0)
    {        
        Shell_global_CPID = Shell_local_PID;
        // This is Parent Process Code
        // Return Code of fork is PID of Child Process Code
        if(Shell_global_DebugEnabled)
        {
            printf("[PP] PPID: %d and CPID: %d\n", Shell_global_PPID, Shell_global_CPID);
            printf("[PP] PPID: %d is in wait state\n", Shell_global_PPID);
        }
        // Parent Process should wait until Child Process Finishes
        // This blocks the Parent Process until One of the Child Process exits or a signal
        // is received
        // Child Process may terminate if
        // - Child Process calls exit();
        // - Returns (an int) from main
        // - receives a signal (from OS or another Process) whose default action is to terminate
        waitpid(Shell_global_CPID, &Shell_local_CPID_Status, 0);
    }
    else if(Shell_local_PID == 0)
    {
        // This is Child Process Code
        // Return Code of fork is 0
        Shell_global_CPID = getpid();
        if(Shell_global_DebugEnabled)
        {
            printf("[CP] PPID: %d and CPID: %d\n", Shell_global_PPID, Shell_global_CPID);
            printf("[CP] CPID: %d is Executing\n", Shell_global_CPID);
        }

        // Command Not Built-In
        if( -1 != execvp((const char*) param_argv[0], (char * const*) param_argv) )
        {
            // If Excevp Succeeded, This line should not be reached
        }
        else
        {
            // Execvp Failed
            local_RetValue = -1;
        }
        Util_ModPrintf("Command Not Found\n");
    }
    else
    {
        // Fork Failed
        if(Shell_global_DebugEnabled)
        {
            printf("[PP] Engine Error: Internal Forking Failed\n");
            printf("[PP] Terminating Shell\n");
        }

        local_RetValue = -1;
    }

    return local_RetValue;
}

bool Shell_IsBuiltInCmd(int8_t* param_line)
{
    bool local_RetValue = false;    
    uint32_t local_BuiltInCmdsNumber = 0u, local_Index = 0u;

    if(Shell_global_BuiltInCmds != NULL)
    {
        local_BuiltInCmdsNumber = sizeof(Shell_global_BuiltInCmds)/sizeof(Shell_global_BuiltInCmds[0]);
        if(Shell_global_DeepInspectionEnabled)
        {
            printf("Number of Built-In CMDS: %d\n", local_BuiltInCmdsNumber);
        }

        for(local_Index=0; local_Index < local_BuiltInCmdsNumber; local_Index++)
        {
            if(0 == strncmp(Shell_global_BuiltInCmds[local_Index], param_line, strlen(Shell_global_BuiltInCmds[local_Index])))
            {
                local_RetValue = true;
                break;
            }
        }
    }

    return local_RetValue;
}

bool Shell_ExecBuiltInCmd(int8_t* param_line)
{
    bool local_RetValue = false;    

    if(0 == strncmp("exit", param_line, strlen(param_line)) )
    {
        Shell_global_ExitRequested_bool = true;
        local_RetValue = true;
        if(Shell_global_DebugEnabled)
        {
            printf("Built-In Exit CMD Executed\n");
        }
    }
    else if(0 == strncmp("editshell", param_line, strlen(param_line)) )
    {
        Util_EditSettings();
        local_RetValue = true;
        if(Shell_global_DebugEnabled)
        {
            printf("Built-In editshell CMD Executed\n");
        }
    }
    else
    {

    }

    return local_RetValue;
}

bool Shell_InitCMDCache(void)
{
    bool local_RetValue = true;
    // Read Environment Variable of PATH
    // And Get directories and the names of applications inside
    // PATH Will have a format like
    // /snap/bin:/snap/bin
    // We need to extract every path element, discover the apps inside and store them in our array
    // Our array for now is of indefinite size, we will create
    // it dynamically
    // lets first tokenize the PATH string
    // Its not allowed to modify directly in PATH
    // Hence we need to have a duplicate for it
    // Since we don't know its size we will create the string 
    // dynamically
    int8_t* shell_local_PATH_String = NULL;
    int8_t* shell_local_PATH_Dir = NULL;
    int32_t shell_local_CMD_Index = 0u;
    int8_t** shell_local_TempCachePtr = NULL;  
    DIR* local_Dir = NULL;
    struct dirent* local_Entry = NULL;

    if(getenv("PATH") != NULL)
    {
        shell_local_PATH_String = strdup( getenv("PATH") );

        if(shell_local_PATH_String != NULL)
        {
            shell_local_PATH_Dir = strtok(shell_local_PATH_String, ":");
            while(shell_local_PATH_Dir != NULL)
            {
                local_Dir = opendir(shell_local_PATH_Dir);
                if(local_Dir != NULL)
                {
                    while((local_Entry = readdir(local_Dir)) != NULL)
                    {
                        if((local_Entry->d_name)[0] != '.')
                        {
                            shell_global_CmdCacheCMDSNumber++;
                            shell_local_TempCachePtr = (int8_t**) realloc( shell_global_CmdCache, shell_global_CmdCacheCMDSNumber * sizeof(int8_t*) );
                            if( shell_local_TempCachePtr != NULL )
                            {
                                shell_global_CmdCache = shell_local_TempCachePtr;
                                shell_global_CmdCache[shell_local_CMD_Index] = strdup(local_Entry->d_name);
                                shell_local_CMD_Index++;
                            }
                        }
                    }               
                    closedir(local_Dir);
                }
                shell_local_PATH_Dir = strtok(NULL, ":");
            }

            if(shell_global_CmdCache != NULL)
            {
                qsort(shell_global_CmdCache, shell_global_CmdCacheCMDSNumber, sizeof(int8_t*), Shell_CmpStrings);

                if(Shell_global_DeepInspectionEnabled)
                {
                    printf("PATH:\n");
                }
                
                for(int32_t local_Id=0; local_Id < shell_local_CMD_Index; local_Id++)
                {
                    if(Shell_global_DeepInspectionEnabled)
                    {
                        printf("%s\n", shell_global_CmdCache[local_Id]);
                    }
                }
            }

            free(shell_local_PATH_String);
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

// Comparison function for qsort
int32_t Shell_CmpStrings(const void *param_Str1Ptr, const void *param_Str2Ptr) 
{
    return strcmp(*(const char**) param_Str1Ptr,*(const char**)  param_Str2Ptr);
}

bool Shell_EngineInit(void)
{
    bool local_RetValue = false;
    if(true == Shell_InitCMDCache())
    {
        rl_attempted_completion_function = (rl_completion_func_t *) Shell_Completion; 
        local_RetValue = true;
    }     
    return local_RetValue;
}

void Shell_EngineExitActions(void)
{
    __pid_t local_PID = 0;
    if (shell_global_CmdCache != NULL) {
        for (int32_t i = 0; i < shell_global_CmdCacheCMDSNumber; i++) {
            free(shell_global_CmdCache[i]); // Free each string
        }
        free(shell_global_CmdCache); // Free the pointer array
        shell_global_CmdCache = NULL;
    }       

    if(Shell_global_DebugEnabled)
    {
        local_PID = getpid();
        if(local_PID == Shell_global_PPID)
        {
            printf("PPID: %d is terminating\n",local_PID);
        }
        else if(local_PID == Shell_global_CPID)
        {
            printf("CPID: %d is terminating\n",local_PID);
        }
        else
        {
            printf("PID: %d is terminating\n",local_PID);
        }
    }
}

int8_t* Shell_GetCMD(const int8_t* param_Str, int32_t state)
{
    // This function shall be called repeatedly
    // Starting from state = 0
    // Until no further entries are found
    // matching param_Str partially hence
    // returns null
    static uint32_t local_Index = 0u;
    static uint32_t local_StrLen = 0u;
    int8_t* local_CMD_Ptr = NULL;
    if(state == 0)
    {
        //initial call
        local_Index = 0u;
        local_StrLen = strlen(param_Str);
    }

    while(local_Index < shell_global_CmdCacheCMDSNumber)
    {
        if( 0 == strncmp(param_Str, shell_global_CmdCache[local_Index], local_StrLen) )
        {
            // This is returned as string dup not the shell_global_CmdCache[local_Index]
            // because rl_completion_matches is destructive and will free the pointer
            // after its work is done, hence we donot want to destroy shell_global_CmdCache
            // but we can destroy a copy of the CMD string
            local_CMD_Ptr = strdup(shell_global_CmdCache[local_Index]);
            local_Index++;
            break;
        }
        local_Index++;
    }

    return local_CMD_Ptr;
}

int8_t** Shell_Completion(const char *text, int start, int end)
{
    int8_t** local_PossibleCMDsArray = NULL;
    // Only complete the first word
    if (start == 0) 
    {
        // rl_completion_matches function will create the array of CMD strings
        // using the Shell_GetCmD
        local_PossibleCMDsArray = (int8_t**) rl_completion_matches(text, (rl_compentry_func_t *) Shell_GetCMD);
    }
    return local_PossibleCMDsArray;
}
