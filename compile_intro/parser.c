#include "minishell.h"

t_AST_Node	*syntax_analyzer(t_list *token)
{
	t_AST_Node		*Node;

	Node = parse_get_node(&token);
	return (Node);
}



