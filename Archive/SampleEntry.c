#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char command[256];

    if (argc < 2) {
        printf("Usage: %s <input>\n", argv[0]);
        return 1;
    }

    sprintf(command, "echo %s", argv[1]);
    system(command);

    return 0;
}