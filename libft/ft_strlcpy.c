/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:40:31 by desausag          #+#    #+#             */
/*   Updated: 2020/11/19 14:06:19 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *destination, const char *append, size_t size)
{
	size_t	n;

	n = 0;
	if (!destination || !append)
		return (0);
	if (size == 0)
		return (ft_strlen(append));
	while (append[n] != '\0' && n < size - 1)
	{
		destination[n] = append[n];
		n++;
	}
	destination[n] = '\0';
	return (ft_strlen(append));
}
