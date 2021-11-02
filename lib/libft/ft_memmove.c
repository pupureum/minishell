/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:39:34 by bylee             #+#    #+#             */
/*   Updated: 2021/06/30 20:15:12 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	index;

	index = 0;
	if (!dst && !src)
		return ((void *)0);
	if ((unsigned char *)dst < (unsigned char *)src)
	{
		while (index < len)
		{
			((unsigned char *)dst)[index] = ((unsigned char *)src)[index];
			index++;
		}
	}
	else
	{
		while (index < len)
		{
			((unsigned char *)dst)[len - index - 1]
				= ((unsigned char *)src)[len - index - 1];
			index++;
		}
	}
	return (dst);
}
