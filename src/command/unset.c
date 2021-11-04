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

void	del_export(t_list **export_list, char *arg)
{
	char	**export;
	t_list	*cur;
	t_list	*former;
	t_list	*head;
	t_list	*remove_node;

	// head = (t_list *)malloc(sizeof(t_list));
	// head->next = *export_list;
	cur = *export_list;
	former = cur;
	while (cur)
	{
		export = ft_split(cur->content, '=');
		if (ft_strncmp(arg, export[0], ft_strlen(arg)) == 0)
		{
			// remove_node = head->next;
			// head->next = remove_node->next;
			// remove_node->next = NULL;
			// free(remove_node);
			// printf("hello\n");
			// head = head->next;	 
			// printf("hiiiii\n");
			former->next = cur->next;
			cur->next = NULL;
			free(cur);
			cur = former->next;
		}
		else
		{
			// head = head->next->next;
			
			former = cur;
			cur = cur->next;
		}
		free_str(export);
	}
	// free(head);
}

// void	del_env(t_list **env_list, char *arg)
// {
// 	char	**env;
// 	t_list	*cur;
// 	t_list	*former;
// 	t_list	*head;
// 	t_list	*remove_node;
// 	t_list	*current;

// 	printf("qqqq");
// 	head->next = *env_list;
// 	cur = *env_list;
// 	former = cur;
// 	while (head)
// 	{
// 		env = ft_split(head->next->content, '=');
// 		if (ft_strncmp(arg, env[0], ft_strlen(arg)) == 0)
// 		{
// 			remove_node = head->next;
// 			head->next = remove_node->next;
// 			remove_node->next = NULL;
// 			free(remove_node);
// 			printf("hello\n");
// 			head = head->next;	 
// 			printf("hiiiii\n");
// 			// former->next = cur->next;
// 			// cur->next = NULL;
// 			// free(cur);
// 			// cur = former->next;
// 		}
// 		else
// 		{
// 			printf("aaaaaaa\n");
// 			current = head->next;
// 			printf("bbbbbbb\n");
// 			head = current->next;
// 			printf("cccccccc\n");
// 		}
// 		free_str(env);
// 	}
// }

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
	int		i;
	char	**env;

	i = 0;
	get_env(*env_list);
	print_export_list(*export_list);
	while (args)
	{
		if (ft_strchr((char *)(args->content), '=') != NULL)
		{
			printf("bash: unset: `%s': not a valid identifier\n", (char *)(args->content));
			return (1);
		}
		if ((ft_strncmp((char *)(args->content), (*export_list)->content, ft_strlen((char *)(args->content)))
				== 0) || (ft_strncmp((char *)(args->content), (*export_list)->content,
					 ft_strlen((char *)(args->content))) == 0))
		{
			*export_list = (*export_list)->next;
			*env_list = (*env_list)->next;
		}
		else
		{
			del_export(export_list, (char *)(args->content));
			del_env(env_list, (char *)(args->content));
		}
		args = args->next;
	}
	printf("----------------------------------------------------\n");
	get_env(*env_list);
	print_export_list(*export_list);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*export_list;
	t_list	*env_list;
	(void)argc;
	(void)argv;
	t_list	*args;
	t_list	*new;
	t_list	*new2;
	t_list	*cur;

	args = ft_lstnew("vv");
	new = ft_lstnew("SECURITYSESSIONID");
	new2 = ft_lstnew("PWD");
	if (args == NULL || new == NULL | new2 == NULL)
		return (0);
	ft_lstadd_back(&args, new);
	ft_lstadd_back(&args, new2);

	export_list = init_envp(envp);
	env_list = init_envp(envp);
	run_unset(args, &export_list, &env_list);
	while(args)
	{
		cur = args;
		args = args->next;
		free(cur);
	}
	while(1){};
	return (0);
}
