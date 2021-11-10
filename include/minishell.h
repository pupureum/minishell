/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:03:21 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/10 22:11:18 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "interpreter.h"
# include "pipeline.h"
# include "redirection.h"
# include "command.h"

t_minishell	g_shell;

/*
init_envp.c
*/
t_error	init_envp(char *envp[]);

/*
init_term.c
*/
t_error	set_term_mode(struct termios *term);
t_error	get_term_mode(struct termios *term);
t_error	init_nonc_mode(struct termios *new);
t_error	init_term(struct termios *org, struct termios *new);

void	redir_and_exe(int idx_cmd, t_AST_Node *node);

/*
execute_cmd.c
*/
void	execute_cmd(t_AST_Node *node);

/*
sort_export_list.c
*/
void	sort_export_list(t_list **export_list);

/*
TEMPORARY
*/

# define END_COLOR		"\033[0m"
# define KEY_COLOR		"\033[1;35m"
# define VALUE_COLOR	"\033[0;32m"

void	free_tokens(t_list *list);
void	destruct_AST(t_AST_Node *node);

#endif
