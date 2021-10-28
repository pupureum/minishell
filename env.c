#include "command.h"

void	get_env(t_list *envp)
{
	while (envp)
	{
		printf ("%s\n", envp->content);
		envp = envp->next; 
	}
}
