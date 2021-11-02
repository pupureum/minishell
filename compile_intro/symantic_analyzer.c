#include "minishell.h"
/* 
int	symantic_cmd_case(t_AST_Node *node)
{
	t_list	*args_list;
	char	*item;

	args_list = ((t_cmd *)(node->content))->args;
	while (args_list)
	{
		item = ((char *)(args_list->content));
		args_list = args_list->next;
		converter(item, &args_list);
		converter(&item);
	}
	return (SUCCESS);
}

int	symantic_analyzer(t_AST_Node *node)
{
	int	ret;

	ret = SUCCESS;
	if (node->type == TYPE_CMD)
		symantic_cmd_case(node);
	
	return (ret);
} */
