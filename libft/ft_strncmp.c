/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:25:04 by desausag          #+#    #+#             */
/*   Updated: 2020/11/06 22:12:18 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t c)
{
	size_t	i;
	int		r;

	i = 0;
	while ((s1[i] == s2[i]) && (i < c) && (s1[i] != '\0') && (s2[i] != '\0'))
		i++;
	if (i == c)
		return (0);
	r = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (r);
}
