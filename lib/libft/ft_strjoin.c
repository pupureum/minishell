/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:59:27 by bylee             #+#    #+#             */
/*   Updated: 2021/06/30 20:12:38 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	length;
	size_t	iter;
	char	*result;

	if (!s1 || !s2)
		return (0);
	index = 0;
	iter = 0;
	length = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(length);
	if (!result)
		return (0);
	while (s1[iter])
		result[index++] = s1[iter++];
	iter = 0;
	while (s2[iter])
		result[index++] = s2[iter++];
	result[index] = '\0';
	return (result);
}
