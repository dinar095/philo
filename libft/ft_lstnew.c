/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:25:20 by desausag          #+#    #+#             */
/*   Updated: 2020/11/18 09:37:25 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = 0;
	tmp = (t_list *)(malloc(sizeof(t_list)));
	if (tmp)
	{
		tmp->content = content;
		tmp->next = NULL;
		return (tmp);
	}
	return (NULL);
}
