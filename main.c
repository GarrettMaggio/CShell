#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ; // declares an external variable. Which is a pointer to an array of strings

int main(void) {
    char user_input[200];
    char path_to_search[120];
    char command_input[9];

    int m = 0;
    // intentional infinite loop
    while (m < 1 ) {
        printf("%s", "Please enter a command.\n");
        fgets(user_input, 200, stdin);
        user_input[strcspn(user_input, "\n")] = '\0'; // this line eliminates the newline character the fgets adds in the character array.
        //  the '\n' character gets replaced with the null terminator '\0'
        // not putting it here caused errors when parsing the input.

        int i = 0, j = 0;

        while (user_input[i] != '\0' && user_input[i] != ' ' && i < sizeof(command_input)) {
            command_input[i] = user_input[i];
            i++;
        }
        command_input[i] = '\0';

        if (user_input[i] == ' ') {
            i++;
        }

        while ( user_input[i] != '\0' && j < sizeof(path_to_search))  {
            if (user_input[i] >= 32 && user_input[i] <= 126) {
                path_to_search[j] = user_input[i];
                j++;
            }
            i++;
        }
        path_to_search[j] = '\0';

        /*
            for (int j = 0; path_to_search[j] != '\0'; j++) {
                printf("%c", path_to_search[j]);
            }


            for (int i = 0; command_input[i] != '\0'; i++) {
                printf("%c", command_input[i]);
            }
        */

        memset(user_input, 0, sizeof(user_input));

        if (strcmp ("myclear", command_input) == 0) {
            system("clear");
        }
        if (strcmp ("mydir", command_input) == 0) {
            if (path_to_search > 0) {
                sprintf(user_input, "ls -la %s", path_to_search );
                system(user_input);
            }
            else {
                strcpy(path_to_search, ".");
                sprintf(user_input, "ls -la %s", path_to_search);
                system(user_input);
            }
        }

        //  myenviron ---
        if (strcmp("myenviron", command_input) == 0) {

            char ** e = environ; // local pointer to the array of strings that environ points too
            while (*e) { // while e is not null
                printf("%s\n", *e++); // print the current environment string and increment to the next string
            }
        }

            if (strcmp ("myquit", command_input) == 0) {
                system("exit");
                return 0;
            }

        if (strcmp ("mydir", command_input) != 0 && strcmp ("myenviron", command_input) != 0 && strcmp ("myquit", command_input) != 0 && strcmp ("myclear", command_input) != 0) {

            if (strlen(path_to_search) < 1) {
                strcpy(path_to_search, " ");
                char *token = strtok(command_input, " ");
                if (token != NULL) {
                    strcpy(user_input, token);
                    system(user_input);
                }
            }
            else {
                char *token = strtok(command_input, " "); // path to search is not an actual path it is optional add on's to the command.
                if (token != NULL) {
                    strcpy(user_input, token);
                    strcat (user_input, " ");
                    strcat(user_input, path_to_search);
                    system(user_input);
                }
            }
        }

        }

    }

