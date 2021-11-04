#include "minishell.h"

t_AST_Node	*interpreter(char *line)
{
	t_list		*tokens;
	t_AST_Node	*head;

	tokens = lexical_analyzer(line);
	print_series_token(tokens);
	translate_env(tokens);
	head = syntax_analyzer(tokens);
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
