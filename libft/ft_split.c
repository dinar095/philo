/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 11:57:51 by desausag          #+#    #+#             */
/*   Updated: 2020/11/19 14:06:19 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**make_arr(char const *s, char c)
{
	char	**result;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != 0)
		{
			n++;
			while (s[i] != c && s[i] != 0)
				i++;
		}
	}
	result = (char **)malloc(sizeof(char *) * (n + 1));
	if (result)
		result[n] = 0;
	return (result);
}

int		free_need(char **arr, int word)
{
	int i;

	i = 0;
	if (!arr[word])
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		start;
	int		word;
	char	**result;

	if (!s)
		return (NULL);
	i = 0;
	word = 0;
	result = make_arr(s, c);
	if (!result)
		return (0);
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i] != 0)
			i++;
		if (start < i)
			result[word] = ft_substr(s, start, i - start);
		if (start < i && free_need(result, word++))
			return (0);
	}
	return (result);
}
