#include "minishell.h"

void	get_env(t_list *envp)
{
	while (envp)
	{
		printf ("%s\n", (char *)(envp->content));
		envp = envp->next;
	}
}
