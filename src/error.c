/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:58:37 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/19 16:41:23 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*format_err(t_error error_code)
{
	if (error_code == MALLOC_ERROR)
		return ("error while allocating memory\n");
	else if (error_code == TERMIOS_ERROR)
		return ("error setting termios val\n");
	else if (error_code == RL_ERROR)
		return ("error with readline lib\n");
	else if (error_code == PARSE_ERROR)
		return ("error parsing command\n");
	else if (error_code == PIPE_ERROR)
		return ("error calling syscall pipe\n");
	else if (error_code == PROCCESS_ERROR)
		return("error while executing child proccess\n");\
	else if (error_code == FORK_ERROR)
		return ("error during syscall fork()\n");
	else if (error_code == FD_DUP_ERROR)
		return ("error dupplicating file descriptor\n");
	else if (error_code == FILE_OPEN_ERROR)
		return ("error opening file\n");
	else
		return ("unknown error\n");
}

static void	print_error(t_error error_code)
{
	char	*msg;

	msg = format_err(error_code);
	write(2, msg, ft_strlen(msg));
}

void	error(t_error error_code)
{
	print_error(error_code);
	exit(error_code);
}
