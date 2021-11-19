/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:35:30 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/19 16:39:18 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_rror
{
	SUCCESS = 0,
	MALLOC_ERROR,
	TERMIOS_ERROR,
	RL_ERROR,
	PARSE_ERROR,
	PIPE_ERROR,
	PROCCESS_ERROR,
	FORK_ERROR,
	FD_DUP_ERROR,
	FILE_OPEN_ERROR
}	t_error;

/*
error.c
*/
void	error(t_error error_code);

#endif
