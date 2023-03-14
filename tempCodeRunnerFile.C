#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_LENGHT 1024
#define F_OK 0



void Initialize()
{
    system("clear");
    char* configfile = "Test";

    if (access(configfile, F_OK) == 0) {
        printf("Reading config file.\n\n");
    } 
    else {
        printf("!! No config file in home diectory !!\n\n");
    }
}

void DisplaySplashScreen()
{
    char* asciiArt = "  __  __ _____   _____ _          _ _ \n"
" |  \\/  |  __ \\ / ____| |        | | |\n"
" | \\  / | |  | | (___ | |__   ___| | |\n"
" | |\\/| | |  | |\\___ \\| '_ \\ / _ \\ | |\n"
" | |  | | |__| |____) | | | |  __/ | |\n"
" |_|  |_|_____/|_____/|_| |_|\\___|_|_|\n";


printf("%s", asciiArt);
printf("\n\nWelcome to MDShell!\n");
printf("You can type commands like any other shell.\n\n");
}

void PrintPrompt()
{
    printf("root@local:/dev$ ");
}

void DisplayHelp()
{
    system("clear");
    printf("Help\n");
}

void ChangeDirectory()
{
    printf("cd\n");
}

int main()
{

    Initialize();
    DisplaySplashScreen();
    char usr_input[MAX_INPUT_LENGHT];
    while (1)
    {
        PrintPrompt();

        fgets(usr_input, MAX_INPUT_LENGHT, stdin);

        if(strtok(usr_input," \n\t") == NULL) continue;
        if(strcmp(usr_input, "exit") == 0) return 0;
        if(strcmp(usr_input, "help") == 0) DisplayHelp();
        if(strcmp(usr_input, "cd") == 0) ChangeDirectory();
 
        
    }

    
    return 0;
}