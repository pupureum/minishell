#include "minishell.h"

char	*make_str(t_list *export_list)
{
	char	*temp;
	char	*value;

	temp = ft_strchr(export_list->content, '=');
	temp++;
	value = ft_strdup(temp);
	if (value == 0)
		malloc_error();
	return (value);
}

void	print_export_list()
{
	char	**name;
	char	*value;
	t_list	*envp;

	envp = g_shell.export_list;
	while (envp)
	{
		if (ft_strchr(envp->content, '=') != NULL)
		{
			value = make_str(envp);
			name = ft_split(envp->content, '=');
			if (name == NULL)
				malloc_error();
			printf("declare -x %s=\"%s\"\n", name[0], value);
			free_str(name);
			free(value);
		}
		else if (ft_strchr(envp->content, '=') == NULL)
			printf("declare -x %s\n", (char *)(envp->content));
		envp = envp->next;
	}
}

void	del_export(t_list **export_list, char *arg)
{
	char	**export;
	t_list	*cur;
	t_list	*former;

	cur = *export_list;
	former = cur;
	while (cur)
	{
		export = ft_split(cur->content, '=');
		if (ft_strncmp(arg, export[0], ft_strlen(arg) + 1) == 0)
		{
			former->next = cur->next;
			cur->next = NULL;
			free(cur);
			cur = former->next;
		}
		else
		{
			former = cur;
			cur = cur->next;
		}
		free_str(export);
	}
}

void	del_env(t_list **env_list, char *arg)
{
	char	**env;
	t_list	*cur;
	t_list	*former;

	cur = *env_list;
	former = cur;
	while (cur)
	{
		env = ft_split(cur->content, '=');
		if (ft_strncmp(arg, env[0], ft_strlen(arg)) == 0)
		{
			former->next = cur->next;
			cur->next = NULL;
			free(cur);
			cur = former->next;
		}
		else
		{
			former = cur;
			cur = cur->next;
		}
		free_str(env);
	}
}

int	run_unset(t_list *args, t_list **export_list, t_list **env_list)
{
	// int		i;

	// i = 0;
	// while (args)
	// {
	// 	if (ft_strchr((char *)(args->content), '=') != NULL)
	// 	{
	// 		printf("bash: unset: `%s': not a valid identifier\n", (char *)(args->content));
	// 		return (1);
	// 	}
	// 	if ((ft_strncmp((char *)(args->content), (*export_list)->content, ft_strlen((char *)(args->content)) + 1)
	// 			== 0) || (ft_strncmp((char *)(args->content), (*export_list)->content,
	// 				 ft_strlen((char *)(args->content)) + 1) == 0))
	// 	{
	// 		*export_list = (*export_list)->next;
	// 		*env_list = (*env_list)->next;
	// 	}
	// 	else
	// 	{
	// 		del_export(export_list, (char *)(args->content));
	// 		del_env(env_list, (char *)(args->content));
	// 	}
	// 	args = args->next;
	// }
	return (SUCCESS);
}
