/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:34 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/20 19:31:42 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_error	handle_redir(t_fd **fd_table, t_token **tokens)
{
	int		iter;
	t_list	*redirs;

	iter = 0;
	while (tokens[iter])
	{
		if (ft_strncmp(tokens[iter]->value, "<", 2) == 0
			|| ft_strncmp(tokens[iter]->value, ">", 2) == 0
			|| ft_strncmp(tokens[iter]->value, ">>", 3) == 0)
			iter += append_redir(&redirs, tokens);
	}
	return (SUCCESS);
}
