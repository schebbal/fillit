/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 15:37:36 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 15:43:33 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	len;

	if ((dest = (char*)malloc(ft_strlen(src) + 1)) != NULL)
	{
		len = 0;
		while (src[len])
		{
			dest[len] = src[len];
			len++;
		}
		dest[len] = '\0';
	}
	return (dest);
}
