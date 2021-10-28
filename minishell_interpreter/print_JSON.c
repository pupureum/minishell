
#include "interpreter.h"

static char	*check_redirect_type(int type)
{
	if (!(type & (TYPE_REDIR_STDIN | TYPE_REDIR_STDOUT | TYPE_REDIR_HEREDOC | TYPE_REDIR_HEREDOC)))
		return (NULL);
	if (type == TYPE_REDIR_STDIN)
		return (ft_strdup("STDIN"));
	else if (type == TYPE_REDIR_STDOUT)
		return (ft_strdup("STDOUT"));
	else if (type == TYPE_REDIR_HEREDOC)
		return (ft_strdup("HEREDOC"));
	else if (type == TYPE_REDIR_APPEND)
		return (ft_strdup("APPEND"));

	return (NULL);
}


void	print_REDIRECT(t_redirect *redirect, int indent)
{
	char *type;

	type = check_redirect_type(redirect->type);
	print_indent(indent);
	printf("%s{ \n", KEY_COLOR);
	print_indent(indent);
	printf("\tredirect : %s%s%s\n", VALUE_COLOR, type, KEY_COLOR);
	print_indent(indent);
	printf("\tafter FD : %s%s%s\n", VALUE_COLOR, redirect->after_fd, KEY_COLOR);
	print_indent(indent);
	printf("\tinfo : \n");
	if (redirect->child == NULL)
	{
		print_indent(indent);
		printf("\t%s(NULL)%s\n", VALUE_COLOR, KEY_COLOR);
	}
	else
		print_JSON(redirect->child, indent + 1);
	print_indent(indent);
	printf("}\n");
}

void	print_CMD(t_cmd *cmd, int indent)
{
	t_list	*curr;

	if (cmd == NULL)
		return ;
	curr = cmd->args;
	print_indent(indent);
	printf("%s{ \n", KEY_COLOR);
	print_indent(indent);
	printf("\tcmd : \"%s%s%s\"\n", VALUE_COLOR, cmd->cmd, KEY_COLOR);
	print_indent(indent);
	printf("\targs : \n");
	while (curr)
	{
		print_indent(indent);
		printf("\t\"%s%s%s\"\n", VALUE_COLOR, (char *)curr->content, KEY_COLOR);
		curr = curr->next;
	}
	print_indent(indent);
	printf("}\n");
}

void	print_PIPE(t_pipe *pipe, int indent)
{
	print_indent(indent);
	printf("%s{ \n", KEY_COLOR);
	print_indent(indent);
	printf("\tpipeline\n");
	print_indent(indent);
	printf("\t%sleftchild :\n", KEY_COLOR);
	print_JSON(pipe->leftchild, indent + 1);
	print_indent(indent);
	printf("\t%srightchild :\n", KEY_COLOR);
	print_JSON(pipe->rightchild, indent + 1);
	print_indent(indent);
	printf("}\n");
}

void	print_JSON(t_AST_Node	*AST, int indent)
{
	if (AST->type == TYPE_CMD)
		print_CMD(AST->content, indent);
	else if (AST->type == TYPE_PIPE)
		print_PIPE(AST->content, indent);
	else if (AST->type == TYPE_REDIRECT)
		print_REDIRECT(AST->content, indent);
}
