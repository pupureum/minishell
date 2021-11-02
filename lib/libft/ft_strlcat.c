/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:02:32 by bylee             #+#    #+#             */
/*   Updated: 2020/10/13 19:13:05 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	iter;
	size_t	length;

	iter = 0;
	length = 0;
	while (dst[length])
		length++;
	while (src[iter] && iter + length + 1 < dstsize)
	{
		dst[length + iter] = src[iter];
		iter++;
	}
	dst[iter + length] = '\0';
	while (src[iter])
		iter++;
	if (length > dstsize)
		return (dstsize + iter);
	else
		return (length + iter);
}
