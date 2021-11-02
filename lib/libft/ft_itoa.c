/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:21:18 by bylee             #+#    #+#             */
/*   Updated: 2021/06/30 20:17:21 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getlength(int n)
{
	size_t	length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		length++;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	length;

	length = ft_getlength(n);
	result = (char *)malloc(sizeof(char) * (length + 1));
	result[length] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		while (length-- > 1)
		{
			result[length] = '0' - n % 10;
			n /= 10;
		}
	}
	else
	{
		while (length--)
		{
			result[length] = '0' + n % 10;
			n /= 10;
		}
	}
	return (result);
}
