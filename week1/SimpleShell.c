#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LEN 1000
#define NUM_COMMANDS 100
#define MAX_ARGS 100

void execute_command(char *input) {
    // Tokenize the input into command and arguments
    char *args[MAX_ARGS];
    char *token;
    int i = 0;

    token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS - 1){
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid_t pid = fork();
    if(pid == -1){
        perror("Fork failed");
        return;
    }
    if(pid){ // Parent Process
        int status;
        waitpid(pid, &status, 0);
    }
    else{ // Child process
        if(execvp(args[0], args) < 0){
            perror("Execution failed");
        }
    }
}

void parallel_execute_commands(char *input) {
    char *commands[NUM_COMMANDS], *args[MAX_ARGS];
    char *token1, *token2, *temp;
    token1 = strtok(input, ";");
    int num_commands = 0;
    while(token1 != NULL && num_commands < NUM_COMMANDS){
        commands[num_commands++] = token1;
        token1 = strtok(NULL, ";");
    }
    pid_t pid[NUM_COMMANDS];
    for(int i = 0; i < num_commands; i++){
        pid[i] = fork();
        if(pid[i] == -1){
            perror("Fork failed");
            continue;
        }
        if(pid[i] == 0) {  // Child process
            char *args[MAX_ARGS];
            char *token;
            int j = 0;
            token = strtok(commands[i], " ");
            while (token != NULL && j < MAX_ARGS - 1){
                args[j++] = token;
                token = strtok(NULL, " ");
            }
            args[j] = NULL;
            if(execvp(args[0], args) < 0){
                perror("Execution failed");
            }
        }
    }
    for (int i = 0; i < num_commands; i++) {
        if (pid[i] > 0) { // Parent process
            waitpid(pid[i], NULL, 0);
        }
    }
}

int main() {
    char command[LEN];

    while(1){
        printf("myshell> ");
        fflush(stdout);

        // Read input
        fgets(command, LEN, stdin);
        for(int i = 0; i < LEN; i++){
            if(command[i] == '\n'){
                command[i] = '\0';
                break;
            }
        }
        
        // Check for exit command
        if(!strcmp(command, "exit")) break;
        if(!strncmp(command, "parallel", 8)) parallel_execute_commands(command + 9);
        else execute_command(command);
    }

    return 0;
}
