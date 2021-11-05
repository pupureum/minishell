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
		envp = ft_split(list, '=');
		if (ft_strncmp(envp[0], str, ft_strlen(envp[0])) == 0)
			result = ft_strdup(envp[1]);
		else
			result = ft_strdup("");
		free_str(envp);
		list = list->next;
	}
	return (result);
}

int	is_special_case(t_list *token, char *line)
{
	if ((((t_token *)(token->content))->type == CUR_ARG) &&
		((ft_strcmp(line, "~") == 0)))
		return (1);
	else if ((((t_token *)(token->content))->type == CUR_ARG) &&
		((ft_strncmp(line, "~/", 2) == 0)))
		return (2);
	else if ((((t_token *)(token->content))->type == (CUR_ARG | CUR_DQUOTE)) &&
		ft_strchr(line, '$') == NULL)
		return (3);
	else
		return (0);
}

int	convert_arg(t_list *token)
{
	char	*line;
	int		case_num;

	line = ((t_token *)(token->content))->value;
	case_num = is_special_case(token, line);
	if (case_num)
		return (translate_home_case(case_num, token, line));
	else
		return (translate_dollar_case(token, line));
}

int	translate_env(t_list *token)
{
	while (token)
	{
		if (((t_token *)(token->content))->type ^ (CUR_QUOTE | CUR_ARG))
			convert_arg(token);
		token = token->next;
	}
	return (SUCCESS);
}
