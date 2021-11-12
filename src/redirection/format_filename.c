/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:57:37 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/12 22:57:52 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*format_filename(int idx)
{
	char	*num_str;
	char	*filename;

	num_str = ft_itoa(idx);
	filename = ft_strjoin(".tempfile", num_str);
	free(num_str);
	return (filename);
}
