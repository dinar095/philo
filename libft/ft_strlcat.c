/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:30:41 by desausag          #+#    #+#             */
/*   Updated: 2020/11/12 11:25:15 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *destination, const char *append, size_t size)
{
	size_t	dst_size;
	size_t	n;

	dst_size = 0;
	while (destination[dst_size] != '\0' && dst_size < size)
		dst_size++;
	if (dst_size == size)
		return (size + ft_strlen(append));
	n = dst_size;
	while (n < size - 1 && append[n - dst_size] != '\0')
	{
		destination[n] = append[n - dst_size];
		n++;
	}
	destination[n] = '\0';
	return (dst_size + ft_strlen(append));
}
