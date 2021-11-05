#include "minishell.h"

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

int	translate_dollar_case(t_list *token, char *line)
{
	char	**words;
	int		idx;

	words = ft_split(line, '$');
    ((t_token *)(token->content))->value = convert_dollar_case(words, idx);
	free_mat(words);
	return (SUCCESS);
}
