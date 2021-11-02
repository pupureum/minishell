/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:12:39 by bylee             #+#    #+#             */
/*   Updated: 2021/11/02 20:25:47 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (handle_redir(cmd_idx, &line, &fd_table, curr->content) != SUCCESS)
			break ;
		curr = ((t_redirect *)curr->content)->child;
	}
	//execute();
	//fd table clear;
	//delete temp file;
}