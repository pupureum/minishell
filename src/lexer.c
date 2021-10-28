#include "minishell.h"

static char **remove_not_lexeme(char **line)
{
	if (**line == (char)NULL)
		return (NULL);
    while (**line && ft_strchr(" \n\t", **line))
        (*line)++;
	//
	return line;
}

static t_token *get_special_token(t_token *token, char **line, int *cur_option)
{
	token->value = get_special_item(line, cur_option);
	if (*cur_option & CUR_REDIRECT)
		token->type = CUR_REDIRECT;
	else if (*cur_option & CUR_PIPE)
		token->type = CUR_PIPE;
	return (token);
}

static t_token *get_plain_token(t_token *token, char **line, int *cur_option)
{
	if (*cur_option & CUR_REDIRECT)
	{
		token->type = CUR_AFTER_FD;
		*cur_option ^= CUR_REDIRECT;
	}
	else if (*cur_option & CUR_CMD)
		token->type = CUR_ARG;
	else
	{
		*cur_option = CUR_CMD;
		token->type = CUR_CMD;
	}
	token->value = get_plain_item(line);
	return (token);
}

static t_list	*scan_line(char **line, int *cur_option)
{
	t_list *ret;
	t_list *head;
	t_token *token;

	line = remove_not_lexeme(line);
	// divide_init_process
		if (line == NULL)
			return NULL;
		token = (t_token *)malloc(sizeof(t_token));
		malloc_error_check(token);
		if (ft_strchr("|<>", **line))
			token = get_special_token(token, line, cur_option);
		else
			token = get_plain_token(token, line, cur_option);
	ret = ft_lstnew(token);
	head = ret;
	while (*line)
	{
		line = remove_not_lexeme(line);
		if (line == NULL)
			break;
		token = (t_token *)malloc(sizeof(t_token));
		malloc_error_check(token);
		if (ft_strchr("|<>", **line))
			token = get_special_token(token, line, cur_option);
		else
			token = get_plain_token(token, line, cur_option);
		ret->next = ft_lstnew(token);
		ret = ret->next;
	}
	return (head);
}

t_list *lexical_analyzer(char *line)
{
	t_list		*tokens;
	int			cur_option;

	cur_option = CUR_NONE;
	tokens = scan_line(&line, &cur_option);
	return (tokens);
}
