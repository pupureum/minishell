#include "minishell.h"

static char	*get_pipe_token(char **line, int *cur_option)
{
	char *ret;

	*cur_option = CUR_PIPE;
	ret = ft_strdup("|");
	*line += 1;

	return ret;
}

static char	*get_redirect_token(char **line)
{
	char	*ret;

	ret = NULL;
	if (ft_strncmp(*line, "<<", 2) == 0)
		ret = ft_strdup("<<");
	else if (ft_strncmp(*line, ">>", 2) == 0)
		ret = ft_strdup(">>");
	else if (ft_strncmp(*line, "<", 1) == 0)
		ret = ft_strdup("<");
	else if (ft_strncmp(*line, ">", 1) == 0)
		ret = ft_strdup(">");
	if (ft_strlen(ret) == 2)
		*line += 2;
	else if (ft_strlen(ret) == 1)
		*line += 1;
	return (ret);
}

/*
1. line - 1 index에서 접근해서 space or not
default / not space -> **line
*맨앞인경우인데
if (**line = <)

flag = 1; -> flag = 0;
-> default

2. give line (separate)
ast X, line(syntax_analyzer)
g_shell.line
strchr()

ret = strchr();
g_shell.line != strchr("<>", **line); -> 첫문자 확인
else
*(strchr("<>", **line) - 1) == " \n\t" -> 1
	else
		fd_in?


*/

static void	set_quote_option(char **line, int *cur_option)
{
	if (!ft_strcmp("'", *line) && !(*cur_option & CUR_DQUOTE))
	{
		*cur_option ^= CUR_QUOTE;
	}
	else if (!ft_strcmp("\"", *line) && !(*cur_option & CUR_QUOTE))
	{
		*cur_option ^= CUR_DQUOTE;
	}
}

char	 *get_special_item(char **line, int *cur_option)
{
	char *token_value;

	token_value = NULL;
	if (ft_strchr("|", **line))
	{
		token_value = get_pipe_token(line, cur_option);
	}
	else if (ft_strchr("<>", **line))
	{

		if (*cur_option & CUR_REDIRECT)
		{
			exit(1);
			return ((char *)PARSE_ERROR);
		}
		*cur_option |= CUR_REDIRECT;
		token_value = get_redirect_token(line);
	}
	return (token_value);
}

static int check_option(char *plain, int *cur_option)
{
	if (*cur_option != CUR_NONE)
	{
		printf("%s\n", strerror(1));
		free(plain);
		return (PARSE_ERROR);
	}
	return (0);
}

char	*get_plain_item(char **line)
{
	char	*plain;
	char	null_char[2];
	int		temp_option;

	plain = ft_strdup("");
	null_char[1] = (char)NULL;
	temp_option = CUR_NONE;
	while (**line)
	{
		null_char[0] = **line;
		if ((temp_option == CUR_NONE) && ft_strchr(" \n\t<>|", **line))
			break;
		set_quote_option(line, &temp_option);
		plain = ft_strjoin_free(plain, null_char, 1);
		if (plain == NULL)
		{
			printf("%s\n", strerror(12));
			free(plain);
			return ((char *)PARSE_ERROR);
		}
		*line += 1;
	}
	if (check_option(plain, &temp_option))
		return ((char *)PARSE_ERROR);
	return (plain);
}