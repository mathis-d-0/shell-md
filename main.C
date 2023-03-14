#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ARGS 15
#define MAX_PATH 50
#define MAX_INPUT_LENGHT 1024
#define F_OK 0



void Initialize()
{

    system("clear");
    char* configfile = "Test";

    if (access(configfile, F_OK) == 0) {
        
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

int PrintPrompt()
{
    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {

   } else {
       perror("getcwd() error");
       return 1;
   }
    printf("root@local:%s$ ", cwd);
}

void DisplayHelp()
{
    system("clear");
    printf("Help\n");
}

void ChangeDirectory(char *dir)
{
    if (dir == NULL) {
        printf("Error: no directory specified.\n");
    } else if (chdir(dir) != 0) {
        printf("Error: could not change directory to %s.\n", dir);
    }
}

int main()
{

    Initialize();
    DisplaySplashScreen();
    char usr_input[MAX_INPUT_LENGHT];
    char *args[MAX_ARGS];
    char *token;
    pid_t pid;
    int status;

    while (1)
    {
        PrintPrompt();

        fgets(usr_input, MAX_INPUT_LENGHT, stdin);

        


        token = strtok(usr_input, " \n");
        int i = 0;
        while(token != NULL && i < MAX_ARGS) {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL;


        if(strtok(usr_input," \n\t") == NULL) continue;
        if(strcmp(usr_input, "exit") == 0) return 0;
        if(strcmp(usr_input, "help") == 0) DisplayHelp();
        if (strcmp(args[0], "cd") == 0) {
            ChangeDirectory(args[1]);
            continue;
        }


        if((pid = fork()) < 0) {
            printf("Error: fork failed.\n");
            exit(1);
        } else if(pid == 0) {
            if(execvp(args[0], args) < 0) {
                printf("Error: command \"%s\" not found.\n", args[0]);
                exit(1);
            }
        } else {
            waitpid(pid, &status, 0);
        }
        
    }

    
    return 0;
}