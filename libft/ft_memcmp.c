/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:27:44 by desausag          #+#    #+#             */
/*   Updated: 2020/11/11 14:01:04 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*v1;
	unsigned char	*v2;
	size_t			i;

	v1 = (unsigned char*)s1;
	v2 = (unsigned char*)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((v1[i] - v2[i] == 0) && (n > 1))
	{
		i++;
		n--;
	}
	return (v1[i] - v2[i]);
}
