#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define TXT_BOLD "\033[1m"
#define TXT_NRM "\033[0m"

#define COLOR_NRM  "\x1B[0m"
#define COLOR_RED  "\x1B[1;31m"
#define COLOR_GRN  "\x1B[1;32m"
#define COLOR_YEL  "\x1B[1;33m"
#define COLOR_BLU  "\x1B[1;34m"
#define COLOR_MAG  "\x1B[1;35m"
#define COLOR_CYN  "\x1B[1;36m"
#define COLOR_WHT  "\x1B[1;37m"

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
printf("Type %s%sexit%s%s to exit the shell and %s%shelp%s%s to get help.\n\n",TXT_BOLD, COLOR_YEL, TXT_NRM, COLOR_NRM, TXT_BOLD, COLOR_YEL, TXT_NRM, COLOR_NRM);
}

// 
// Print the prompt
//
int PrintPrompt()
{

    //Get the current path
    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
   } else {
       perror("getcwd() error");
       return 1;
   }

   //Reduce the user directory to "~"
    char* homedir = getenv("HOME");
    if (homedir != NULL && strncmp(cwd, homedir, strlen(homedir)) == 0) {
        snprintf(cwd, sizeof(cwd), "~%s", cwd + strlen(homedir));
    }

    //Get the username
    char *username = getlogin();

    //Get the hostname
   char hostname[25];
   if (gethostname(hostname, 25) == 0) { 
   } else {
    perror("gethostname() error");
    return 1;
   }


    printf("%s%s@%s%s:%s%s%s$ ", COLOR_GRN, username, hostname, COLOR_NRM, COLOR_BLU, cwd, COLOR_NRM);

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
        
        // Get user input
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
