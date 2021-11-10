#include "minishell.h"

void	free_tokens(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->content)
		{
			free(((t_token *)(temp->content))->value);
			free(temp->content);
		}
		free(temp);
	}
}

void	destruct_AST(t_AST_Node *node)
{
	if (node->type == TYPE_PIPE)
	{
		destruct_AST(((t_pipe *)(node->content))->leftchild);
		destruct_AST(((t_pipe *)(node->content))->rightchild);
	}
	else if (node->type & TYPE_REDIRECT)
	{
		destruct_AST(((t_redirect *)(node->content))->child);
		free(((t_redirect *)(node->content))->after_fd);
	}
	else
		free_tokens(((t_cmd *)(node->content))->args);
}
