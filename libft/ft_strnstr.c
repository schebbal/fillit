/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 16:24:22 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/20 12:09:17 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	z;

	i = 0;
	z = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			z = 0;
			while (to_find[z] == str[i + z])
			{
				if (i + z + 1 > len)
					return (NULL);
				if (to_find[z + 1] == '\0')
					return ((char *)(str + i));
				z++;
			}
		}
		i++;
	}
	return (NULL);
}
