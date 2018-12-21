/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 14:42:50 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/19 12:32:06 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	unsigned char	tmp;
	size_t			i;

	tmp1 = (unsigned char *)dst;
	tmp2 = (unsigned char *)src;
	tmp = c;
	i = 0;
	while (i < n)
	{
		tmp1[i] = tmp2[i];
		if (tmp1[i] == tmp)
			return (tmp1 + i + 1);
		i++;
	}
	return (NULL);
}
