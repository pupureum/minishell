#include "command.h"
#include "libft.h"

void	get_env(t_list *envp)
{
	while (envp)
	{
		printf ("%s\n", (char *)(envp->content));
		envp = envp->next; 
	}
}

void    print_export_list(t_list *export_list)
{
	char	*temp;
	char	*a;
    char	**div_list;

    div_list = (char **)malloc(sizeof(char *) * 3);
    if (div_list == NULL)
    {
        printf("Malloc Error");
        exit(0);
    }
    while (export_list)
    {
		if (ft_strchr(export_list->content, '=') != NULL)
		{
			temp = ft_strchr(export_list->content, '=');
			temp++;
			a = ft_strdup(temp);
			div_list = ft_split(export_list->content, '=');
			printf("declare -x %s=\"%s\"\n", div_list[0], a);
			free(div_list);
			free(a);
		}
		else if(ft_strchr(export_list->content, '=') == NULL)
			printf("declare -x %s\n", (char *)(export_list->content));
		export_list = export_list->next;
    }
}

t_list  *init_envp(char *export_list[])
{
    int     i;
    char    *cur_export_list;
    t_list  *new;
    t_list  *r;

    i = 0;
	r = NULL;
    while (export_list[i])
    {
        new = ft_lstnew(export_list[i]);
        if (new == NULL)
		{
			printf("Malloc Error\n");
            exit(0);
		}
		if (r == NULL)
			r = new;
		else
        	ft_lstadd_back(&r, new);
        i++;

    }
    return (r);
}

int	run_unset(char **token, t_list *export_list, t_list *env_list)
{
	int i;
	char **export;
	char **env;
	t_list *cur;
	t_list *former;

	i = 1;
	get_env(env_list);
	print_export_list(export_list);
	while(token[i])
	{
		if (ft_strchr(token[i], '=') != NULL)
		{
			printf("unset: %s: invalid parameter name\n", token[i]);
			return (1);
		}
		cur = export_list;
		former = cur;
		while(cur)
		{
			export = ft_split(cur->content, '=');
			if (ft_strncmp(token[i], export[0], ft_strlen(token[i])) == 0)
			{
				former->next = cur->next;
				cur->next = NULL;
				free(cur);
			}
			else
			{
				former = cur;
				cur = cur->next;
			}
			free_str(export);
		}
		cur = env_list;
		former = cur;
		while(cur)
		{
			env = ft_split(env_list->content, '=');
			if (ft_strncmp(token[i], env[0], ft_strlen(token[i])) == 0)
			{
				former->next = cur->next;
				cur->next = NULL;
				free(cur);
			}
			else
			{
				former = cur;
				cur = cur->next;
			}
			free_str(env);
		}
		i++;
	}
	printf("----------------------------------------------------\n");
	get_env(env_list);
	print_export_list(export_list);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_list *env_list;
	t_list *export_list;
	char	*test[] = {"unset", "HOME", "c", NULL};

	env_list = init_envp(envp);
	export_list = init_envp(envp);
	run_unset(test, export_list, env_list);
	return (0);
}