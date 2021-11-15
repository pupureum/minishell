#include "minishell.h"

extern t_minishell	g_shell;

void	malloc_error(void)
{
	printf("Malloc Error\n");
	exit(0);
}

void	add_to_list(char *token, int num)
{
	char	*arg;
	t_list	*new;

	arg = ft_strdup(token);
	new = ft_lstnew(token);
	if (arg == NULL || new == NULL)
		error(MALLOC_ERROR);
	if (num == 2)
	{
		ft_lstadd_back(&g_shell.export_list, new);
		ft_lstadd_back(&g_shell.env_list, new);
	}
	else
		ft_lstadd_back(&g_shell.export_list, new);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	token_size(char **token)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (token[i++])
		len++;
	return (len);
}
