/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:21:21 by desausag          #+#    #+#             */
/*   Updated: 2020/11/12 15:51:41 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*p;

	i = ft_strlen(str) + 1;
	p = (char*)malloc(sizeof(char) * (i));
	if (p == NULL)
		return (NULL);
	ft_memcpy(p, str, i);
	return (p);
}
