#include "command.h"
#include "libft.h"

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

void	print_export_list(t_list *export_list)
{
	char	**name;
	char	*value;

	while (export_list)
	{
		if (ft_strchr(export_list->content, '=') != NULL)
		{
			value = make_str(export_list);
			name = ft_split(export_list->content, '=');
			if (name == NULL)
				malloc_error();
			printf("declare -x %s=\"%s\"\n", name[0], value);
			free_str(name);
			free(value);
		}
		else if (ft_strchr(export_list->content, '=') == NULL)
			printf("declare -x %s\n", (char *)(export_list->content));
		export_list = export_list->next;
	}
}

void	del_export(t_list **export_list, char *token)
{
	char	**export;
	t_list	*cur;
	t_list	*former;

	cur = *export_list;
	former = cur;
	while (cur)
	{
		export = ft_split(cur->content, '=');
		if (ft_strncmp(token, export[0], ft_strlen(token)) == 0)
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

void	del_env(t_list **env_list, char *token)
{
	char	**env;
	t_list	*cur;
	t_list	*former;

	cur = *env_list;
	former = cur;
	while (cur)
	{
		env = ft_split(cur->content, '=');
		if (ft_strncmp(token, env[0], ft_strlen(token)) == 0)
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

int	run_unset(char **token, t_list **export_list, t_list **env_list)
{
	int		i;
	char	**env;

	i = 0;
	get_env(*env_list);
	print_export_list(*export_list);
	while (token[++i])
	{
		if (ft_strchr(token[i], '=') != NULL)
		{
			printf("bash: unset: `%s': not a valid identifier\n", token[i]);
			return (1);
		}
		if ((ft_strncmp(token[i], (*export_list)->content, ft_strlen(token[i]))
				== 0) || (ft_strncmp(token[i], (*export_list)->content,
					 ft_strlen(token[i])) == 0))
		{
			*export_list = (*export_list)->next;
			*env_list = (*env_list)->next;
		}
		else
		{
			del_export(export_list, token[i]);
			del_env(env_list, token[i]);
		}
	}
	printf("----------------------------------------------------\n");
	get_env(*env_list);
	print_export_list(*export_list);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_list *env_list;
// 	t_list *export_list;
// 	char	*test[] = {"unset", "_", NULL};

// 	(void)argc;
// 	(void)argv;
// 	env_list = init_envp(envp);
// 	export_list = init_envp(envp);
// 	run_unset(test, &export_list, &env_list);
// 	while(1){};
// 	return (0);
// }
