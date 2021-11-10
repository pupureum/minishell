/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:12:39 by bylee             #+#    #+#             */
/*   Updated: 2021/11/10 19:42:42 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_shell;

void	redir_and_exe(int idx_cmd, t_AST_Node *node)
{
	t_list		*fd_table;
	t_AST_Node	*curr;

	fd_table = init_fd_table();
	if (fd_table == NULL)
		error(MALLOC_ERROR);
	curr = node;
	while (curr->type == TYPE_REDIRECT)
	{
		if (handle_redir(idx_cmd, &fd_table, curr->content) != SUCCESS)
			break ;
		curr = ((t_redirect *)curr->content)->child;
	}
	t_list	*temp = fd_table;
	while (temp)
	{
		printf("shell_fd: %d, proc_fd: %d\n", ((t_fd *)(temp->content))->fd_shell, ((t_fd *)(temp->content))->fd_proc);
		temp = temp->next;
	}
	execute_cmd(curr);
	//fd table clear;
	//delete temp file;
}
