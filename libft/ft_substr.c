/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:07:51 by desausag          #+#    #+#             */
/*   Updated: 2020/11/16 13:45:43 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (0);
	ptr = 0;
	if (ft_strlen(s) <= start)
	{
		ptr = (char *)malloc(1);
		if (ptr)
			ptr[0] = 0;
		return (ptr);
	}
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (ptr);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
