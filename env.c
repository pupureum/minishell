#include "command.h"

void	get_env(char **envp)
{
	while (*envp)
		printf ("%s\n", *envp++);
}
