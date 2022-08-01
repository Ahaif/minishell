#include "./include/readline/readline.h"
#include <unistd.h>


int main(void)
{
    int i = 0;
    if (i < 10)
    {
        rl_on_new_line();
        sleep(1);
    }
    readline("rules \n");
    rl_clear_history();
}