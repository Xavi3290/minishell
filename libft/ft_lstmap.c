/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:02:59 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/17 19:09:25 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*clear_all(t_list	*first, void (*del)(void *))
{
	ft_lstclear(&first, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		size;
	t_list	*first;
	t_list	*curr;

	if (!lst || !f || !del)
		return (NULL);
	size = ft_lstsize(lst);
	first = (t_list *) malloc(sizeof(t_list));
	if (!first)
		return (NULL);
	first -> content = f(lst -> content);
	curr = first;
	while (--size > 0)
	{
		lst = lst -> next;
		curr -> next = (t_list *) malloc(sizeof(t_list));
		if (!curr -> next)
			return (clear_all(first, del));
		curr = curr -> next;
		curr -> content = f(lst -> content);
	}
	curr -> next = NULL;
	return (first);
}
