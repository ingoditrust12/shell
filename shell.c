#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    while (1) {
        // Prompt for user input
        printf("Shell > ");

        // Read the command from the user
        char command[100];
        fgets(command, sizeof(command), stdin);

        // Remove the trailing newline character
        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }

        // Check if the user wants to exit
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Create a child process
        pid_t child_pid = fork();

        if (child_pid == -1) {
            // Error occurred while forking
            perror("fork failed");
            return 1;
        } else if (child_pid == 0) {
            // Child process
            execl(command, command, NULL);
            perror("execl failed");
            exit(1);
        } else {
            // Parent process
            int status;
            waitpid(child_pid, &status, 0);
        }
    }

    return 0;
}

