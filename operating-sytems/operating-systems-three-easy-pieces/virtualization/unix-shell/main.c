#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char path[5] = "/bin";
char *program_path[];
char *arguments[2]; // currently only working for la -la, need to amend this.

void spawn_new_process(char *command) {
  pid_t child_pid;
  int child_status;

  char *args[30];

  int len = strlen(command);
  if (len > 0 && command[len - 1] == '\n') {
    command[len - 1] = '\0';
  }

  char *pch = strtok(command, " ");

  int i = 0;
  while (pch != NULL) {
    if (i == 0) {
      strcpy(program_path, pch);
      i++;
    } else {
      arguments[i++] = pch;
      pch = strtok(NULL, "");
    }
  }

  child_pid = fork();
  if (child_pid < 0) {
    // If we can't generate a new process.
    fprintf(stderr, "Fork failed\n");
    exit(1);
  } else if (child_pid == 0) {
    // This gets run by the child process
    execvp(program_path, arguments);
    // If execvp returns, it must have failed.
    printf("Unknown command\n");
    exit(0);
  } else {
    // This is run by the parent while it waits for the child process.
    int child_pid_wait = wait(NULL);
  }
}

void process_command(char *command) {
  if (strncmp(command, "exit", 4) == 0) {
    exit(0);
  } else if (strncmp(command, "cd", 2) == 0) {
    printf("cd: %s", command);
  } else if (strncmp(command, "path", 4) == 0) {
    printf("path: %s", command);
  } else {
    spawn_new_process(command);
  }
}

int main(int argc, char **argv) {
  char *command_buffer;
  size_t bufsize = 100;
  size_t current_command;

  command_buffer = (char *)malloc(bufsize * sizeof(char));

  if (command_buffer == NULL) {
    perror("Unable to allocate buffer");
  }

  while (1) {
    printf("schell> ");
    current_command = getline(&command_buffer, &bufsize, stdin);
    process_command(command_buffer);
  }
}


var s = "¡¡¡Hello, Gophers!!!"
	s = strings.TrimSuffix(s, ", Gophers!!!")
	s = strings.TrimSuffix(s, ", Marmots!!!")
	fmt.Print(s)