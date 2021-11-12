/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:58:37 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/12 22:17:42 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(t_error error_code)
{
	// if (error_code == MALLOC_ERROR)
	// 	printf("malloc_err\n");
	printf("error_code: %d\n", error_code);
}

void	error(t_error error_code)
{
	print_error(error_code);
	exit(error_code);
}
