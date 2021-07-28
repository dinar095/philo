/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:00:03 by desausag          #+#    #+#             */
/*   Updated: 2020/11/19 14:06:19 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *large, const char *small, size_t len)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = ft_strlen(small);
	if (i == 0)
		return ((char *)large);
	while (large[n] != '\0' && (n + i <= len))
	{
		if (large[n] == small[0])
		{
			if (!ft_strncmp(large + n, small, i))
				return ((char *)(large + n));
		}
		n++;
	}
	return (NULL);
}
