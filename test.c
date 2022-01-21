#include "aqadil/minishell.h"





int main (void)
{
    char *path;

    path = getenv("PATH");


    printf("%s", path);
}