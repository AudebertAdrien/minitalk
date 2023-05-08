/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:17:00 by aaudeber          #+#    #+#             */
/*   Updated: 2023/02/17 17:32:04 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(NULL);
	if (!new)
		return (NULL);
	ptr = new;
	while (lst)
	{
		new->content = (*f)(lst->content);
		if (lst->next)
		{
			new->next = ft_lstnew(NULL);
			if (!new->next)
			{
				ft_lstclear(&ptr, del);
				return (NULL);
			}
			new = new->next;
		}
		lst = lst->next;
	}
	return (ptr);
}
