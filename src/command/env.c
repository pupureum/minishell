#include "minishell.h"

extern t_minishell	g_shell;

int	get_env()
{
	t_list	*envp;

	envp = g_shell.env_list;
	while (envp)
	{
		printf ("%s\n", (char *)(envp->content));
		envp = envp->next;
	}
	return (SUCCESS);
}
