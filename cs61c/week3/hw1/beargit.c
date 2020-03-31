#include <stdio.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

#include "beargit.h"
#include "util.h"

/* Implementation Notes:
 *
 * - Functions return 0 if successful, 1 if there is an error.
 * - All error conditions in the function description need to be implemented
 *   and written to stderr. We catch some additional errors for you in main.c.
 * - Output to stdout needs to be exactly as specified in the function
 * description.
 * - Only edit this file (beargit.c)
 * - You are given the following helper functions:
 *   * fs_mkdir(dirname): create directory <dirname>
 *   * fs_rm(filename): delete file <filename>
 *   * fs_mv(src,dst): move file <src> to <dst>, overwriting <dst> if it exists
 *   * fs_cp(src,dst): copy file <src> to <dst>, overwriting <dst> if it exists
 *   * write_string_to_file(filename,str): write <str> to filename (overwriting
 * contents)
 *   * read_string_from_file(filename,str,size): read a string of at most <size>
 * (incl. NULL character) from file <filename> and store it into <str>. Note
 * that <str> needs to be large enough to hold that string.
 *  - You NEED to test your code. The autograder we provide does not contain the
 *    full set of tests that we will run on your code. See "Step 5" in the
 * homework spec.
 */

/* beargit init
 *
 * - Create .beargit directory
 * - Create empty .beargit/.index file
 * - Create .beargit/.prev file containing 0..0 commit id
 *
 * Output (to stdout):
 * - None if successful
 */

int beargit_init(void) {
  fs_mkdir(".beargit");

  FILE *findex = fopen(".beargit/.index", "w");
  fclose(findex);

  write_string_to_file(".beargit/.prev",
                       "0000000000000000000000000000000000000000");

  return 0;
}

/* beargit add <filename>
 *
 * - Append filename to list in .beargit/.index if it isn't in there yet
 *
 * Possible errors (to stderr):
 * >> ERROR: File <filename> already added
 *
 * Output (to stdout):
 * - None if successful
 */

int beargit_add(const char *filename) {
  FILE *findex = fopen(".beargit/.index", "r");
  // opens the .index file for reading
  FILE *fnewindex = fopen(".beargit/.newindex", "w");
  // opens the .newindex file for writing, and (presumably) also creates it
  char line[FILENAME_SIZE]; // creates a new string as big as the line size?
  while (fgets(line, sizeof(line), findex)) {
    // gets a line from file, puts it in line, and loops until done.
    strtok(line, "\n");                // splits the string by \n
    if (strcmp(line, filename) == 0) { // compares string, checks if same
      fprintf(stderr, "ERROR: File %s already added\n", filename);
      fclose(findex);              // close file
      fclose(fnewindex);           // close new file
      fs_rm(".beargit/.newindex"); // delete new file
      return 3;                    // return error code
    }

    fprintf(fnewindex, "%s\n", line);
    // fprintf puts the existing file into the temp file
  }

  fprintf(fnewindex, "%s\n", filename);
  // appends the new filename into the temp file
  fclose(findex);    // close old file
  fclose(fnewindex); // close temp file

  fs_mv(".beargit/.newindex", ".beargit/.index"); // makes temp file actual file

  return 0;
}

/* beargit rm <filename>
 *
 * See "Step 2" in the homework 1 spec.
 *
 */

int beargit_rm(const char *filename) {
  FILE *index = fopen(".beargit/.index", "r");
  FILE *temp_index = fopen(".beargit/.newindex", "w");
  char filename_to_find[FILENAME_SIZE];
  int found = 0;

  while (fgets(filename_to_find, sizeof(filename_to_find), index)) {
    strtok(filename_to_find, "\n");
    if (strcmp(filename_to_find, filename) == 0) {
      found = 1;
    } else {
      // magic is that we loop through the file, and if we DONT see our
      // filename, we add to our temp file we then use this to overwrite later
      fprintf(temp_index, "%s\n", filename_to_find);
    }
  }
  fclose(index);
  fclose(temp_index);
  fs_mv(".beargit/.newindex", ".beargit/.index");
  if (found == 0) {
    fprintf(stderr, "ERROR: File %s not tracked\n", filename);
    return 1;
  }
  return 0;
}

/* beargit commit -m <msg>
 *
 * See "Step 3" in the homework 1 spec.
 *
 */

const char *go_bears = "GO BEARS!";

int is_commit_msg_ok(const char *msg) {
  const char *BEARS_MESSAGE[] = "GO BEARS!";

  int function_exiter = 0;
  int bears_iterator = 0;
  int i;

  for (i = 0; *msg != '\0'; msg++) {
    if (*msg == bears_count[i]) {
      function_exiter = 1;
      if (bears_count[i + 1] == '\0') {
        return 1;
      }
      i++;
    } else if (function_exiter == 1) {
      // we enter here if the last character matched, but this one did not.
      function_exiter = 0;
      i = 0;
    }
  }

  return 0;
}

void next_commit_id(char *commit_id) { /* COMPLETE THE REST */
}

int beargit_commit(const char *msg) {
  if (!is_commit_msg_ok(msg)) {
    fprintf(stderr, "ERROR: Message must contain \"%s\"\n", go_bears);
    return 1;
  }

  char commit_id[COMMIT_ID_SIZE];
  read_string_from_file(".beargit/.prev", commit_id, COMMIT_ID_SIZE);
  next_commit_id(commit_id);

  /* COMPLETE THE REST */

  return 0;
}

/* beargit status
 *
 * See "Step 1" in the homework 1 spec.
 *
 */

int beargit_status() {
  char *buffer = 0;
  long size;
  FILE *file_pointer = fopen(".beargit/.index", "r");
  int line_count = 0;

  ASSERT_ERROR_MESSAGE(file_pointer != NULL, "couldn't open file, soz");

  fseek(file_pointer, 0, SEEK_END);
  size = ftell(file_pointer);
  fseek(file_pointer, 0, SEEK_SET);
  buffer = malloc(size);
  if (buffer) {
    fread(buffer, 1, size, file_pointer);
  }
  fclose(file_pointer);

  const char *p = &buffer[0];
  for (int i = 0; i < size; i++) {
    if (p[i] == '\n') {
      line_count++;
    }
  }

  if (buffer) {
    printf("Tracked files:\n");
    printf("\n");
    printf("%s\n", buffer);
    printf("%d files total\n", line_count);
  } else {
    printf("Something went wrong, sorry. Try again?");
  }

  // its printing some null pointer value for some reason but pretty good!
  return 0;
}

/* beargit log
 *
 * See "Step 4" in the homework 1 spec.
 *
 */

int beargit_log() {
  /* COMPLETE THE REST */

  return 0;
}
