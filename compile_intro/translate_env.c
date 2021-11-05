#include "minishell.h"

extern t_minishell g_shell;

char    *get_env_str(char *str)
{
    t_list  *list;
    char    **envp;
    char    *result;

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
}s

int is_special_case(t_list *token, char *line)
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

int solve_special_case(int case_num, t_list *token, char *line)
{
    char    *temp;

    if (case_num == 1)
    {
        free(((t_token *)(token->content))->value);
        ((t_token *)(token->content))->value = get_env_str("HOME");
    }
    else if (case_num == 2)
    {
        temp = ft_strjoin_free(get_env_str("HOME"), line + 2, 1);
        free(((t_token *)(token->content))->value);
        ((t_token *)(token->content))->value = temp;
    }
    return (SUCCESS);
}

void	free_mat(char **mat)
{
	int	idx;

	idx = 0;
	while (mat[idx])
	{
		free(mat[idx]);
		idx++;
	}
	free(mat);
}

char	*convert_dollar_case(char **words, int sp_idx)
{
	char	*result;

	result = ft_strdup(*words);
	while (++words)
	{
		sp_idx = 0;
		if ((*words)[0] == '?')
		{
			result = ft_strjoin_free(result, ft_itoa(g_shell.exit_status), 3);
			result = ft_strjoin_free(result, *words + 1, 1);
			continue ;
		}
		while ((*words)[sp_idx] > ' ')
			sp_idx++;
		if ((*words)[sp_idx] == '\0')
			result = ft_strjoin_free(result, get_env_str(*words), 3);
		else
		{
			(*words)[sp_idx] = '\0';
			result = ft_strjoin_free(result, get_env_str(*words), 3);
			result = ft_strjoin_free(result, " ", 1);
			result = ft_strjoin_free(result, *words + sp_idx + 1, 1);
		}
	}
	return (result);
}

int	solve_dollar_case(t_list *token, char *line)
{
	char	**words;
	int		idx;

	words = ft_split(line, '$');
    ((t_token *)(token->content))->value = convert_dollar_case(words, idx);
	free_mat(words);
	return (SUCCESS);
}

int convert_arg(t_list *token)
{
    char    *line;
    int     case_num;

    line = ((t_token *)(token->content))->value;
    case_num = is_special_case(token, line);
    if (case_num)
        return (solve_special_case(case_num, token, line));
	else
		return (solve_dollar_case(token, line));
}

int translate_env(t_list *token)
{
    while (token)
    {
        if (((t_token *)(token->content))->type ^ (CUR_QUOTE | CUR_ARG))
            convert_arg(token);
        token = token->next;
    }
    return (SUCCESS);
}
