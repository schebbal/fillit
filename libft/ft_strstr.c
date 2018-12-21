/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 11:47:52 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 17:40:27 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int	i;
	int	z;

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
				if (to_find[z + 1] == '\0')
					return ((char *)(str + i));
				z++;
			}
		}
		i++;
	}
	return (NULL);
}
