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

t_list	*init_envp(char *export_list[])
{
	int		i;
	char	*cur_export_list;
	t_list	*new;
	t_list	*r;

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

char	*make_str(t_list *export_list)
{
	char	*temp;
	char	*str;

	temp = ft_strchr(export_list->content, '=');
	temp++;
	str = ft_strdup(temp);
	if (str == 0)
		malloc_error();
	return (str);
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
			&& (ft_strchr(token, '=') != NULL)) // = 문자 있는데 중복, 값 바꿔줌
		{
			env_list->content = token;
			free_str(envp);
			return ;
		}
		env_list = env_list->next;
		free_str(envp);
	}
	free_str(value);
}

int	check_dup(char *token, t_list *export_list, t_list *env_list)
{
	char	**value;
	char	**envp;


	value = ft_split(token, '=');
	if (value == NULL)
		malloc_error();
	while (export_list)
	{
		envp = ft_split(export_list->content, '=');
		if (ft_strncmp(envp[0], value[0], ft_strlen(value[0])) == 0 && (ft_strchr(token, '=') != NULL)) // = 문자 있는데 중복, 값 바꿔줌
		{
			export_list->content = token;
			convert_env(token,env_list);
			export_list = export_list->next;
			free_str(value);
			free_str(envp);
			return (END);
		}
		else if (ft_strncmp(envp[0], value[0], ft_strlen(value[0])) == 0 && (ft_strchr(token, '=') == NULL)) // = 문자 없는데 중복
		{
			export_list = export_list->next;
			free_str(value);
			free_str(envp);
			return (END);
		}
		export_list = export_list->next;
		free_str(envp);
	}
	free_str(value);
	return (0);
}

// int	only_export_list(char **token, t_list *export_list)
// {
// 	t_list *new;

// 	if (ft_strchr(token[1], '=') != NULL) // = 문자 있음, 정상처리
// 		return (0);
// 	else //뭉탱이 value한개 넘게 오면 Error, 한개면 export_list에만 출력되도록 add
// 	{
// 		if (token_size(token) > 2)
// 			return (1);
// 		return (0);
// 	}
// }

void	add_to_list(char *token, t_list *export_list)
{
	t_list	*new;

	new = ft_lstnew(token);
	if (new == NULL)
	{
		printf("Malloc Error");
		exit(0);
	}
	ft_lstadd_back(&export_list, new);
}

void	seperate_case(t_list *export_list, t_list *env_list, char *token) // = 유무에 따라 분리
{
	if (ft_strchr(token, '=') != NULL)
	{
		if (check_dup(token,export_list, env_list) == 0) //중복 없는 환경변수
		{
			add_to_list(token, export_list);
			add_to_list(token, env_list);
		}
	}
	else
	{
		if (check_dup(token,export_list, env_list) == 0) //중복 없는 환경변수, = 없어서 export_list에만 추가
			add_to_list(token, export_list);	
	}	
}

int	run_export(char **token, t_list *export_list, t_list)
{

	char	*temp;
	int		i;

	i = 0;
	if (token_size(token) == 1 && (ft_strncmp(token[0], "export", 7) == 0)) //export만 들어온 경우. 
		print_export_list(export_list);
	else if (token_size(token) >= 2 && (ft_strncmp(token[0], "export", 7) == 0))
	{
		while(token[++i])
			seperate_case(export_list, env_list, token[i]);	
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
	char	*token[] = {"export", "a===", "b=", "c", "a=c", "d", NULL};

	export_list = init_envp(envp);
	env_list = init_envp(envp);
	run_export(token, export_list, env_list);
	while(1){};
	return (0);
}