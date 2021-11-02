#include "command.h"
#include "libft.h"

void	convert_env(char *token, t_list *env_list)
{
	char	**value;
	char	**envp;

	value = ft_split(token, '=');
	if (value == NULL)
		malloc_error();
	while (env_list)
	{
		envp = ft_split((char *)(env_list->content), '=');
		if (envp == NULL)
			malloc_error();
		if (ft_strncmp(envp[0], value[0], ft_strlen(value[0])) == 0
			&& (ft_strchr(token, '=') != NULL))
		{
			env_list->content = token;
			free_str(envp);
			free_str(value);
			return ;
		}
		env_list = env_list->next;
		free_str(envp);
	}
	free_str(value);
}

int	update_envp(char **envp, t_list *export_list, t_list *env_list, char *token)
{
	char	**value;

	value = ft_split(token, '=');
	if (value == NULL)
		malloc_error();
	if (ft_strncmp(envp[0], value[0], ft_strlen(value[0])) == 0
		&& (ft_strchr(token, '=') != NULL))
	{
		export_list->content = token;
		convert_env(token, env_list);
		export_list = export_list->next;
		free_str(value);
		free_str(envp);
		return (END);
	}		
	else if (ft_strncmp(envp[0], value[0], ft_strlen(value[0])) == 0
		&& (ft_strchr(token, '=') == NULL))
	{
		export_list = export_list->next;
		free_str(value);
		free_str(envp);
		return (END);
	}
	free_str(value);
	return (0);
}

int	check_dup(char *token, t_list *export_list, t_list *env_list)
{
	char	**envp;
	int		result;

	while (export_list)
	{
		envp = ft_split(export_list->content, '=');
		result = update_envp(envp, export_list, env_list, token);
		if (result == END)
			return (END);
		export_list = export_list->next;
		free_str(envp);
	}
	return (0);
}

void	append_envp(t_list *export_list, t_list *env_list, char *token)
{
	if (ft_strchr(token, '=') != NULL)
	{
		if (check_dup(token, export_list, env_list) == 0)
		{
			add_to_list(token, export_list);
			add_to_list(token, env_list);
		}
	}
	else
	{
		if (check_dup(token, export_list, env_list) == 0)
			add_to_list(token, export_list);
	}	
}

int	run_export(char **token, t_list *export_list, t_list *env_list)
{
	char	*temp;
	int		i;

	i = 0;
	if (token_size(token) == 1 && (ft_strncmp(token[0], "export", 7) == 0))
		print_export_list(export_list);
	else if (token_size(token) >= 2 && (ft_strncmp(token[0], "export", 7) == 0))
	{
		while (token[++i])
			append_envp(export_list, env_list, token[i]);
	}
	printf("----------------------------------------------------\n");
	get_env(env_list);
	print_export_list(export_list);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*export_list;
	t_list	*env_list;
	(void)argc;
	(void)argv;
	char	*token[] = {"export", "a=123", "b=", "d=c", "d", NULL};

	export_list = init_envp(envp);
	env_list = init_envp(envp);
	run_export(token, export_list, env_list);
	while(1){};
	return (0);
}