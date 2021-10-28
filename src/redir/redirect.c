/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:55:17 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/27 20:51:07 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_error	redirect(t_list *redirs, t_list **fd_table)
{
	while (redirs)
	{
		if (((t_redir *)redirs->content)->type == HEREDOC)
			heredoc()
		redirs = redirs->next;
	}
}
