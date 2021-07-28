/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:55:49 by desausag          #+#    #+#             */
/*   Updated: 2020/11/10 11:12:14 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;
	size_t			i;

	dest = (unsigned char*)destination;
	src = (unsigned char*)source;
	i = 0;
	while (i != n)
	{
		dest[i] = src[i];
		if (src[i] == (unsigned char)c)
		{
			return ((void *)dest + i + 1);
		}
		i++;
	}
	return (NULL);
}
