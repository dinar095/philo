/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:15:25 by desausag          #+#    #+#             */
/*   Updated: 2020/11/09 12:21:14 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*b;
	size_t			i;

	i = 0;
	b = (unsigned char *)destination;
	while (i != n)
	{
		b[i++] = c;
	}
	return (destination);
}
