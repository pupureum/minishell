#include "minishell.h"

extern t_minishell	g_shell;

/* void	convert_env(char *arg)
{
	char	**value_head;
	char	*value;
	char	**envp;
	t_list	*cur;

	cur = g_shell.env_list;

	value_head = ft_split(arg, '=');
	value = ft_strdup(arg);
	if (value_head == NULL)
		malloc_error();
	while (cur)
	{
		envp = ft_split((char *)(cur->content), '=');
		if (envp == NULL)
			malloc_error();
		if (ft_strncmp(envp[0], value_head[0], ft_strlen(value_head[0]) + 1) == 0
			&& (ft_strchr(arg, '=') != NULL))
		{
			free(cur->content);
			cur->content = value;
			free_str(envp);
			free_str(value_head);
			return ;
		}
		cur = cur->next;
		free_str(envp);
	}
	free_str(value_head);
}

int	update_envp(t_list *cur, char **envp, char *arg)
{
	char	**value_head;
	char	*value;

	value_head = ft_split(arg, '=');
	value = ft_strdup(arg);
	if (value_head == NULL || value == NULL)
		malloc_error();
	if (ft_strncmp(envp[0], value_head[0], ft_strlen(value_head[0]) + 1) == 0
		&& (ft_strchr(arg, '=') != NULL))
	{
		free(cur->content);
		cur->content = value;
		convert_env(value);
		free_str(value_head);
		free_str(envp);
		return (END);
	}
	else if (ft_strncmp(envp[0], value_head[0], ft_strlen(value_head[0]) + 1) == 0
		&& (ft_strchr(arg, '=') == NULL))
	{
		free_str(value_head);
		return (END);
	}
	free_str(value_head);
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
		envp = ft_split(cur->content, '=');
		result = update_envp(cur, envp, arg);
		if (result == END)
			return (END);
		cur = cur->next;
		free_str(envp);
	}
	return (0);
} */

void	update_env_val(t_list *env_list, char *arg)
{
	t_list	*curr;
	char	**env_key_val;
	char	**arg_key_val;
	int		result;

	curr = env_list;
	result = 0;
	arg_key_val = ft_split(arg, '=');
	if (arg_key_val == NULL)
		error(MALLOC_ERROR);
	while (curr && result == 0)
	{
		env_key_val = ft_split(curr->content, '=');
		if (ft_strncmp(arg_key_val[0], env_key_val[0], ft_strlen(arg_key_val[0]) + 1) == 0)
		{
			free(curr->content);
			curr->content = arg;
			result = 1;
		}
		free_str(env_key_val);
		curr = curr->next;
	}
	free_str(arg_key_val);
}

int	check_dup(char *arg)
{
	char	**env_key_val;
	char	**arg_key_val;
	t_list	*curr;
	int		result;	

	curr = g_shell.export_list;
	arg_key_val = ft_split(arg, '=');
	result = 0;
	if (arg_key_val == NULL)
		error(MALLOC_ERROR);
	while (curr && result == 0)
	{
		env_key_val = ft_split(curr->content, '=');
		if (ft_strncmp(arg_key_val[0], env_key_val[0], ft_strlen(arg_key_val[0]) + 1) == 0)
			result = 1;
		free_str(env_key_val);
		curr = curr->next;
	}
	free_str(arg_key_val);
	return (result);
}

int	append_envp(char *arg)
{
	if (arg[0] == '=')
	{
		printf("bash: export: '%s': not a valid identifier\n", arg);
		return (1);
	}
	if (ft_strchr(arg, '=') != NULL)
	{
		if (check_dup(arg))
		{
			update_env_val(g_shell.env_list, arg);
			update_env_val(g_shell.export_list, arg);
		}
		else
			add_to_list(arg, 2);
	}
	else
	{
		if (check_dup(arg) == 0)
			add_to_list(arg, 1);
	}
	return (SUCCESS);
}

int	run_export(t_list *args)
{
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(args);
	if (len == 0)
		print_export_list();
	else
	{
		while (args)
		{
			printf("args: %s\n", args->content);
			if (append_envp((char *)(args->content)) != SUCCESS)
				return (1);
			args = args->next;
		}
	}
	return (SUCCESS);
}
