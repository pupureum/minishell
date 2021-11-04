#include "minishell.h"

extern t_minishell g_shell;

char	*get_env_str(char *str)
{
	t_list	*list;
	char	**envp;
	char	*result;
	list = g_shell.export_list;

	while(list)
	{
		env = ft_split(list, '=');
		if (ft_strncmp(envp[0], str, ft_strlen(envp[0])) == 0)
			result = ft_strdup(envp[1]);
		else
			result = ft_strdup("");
		free_str(envp);
		list = list->next;
	}
	return (result);
	
}

t_list	*convert_token(t_list *token)
{
	t_list	*new_token;
	char	*line;
	char	*temp;

	line = ((t_token *)(token->content))->value;
	if ((((t_token *)(token->content))->type == CUR_ARG) && ((ft_strcmp(line, "~") == 0)))
	{
		free(line);
		line = get_env_str("HOME");
		return (token);
	}
	else if ((((t_token *)(token->content))->type == CUR_ARG) && ((ft_strncmp(line, "~/", 2) == 0)))
	{
		temp = ft_strjoin("path", line + 2);
		free(line);
		((t_token *)(token->content))->value = temp;
		return (token);
	}
	new_token = token;
	while (*line)
	{
		if (ft_strchr(line, '~') != NULL)
			;
		else if (ft_strchr(line, '$') != NULL)
			;
		line++;
	}
	new_token->next = token->next;//새로만들어진 linked list의 next를 기존 token의 next로 연결해줘야함
	return (new_token);
}

int	translate_env(t_list *token)
{
	t_list	*before_token;
	t_list	*converted_token;

	before_token = token;
	while (token)
	{
		if (before_token == token)
		{
			token = token->next;
			continue ;
		}
		if (((t_token *)(token->content))->type ^ (CUR_QUOTE | CUR_ARG))
		{
			converted_token = convert_token(token);
			before_token->next = converted_token;
		}
		before_token = token;
		token = token->next;
	}
	return (SUCCESS);
}
