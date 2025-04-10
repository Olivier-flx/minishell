#include <stdio.h>
#include <stdlib.h>

int main() {
    char *path = getenv("PATH");
    if (path) printf("PATH EN C: %s\n", path);
    else printf("PATH no encontrado\n");
    return 0;
}