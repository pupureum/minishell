/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:59:27 by bylee             #+#    #+#             */
/*   Updated: 2021/10/24 16:04:05 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

int	main(void)
{
	int	is_pipe;
	int	result;

	is_pipe = 1;
	result = 0;
	if (is_pipe)
		result = build_pipeline();
	printf("%d\n", result);
	return (0);
}
