/*********************
* File Name     : engine.h
* Description   : Execution Engine responsible for Process Management
*               : and built in commands
* Date          : 09.02.2026
* Author        : Mohamed El Azhary
* Version       : 1.0
**********************/
#ifndef _ENGINE_H
#define _ENGINE_H

/*********Includes**********/
#include "stdbool.h"

/**********Macros***********/

/*********Typedefs**********/

/*********global-variables********/

/********functions-prototypes*******/
bool Shell_GetExit(void);
void Shell_SetExit(void);
void Shell_EngineMain(void);
bool Shell_InitCMDCache(void);
bool Shell_EngineInit(void);
void Shell_EngineExitActions(void);

/*******functions-implementations********/


#endif // End of #ifndef