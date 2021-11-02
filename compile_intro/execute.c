#include "minishell.h"

extern t_minishell g_shell;

void execute(t_AST_Node *node)
{
	if (g_shell.cmd_cnt > 1)
		build_pipeline(node, g_shell.cmd_cnt);
}