#include "minishell.h"

// no_test sudo code **test need 
int control_cmd_except(node)
{
	t_list	*args_list;
	char	*item;
	char	*ptr;

	args_list = ((t_cmd *)node)->args;
	if (!ft_strcmp(((t_cmd *)node)->cmd, "export"))
	{
		while (args_list)
		{
			item = ((char *)(args_list->content));
			if ((ft_strchr("=", item) + 1) == " " || (ft_strchr("=", item) - 1) == " ")
			{	
				printf("no vaild input\n");
				return (PARSE_ERROR);		
			}	
			args_list = args_list->next;
		}
	}
}

void symantic_cmd_case(t_AST_Node *node, int *error)
{
	t_list		*args_list;
	char		*item;
	
	error = control_cmd_except(node);
	args_list = ((t_cmd *)node)->args;
	while (args_list)
	{
		item = ((char *)(args_list->content));
		item = converter(&item);
		args_list = args_list->next;
	}
}

int		symantic_analyzer(t_list *AST)
{
	int *error;
	if (((t_AST_Node *)(AST->content))->type = TYPE_CMD)
	{
		symantic_cmd_case(((t_AST_Node *)AST->content), error);
	}
	return (*error);
}
