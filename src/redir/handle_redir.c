/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:34 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/23 17:13:28 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/* 
t_redir_type	get_redir_type(t_token **tokens)
{
	if (tokens[0]->type == REDIRECT_LEFT)
	{
		if (ft_strncmp(tokens[0]->value, "<", 2) == 0)
			return (INPUT);
		else
			return (HEREDOC);
	}
	else if (tokens[1]->type == REDIRECT_RIGHT)
	{
		if (ft_strncmp(tokens[1]->value, ">", 2) == 0)
			return (OUTPUT);
		else
			return (OUTPUT_APPEND);
	}
	else
		
} */

/* t_redir	parse_redir(t_token **tokens)
{
	t_redir	result;

	result.type = get_redir_type(tokens);
} */

t_error	append_redir(t_redir redir, t_list **redirs)
{
	t_redir	*new;
	t_list	*new_list;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return (MALLOC_ERROR);
	ft_memcpy(new, &redir, sizeof(t_redir));
	new_list = ft_lstnew(new);
	if (new_list == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back(redirs, new_list);
	return (SUCCESS);
}

t_error	handle_redir(t_list **fd_table, t_token **tokens)
{
	int		iter;
	t_list	*redirs;
	t_redir	redir;

	iter = 0;
	redirs = NULL;
	while (tokens[iter])
	{
		redir = parse_redir(tokens + iter); //TODO:Clarify after knowing token
		if (redir.type >= INPUT)
		{
			if (append_redir(redir, &redirs) != SUCCESS)
			{
				ft_lstclear(&redirs, free);
				return (MALLOC_ERROR);
			}
			del_redir_tokens(tokens + iter, 2); //TODO:clarify after clarification of token
		}
		else
			iter++;
	}
	return (redirect(redirs, fd_table));
}
