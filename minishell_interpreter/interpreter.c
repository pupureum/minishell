#include "interpreter.h"

t_AST_Node	*interpreter(char *line)
{
	t_list		*tokens;
	t_AST_Node	*head;

	tokens = lexical_analyzer(line);
	print_series_token(tokens);
	head = syntax_analyzer(tokens);
	print_JSON(head, 0);
	//error = symantic_analyzer(ret);
	/*
	if (error == 1)
	{
		//소멸자
	}
	*/
	return (head);
}

