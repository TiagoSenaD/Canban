#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

int scan_int(int *value) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%d", value) == 1) {
            return 1;
        }
        return -1;
    }
    return -1;
}