#include <stdio.h>

void	get_env(char **envp)
{
	while(*envp)
	printf("%s\n", *envp++);
}
int    main(int argc, char **argv, char **envp)
{
    get_env(envp);
    return (0);
}