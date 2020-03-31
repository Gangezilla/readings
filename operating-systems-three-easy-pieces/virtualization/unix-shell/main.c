#include <stdio.h>
#include <stdlib.h>

void process_command(char *command) { printf("command: %s \n", command); }

int main(int argc, char **argv) {
  char *command_buffer;
  size_t bufsize = 32;
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