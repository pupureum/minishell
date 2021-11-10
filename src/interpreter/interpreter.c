#include "minishell.h"

t_AST_Node	*interpreter(char *line)
{
	t_list		*tokens;
	t_AST_Node	*head = NULL;

	tokens = lexical_analyzer(line);
	if (tokens == NULL)
		return (NULL);
	print_series_token(tokens);
	translate_env(tokens);
	head = syntax_analyzer(tokens);
	free_tokens(tokens);
	print_JSON(head, 0);
	//symantic_analyzer(head);
	/*
	if (error == 1)
	{
		//소멸자
	}
	*/
	return (head);
}

