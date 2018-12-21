/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 14:21:54 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 16:22:01 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	tmp2 = ft_lstnew(tmp->content, tmp->content_size);
	if (!tmp2)
		return (NULL);
	new = tmp2;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		tmp2->next = ft_lstnew(tmp->content, tmp->content_size);
		if (tmp2->next == NULL)
			return (NULL);
		tmp2 = tmp2->next;
		lst = lst->next;
	}
	return (new);
}
