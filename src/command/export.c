#include "minishell.h"

extern t_minishell	g_shell;

void	convert_env(char *arg)
{
	char	**value;
	char	**envp;
	t_list	*cur;

	cur = g_shell.env_list;
	value = ft_split(arg, '=');
	if (value == NULL)
		malloc_error();
	while (cur)
	{
		envp = ft_split((char *)(g_shell.env_list->content), '=');
		if (envp == NULL)
			malloc_error();
		if (ft_strncmp(envp[0], value[0], ft_strlen(value[0]) + 1) == 0
			&& (ft_strchr(arg, '=') != NULL))
		{
			g_shell.env_list->content = arg;
			free_str(envp);
			free_str(value);
			return ;
		}
		cur = cur->next;
		free_str(envp);
	}
	free_str(value);
}

int	update_envp(char **envp, char *arg)
{
	char	**value;

	value = ft_split(arg, '=');
	if (value == NULL)
		malloc_error();
	if (ft_strncmp(envp[0], value[0], ft_strlen(value[0]) + 1) == 0
		&& (ft_strchr(arg, '=') != NULL))
	{
		g_shell.export_list->content = arg;
		convert_env(arg);
		g_shell.export_list = g_shell.export_list->next;
		free_str(value);
		free_str(envp);
		return (END);
	}
	else if (ft_strncmp(envp[0], value[0], ft_strlen(value[0]) + 1) == 0
		&& (ft_strchr(arg, '=') == NULL))
	{
		g_shell.export_list = g_shell.export_list->next;
		free_str(value);
		free_str(envp);
		return (END);
	}
	free_str(value);
	return (0);
}

int	check_dup(char *arg)
{
	char	**envp;
	int		result;
	t_list	*cur;

	cur = g_shell.export_list;
	while (cur)
	{
		envp = ft_split(g_shell.export_list->content, '=');
		result = update_envp(envp, arg);
		if (result == END)
			return (END);
		cur = cur->next;
		free_str(envp);
	}
	return (0);
}

void	append_envp(char *arg)
{
	if (ft_strchr(arg, '=') != NULL)
	{
		if (check_dup(arg) == 0)
			add_to_list(arg, 2);
	}
	else
	{
		if (check_dup(arg) == 0)
			add_to_list(arg, 1);
	}
}

t_error	run_export(t_list *args)
{
	// int		i;
	// int		len;

	// i = 0;
	// len = ft_lstsize(args);
	// if (len == 0)
	// 	print_export_list(g_shell.export_list);
	// else
	// {
	// 	while (args)
	// 	{
	// 		append_envp((char *)(args->content));
	// 		args = args->next;
	// 	}
	// }
	return (SUCCESS);
}
