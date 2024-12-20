/**
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/include/toolbox.h"
#include "test_cmds.h"

#define LINESIZE 128

char line[LINESIZE];

void yyerror(char * s) {
    printf("\n\nError: %s\n", s);
}

void readline(char * l) {
    sys_chan_readline(0, l, LINESIZE);
}

int strindex(char * str, char c) {
    for (int x = 0; x < strlen(str); x++) {
        if (str[x] == 0) {
            return -1;
        } else if (str[x] == c) {
            return x;
        }
    }

    return -1;
}

char * next_string(char * src, char * dest) {
    dest[0] = 0;

    int start = strindex(src, '\"');
    if (start >= 0) {
        char * substring = src + start + 1;
        int end = strindex(substring, '\"');
        if (strindex >= 0) {
            substring[end] = 0;
            strcpy(dest, substring);
            return substring + end + 1;
        }
    }

    return 0;
}

void parse(char * line) {
    char * tok = strtok(line, " ");
    if (tok) {
        if (strcmp(tok, "set-border-size") == 0) {
            tok = strtok(NULL, " ");
            if (tok) {
                short size = atoi(tok);
                cmd_set_border_size(size, size);
                return;
            }

        } else if (strcmp(tok, "set-border-color") == 0) {
            char * red = strtok(NULL, " ");
            if (red) {
                char * green = strtok(NULL, " ");
                if (green) {
                    char * blue = strtok(NULL, " ");

                    cmd_set_border_color(atoi(red), atoi(green), atoi(blue));
                    return;
                }
            }

        } else if (strcmp(tok, "dir") == 0) {
            char * path = strtok(NULL, " ");
            cmd_dir(path);
            return;

        } else if (strcmp(tok, "more") == 0) {
            char * path = strtok(NULL, " ");
            cmd_more(path);
            return;

        } else if (strcmp(tok, "ren") == 0) {
            char * path1 = strtok(NULL, " ");
            if (path1) {
                char * path2 = strtok(NULL, " ");
                printf("Renaming %s to %s\n", path1, path2);
                cmd_rename(path2, path1);
                return;
            }

        } else if (strcmp(tok, "del") == 0) {
            char * path = strtok(NULL, " ");
            cmd_delete(path);
            return;
        }
    }

    printf("Syntax error.\n");
}

void repl() {
    do {
        printf("\n> ");
        readline(line);
        printf("\n");
        parse(line);
    } while(1);
}

int main(int argc, char * argv[]) {
    printf("Welcome to the Foenix Toolbox Tester\n\n");
    int x = 23;
    int y = 54;
    printf("%d\n", x * y);
    repl();
    return 0;
}