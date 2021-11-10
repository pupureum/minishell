/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:29:03 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/09 16:01:27 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft.h"
# include "error.h"

# define TYPE_PIPE 		 	0
# define TYPE_REDIRECT		1
# define TYPE_CMD 			2
# define TYPE_ARG  			4
# define TYPE_REDIR_STDIN	8
# define TYPE_REDIR_STDOUT	16
# define TYPE_REDIR_HEREDOC	32
# define TYPE_REDIR_APPEND	64

typedef struct s_minishell
{
	t_list	*export_list;
	t_list	*env_list;
	char	*line;
	int		cmd_cnt;
	int		exit_status;
}	t_minishell;

typedef struct s_AST_Node
{
	int		type;
	void	*content;
}	t_AST_Node;
#endif
