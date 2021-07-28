/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:01:26 by desausag          #+#    #+#             */
/*   Updated: 2020/11/13 14:45:19 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void		*ptr;

	ptr = malloc(num * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}
