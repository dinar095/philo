/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:03:06 by desausag          #+#    #+#             */
/*   Updated: 2020/11/19 14:06:19 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned char	*dest;
	unsigned char	*sour;
	size_t			i;

	i = 0;
	dest = (unsigned char*)destination;
	sour = (unsigned char*)source;
	while (i != n)
	{
		dest[i] = sour[i];
		i++;
	}
	return (destination);
}
