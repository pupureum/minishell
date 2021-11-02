/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:21:08 by bylee             #+#    #+#             */
/*   Updated: 2020/10/07 21:20:59 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	iter;

	index = 0;
	if (needle[index] == '\0')
		return ((char *)haystack);
	while (index < len && haystack[index])
	{
		iter = 0;
		while (haystack[index + iter] == needle[iter] && index + iter < len)
		{
			iter++;
			if (needle[iter] == '\0')
				return ((char *)haystack + index);
		}
		index++;
	}
	return (0);
}
