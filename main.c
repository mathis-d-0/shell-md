#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// -- Define the text styles
#define TXT_NRM "\033[0m"
#define TXT_BOL "\033[1m"
#define TXT_DIM "\033[2m"
#define TXT_UND "\033[4m"
#define TXT_BLI "\033[5m"

// -- Define the text colors
#define COLOR_NRM  "\x1B[0m"
#define COLOR_RED  "\x1B[1;31m"
#define COLOR_GRN  "\x1B[1;32m"
#define COLOR_YEL  "\x1B[1;33m"
#define COLOR_BLU  "\x1B[1;34m"
#define COLOR_MAG  "\x1B[1;35m"
#define COLOR_CYN  "\x1B[1;36m"
#define COLOR_WHT  "\x1B[1;37m"

// -- Define the text backgrounds
#define BG_NRM "\e[49m"
#define BG_DGR "\e[100m"

// -- Define the general constants
#define MAX_ARGS 15
#define MAX_PATH 50
#define MAX_INPUT_LENGHT 1024
#define F_OK 0


// 
// ---- Function for the basic elements ----
//
int Initialize()
{

    system("clear");
    char* homedir = getenv("HOME");
    char* configfile = "Test";

    if (access(configfile, F_OK) == 0) {
        
    } 
    else {
        printf("!! No config file in home diectory !!\n\n");
    }


    int result = putenv("CLICOLOR=1");
    if (result != 0) {
        perror("putenv failed");
        return 1;
    }
}


// 
// ---- Function for the splashscreen ----
//
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
printf("%sYou can type commands like any other shell.%s\n\n", TXT_DIM, TXT_NRM);
printf("Type %s%sexit%s%s to exit the shell and %s%shelp%s%s to get help.\n\n",TXT_BOL, COLOR_YEL, TXT_NRM, COLOR_NRM, TXT_BOL, COLOR_YEL, TXT_NRM, COLOR_NRM);
}


// 
// ---- Function for the prompt ----
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

    time_t current_time;
    struct tm* time_info;
    char time_string[9];

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);

    printf("%s╭%s%s%s %s%s@%s%s:%s%s%s\n╰$ ", TXT_BOL, BG_DGR, time_string, BG_NRM, COLOR_BLU, username, hostname, COLOR_NRM, COLOR_YEL, cwd, COLOR_NRM);

}


// 
// ---- Function for the help page ----
//
void DisplayHelp()
{
    system("clear");
    printf("Help\n");
}


// 
// ---- Function for the cd command ----
//
void ChangeDirectory(char *dir)
{
    if (dir == NULL) {
        printf("Error: no directory specified.\n");
    } else if (chdir(dir) != 0) {
        printf("Error: could not change directory to %s.\n", dir);
    }
}


// 
// ---- Main function ----
//
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


        if(strtok(usr_input," \n\t") == NULL) {
            printf("\n");
            continue;
        }
        if(strcmp(usr_input, "exit") == 0) return 0;
        if(strcmp(usr_input, "help") == 0) DisplayHelp();
        if (strcmp(args[0], "cd") == 0) {
            ChangeDirectory(args[1]);
            printf("\n");
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
        printf("\n");
    }
    return 0;
}