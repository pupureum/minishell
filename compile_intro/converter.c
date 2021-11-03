#include "minishell.h"

//test_need 
/*
static char	*get_exit_status(char **token, char *result)
{
	char	*exit_status;

	*token += 2;
	exit_status = ft_itoa(g_shell.exit_status);
	if (exit_status == NULL)
	{
		free(result);
		return (NULL);
	}
	return (ft_strjoin_free(result, exit_status, 3));
}

static t_list	*get_envp(char *name, t_list *envp) 
{
	char	*ptr;
	int		len;

	ptr = ft_strchr(name, '=');
	if (ptr)
		len = ptr - name;
	else
		len = ft_strlen(name);
	while (envp)
	{
		if (!ft_strncmp(envp->content, name, len))
		{
			if (*(char *)(envp->content + len) == '=' || \
				*(char *)(envp->content + len) == '\0')
				return (envp);
		}
		envp = envp->next;
	}
	return (NULL);
}

char	*get_envp_value(char *name)
{
	char	*result;
	t_list	*env;

	env = get_envp(name, g_shell.envp);
	if (!env || !ft_strchr(env->content, '='))
		result = ft_strdup("");
	else
		result = ft_strdup(env->content + ft_strlen(name) + 1);
	return (result);
}

static char	*get_env(char **token, char *result)
{
	char	*value;
	char	*key;

	if (!ft_strncmp(*token, "$?", 2))
		return (get_exit_status(token, result));
	key = ft_strdup("");
	malloc_error_check(key);
	(*token)++;
	while (**token && (ft_isalnum(**token)))
	{
		key = ft_strjoin_free(key, **token, 1);
		if (key == NULL)
		{
			free(result);
			return (NULL);
		}
			
		(*token)++;
	}
	value = get_envp_value(key);
	free(key);
	if (value == NULL)
		return (NULL);
	result = ft_strjoin_free(result, value, 2);
	(*token)--;
	return (result);
}

static int	convert_home_macro(char **token, char **result, int *cur_option)
{
	if (!ft_strncmp(*token, "~/", 2) || !ft_strcmp(*token, "~"))
	{
		*result = get_envp_value("HOME");
		++(*token);
	}
	else
		*result = (char *)malloc(sizeof(char));
	malloc_error_check(*result);
	return (1);
}
*/

// t_list	*converter(t_list *node)
// {

// 	int		cur_option;
// 	char	*result;
// 	char	null_char[2];

// 	null_char[1] = NULL;
// 	cur_option = CUR_NONE;
// 	if (!convert_home_macro(token, &result, &cur_option))
// 		return (NULL);
// 	while (**token)
// 	{
// 		null_char[0] = **token;
// 		if (set_quote_option(token, &cur_option) == 0)
// 		{
// 			if (!(cur_option & ~(CUR_DQUOTE)) && **token == '$' && *(*token + 1) && \
// 				(!ft_strncmp(*token, "$?", 2) || ft_isalpha(*(*token + 1))))
// 				result = get_env(token, result);
// 			else
// 				result = ft_strjoin_free(result, **token, 1);
// 			if (result == NULL)
// 				return (NULL);
// 		}
// 		(*token)++;
// 	}
// 	return (result);
// }
/*
converter에서 setting할 것
$? : fore_ground
~. ~/ -> HOME
$환경변수 -> 값으로
export + = 이면 에러 export 인자가 2개이상-> export (cmd) arg = (앞이나 뒤가 공백이면 에러)
a="====b"
*/



