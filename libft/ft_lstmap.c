/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:11:05 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/17 00:16:04 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*t;
	t_list	*tmp;

	if (!del || !f || !lst)
		return (0);
	t = ft_lstnew(f(lst->content));
	if (!t)
		return (0);
	tmp = t;
	lst = lst->next;
	while (lst)
	{
		t->next = ft_lstnew(f(lst->content));
		if (!t->next)
		{
			ft_lstclear(&tmp, del);
			return (0);
		}
		t = t->next;
		lst = lst->next;
	}
	t->next = 0;
	return (tmp);
}
