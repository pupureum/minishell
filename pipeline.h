/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:55:43 by bylee             #+#    #+#             */
/*   Updated: 2021/10/18 20:57:30 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>

typedef struct	s_token
{
	int		type;
	char	*value;
}				t_token;

#endif