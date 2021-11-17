/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:12:39 by bylee             #+#    #+#             */
/*   Updated: 2021/11/17 20:05:56 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_shell;

void	print_fd_table(t_list *fd_table)
{
	while (fd_table)
	{
		printf("shell_fd: %d. proc_fd: %d\n", \
			((t_fd *)(fd_table->content))->fd_shell, \
			((t_fd *)(fd_table->content))->fd_proc);
		fd_table = fd_table->next;
	}
}

static void	delete_tempfile(int idx_cmd)
{
	char	*filename;

	filename = format_filename(idx_cmd);
	if (filename == NULL)
		error(MALLOC_ERROR);
	unlink(filename);
	free(filename);
}

static void	clear_redir_fd(t_list **fd_table)
{
	t_list	*curr;

	curr = *fd_table;
	while (curr)
	{
		close(((t_fd *)(curr->content))->fd_proc);
		curr = curr->next;
	}
	ft_lstclear(fd_table, free);
}

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
	print_fd_table(fd_table);
	if (curr->type == TYPE_CMD)
		execute_cmd(curr, fd_table);
	clear_redir_fd(&fd_table);
	delete_tempfile(idx_cmd);
}
