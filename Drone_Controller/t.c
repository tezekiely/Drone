#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getName()
{
    char *str = malloc(sizeof(char) * 20);

    strcpy(str, "Mars");

    return str;
}

int main()
{
    char *name;

    name = getName();

    printf("%s\n", name);

    free(name);

    return 0;
}