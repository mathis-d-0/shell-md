    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        
   } else {
       perror("getcwd() error");
       return 1;
   }

    printf("%s", cwd);