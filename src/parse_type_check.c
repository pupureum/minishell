#include "minishell.h"

static void check_redirect_mode(t_list **token, t_redirect *redirect)
{
	if (!ft_strcmp(((t_token *)(*token)->content)->value, "<"))
		redirect->type = TYPE_REDIR_STDIN;
	else if (!ft_strcmp(((t_token *)(*token)->content)->value, ">"))
		redirect->type = TYPE_REDIR_STDOUT;
	else if (!ft_strcmp(((t_token *)(*token)->content)->value, "<<"))
		redirect->type = TYPE_REDIR_HEREDOC;
	else if (!ft_strcmp(((t_token *)(*token)->content)->value, ">>"))
		redirect->type = TYPE_REDIR_APPEND;
}

int	type_argument(t_cmd *cmd, t_list **arg, t_token *token)
{
	if (!cmd->args)
	{
		cmd->args = ft_lstnew(token->value);
		if (cmd->args == NULL)
			return (0);
		*arg = cmd->args;
	}
	else
	{
		(*arg)->next = ft_lstnew(token->value);
		if ((*arg)->next == NULL)
			return (0);
		(*arg) = (*arg)->next;
	}
	token->value = NULL;
	return (1);
}

int	type_redirect(t_AST_Node **curr, t_list **token)
{
	t_redirect	*redirect;

	(*curr)->content = (t_redirect *)malloc(sizeof(t_redirect));
	malloc_error_check((*curr)->content);
	redirect = (*curr)->content;
	(*curr)->type = TYPE_REDIRECT;
	check_redirect_mode(token, redirect);
	*token = (*token)->next;
	redirect->after_fd = ((t_token *)(*token)->content)->value;
	((t_token *)(*token)->content)->value = NULL;
	redirect->child = (t_AST_Node *)malloc(sizeof(t_AST_Node));
	if (redirect->child == NULL)
	malloc_error_check(redirect->child);
	*curr = redirect->child;
	return (1);
}