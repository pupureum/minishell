/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:22:15 by bylee             #+#    #+#             */
/*   Updated: 2020/10/09 21:49:03 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	iter;

	iter = 0;
	if (!dst && !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (iter < dstsize - 1 && src[iter])
	{
		dst[iter] = src[iter];
		iter++;
	}
	if (dstsize > 0)
		dst[iter] = '\0';
	return (ft_strlen(src));
}
