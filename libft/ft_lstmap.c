/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:09:09 by desausag          #+#    #+#             */
/*   Updated: 2020/11/18 12:39:28 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*start;

	prev = 0;
	start = 0;
	while (lst)
	{
		tmp = ft_lstnew(((*f)(lst->content)));
		if (tmp == 0)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		if (prev)
			prev->next = tmp;
		else
			start = tmp;
		prev = tmp;
		lst = lst->next;
	}
	return (start);
}
