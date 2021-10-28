#include "command.h"
#include "libft.h"

void	get_env(t_list *envp)
{
	while (envp)
	{
		printf ("%s\n", envp->content);
		envp = envp->next; 
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
        cur_export_list = ft_strdup(export_list[i]);
        if (cur_export_list == NULL)
            return (0);
        new = ft_lstnew(cur_export_list);
        if (new == NULL)
            return (0);
		if (r == NULL)
			r = new;
		else
        	ft_lstadd_back(&r, new);
        i++;
    }
    return (r);
}

char *add_char(char const *s1, char c)
{
	int	len;
	char *result;
	char *str;

	if (!(s1))
		return (NULL);
	ft_strdup(s1);
	result = (char *)malloc(sizeof(char) * len + 1);
	str = (char *)malloc(sizeof(char) * 2);
	if (result == NULL || str == NULL)
	{
		printf("Malloc Error");
		exit(0);
	}
	str[0] = '=';
	len = ft_strlen(s1) + 1;
	ft_strlcpy(result, s1, len);
	ft_strlcat(result, str, len + 1);
	return (result);
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
		temp = ft_strchr(export_list->content, '=');
		temp++;
		a = ft_strdup(temp);
		printf("test\n");
		if (ft_strchr(export_list->content, '=') == NULL)
			printf("declare -x %s\n", export_list->content);
		// else if(ft_strchr(export_list->content, '=') != NULL)
		// {
		// 	printf("declare -x %s=\"%s\"\n", div_list[0], a);
		// }

        // div_export_list = ft_split(export_list->content, '=');
		// if ((div_export_list[1] == NULL) && (ft_strchr(div_export_list[0], '=') == NULL)) // = 없어
		// 	printf("1declare -x %s\n", div_export_list[0]);
		// else if ((div_export_list[1] == NULL) && (ft_strchr(div_export_list[0], '=') != NULL)) // = 있어
		// 	printf("2declare -x %s=\"\"\n", div_export_list[0]);
		// else
		// 	printf("3declare -x %s=\"%s\"\n", div_export_list[0], div_export_list[1]);
		export_list = export_list->next;
    }
}

void	convert_env(char *token, t_list *env_list)
{
	char **value;
	char **envp;

	value = (char **)malloc(sizeof(char *) * 3);
	envp = (char **)malloc(sizeof(char *) * 3);
	value = ft_split(token, '=');
	while(env_list)
	{
		envp = ft_split(env_list->content, '=');
		if (ft_strncmp(envp[0], value[0], ft_strlen(value[0])) == 0 && (ft_strchr(token, '=') != NULL)) // = 문자 있는데 중복, 값 바꿔줌
		{
			env_list->content = token;
			return ;
			// free_str(value);
			// free_str(envp);
		}
		env_list = env_list->next;
		free_str(envp);
	}
	free_str(value);
	free_str(envp);
}

int	check_dup(char *token, t_list *export_list, t_list *env_list)
{
	char **value;
	char **envp;

	value = (char **)malloc(sizeof(char *) * 3);
	envp = (char **)malloc(sizeof(char *) * 3);
	if ((value == NULL) || (envp == NULL))
	{
		printf("Malloc Error");
		exit(0);
	}
	value = ft_split(token, '=');	
	while(export_list)
	{
		envp = ft_split(export_list->content, '=');
		if (ft_strncmp(envp[0], value[0], ft_strlen(value[0])) == 0 && (ft_strchr(token, '=') != NULL)) // = 문자 있는데 중복, 값 바꿔줌
		{
			export_list->content = token;
			convert_env(token,env_list);
			// free_str(value);
			// free_str(envp);
			export_list = export_list->next;
			return(END);
		}
		else if (ft_strncmp(envp[0], value[0], ft_strlen(value[0])) == 0 && (ft_strchr(token, '=') == NULL)) // = 문자 없는데 중복
		{
			// free_str(value);
			// free_str(envp);
			export_list = export_list->next;
			printf("= 문자 없는데 중복\n");
			return(END);
		}
		export_list = export_list->next;
		free_str(envp);
	}
	// free_str(value);
	// free_str(envp);
	return (0);
}

int	onlt_export_list(char **token, t_list *export_list)
{
	t_list *new;

	if (ft_strchr(token[1], '=') != NULL) // = 문자 있음, 정상처리
		return (0);
	else //뭉탱이 value한개 넘게 오면 Error, 한개면 export_list에만 출력되도록 add
	{
		if (token_size(token) > 2)
			return(1);
		return (0);
	}
}

void	add_export_list(char *token, t_list *export_list)
{
	t_list *new;

	new = ft_lstnew(token);
	if (new == NULL)
	{
		printf("Malloc Error");
		exit(0);
	}
	ft_lstadd_back(&export_list, new);
}

int	run_export(char **token, char **envp)
{
	t_list *export_list;
	t_list *env_list;
	char *temp;
	int i;

	i = 1;
	export_list = init_envp(envp);
	env_list = init_envp(envp);
	if (token_size(token) == 1 && (ft_strncmp(token[0], "export", 7) == 0)) //export만
		print_export_list(export_list);
	else if (token_size(token) >= 2 && (ft_strncmp(token[0], "export", 7) == 0)) //&& ) //새로운 export
	{
		while(token[i])
		{
			if (ft_strchr(token[i], '=') != NULL) // = 있음
			{
				if (check_dup(token[i],export_list, env_list) == 0) //없는 환경변수
				{
					// temp = ft_strchr(token[i], '=');
					// if (temp++ )
					add_export_list(token[i], export_list);
					add_export_list(token[i], env_list);
				}
			}
			else // = 없음
			{
				if (check_dup(token[i],export_list, env_list) == 0) //없는 환경변수 export_list에만 추가
					add_export_list(token[i], export_list);
			}
			i++;
		}		
	}
	printf("----------------------------------------------------\n");
	get_env(env_list);
	print_export_list(export_list);
	return (0);
}

int	main(int argc, char **argv, char **export_list)
{
	(void)argc;
	(void)argv;
	char	*token[] = {"export", "a=", "b===", "c", NULL};
	run_export(token, export_list);
	return (0);
}