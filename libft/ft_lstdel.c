/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 08:27:27 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 16:25:06 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*suivant;

	tmp = *alst;
	while (tmp)
	{
		suivant = tmp->next;
		ft_lstdelone(&tmp, del);
		tmp = suivant;
	}
	(*alst) = NULL;
}
