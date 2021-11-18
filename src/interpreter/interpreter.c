#include "minishell.h"

extern t_minishell	g_shell;

t_AST_Node	*interpreter(char *line)
{
	t_list		*tokens;
	t_AST_Node	*head;
	int			cur_option;

	cur_option = CUR_NONE;
	tokens = scan_line(&line, &cur_option);
	if (tokens == NULL)
		return (NULL);
	//print_series_token(tokens);
	translate_env(tokens);
	head = syntax_analyzer(tokens);
	free_tokens(tokens);
	// print_JSON(head, 0);
	if (check_tree(head, 0) != SUCCESS)
	{
		destruct_AST(head);
		return (NULL);
	}
	return (head);
}
