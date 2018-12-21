/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 20:03:34 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 17:45:58 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j++] == c)
			i++;
	}
	j = 0;
	while (s[j])
	{
		if (s[j] == c)
		{
			if (i == 1)
				return ((char *)s + j);
			else
				i--;
		}
		j++;
	}
	if (s[j] == c)
		return ((char *)s + j);
	return (NULL);
}
