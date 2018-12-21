/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/20 09:45:55 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/20 10:43:27 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**tab;
	int		j;
	int		k;

	k = 0;
	i = 0;
	if (!s || !(tab = ft_memalloc(sizeof(char *) * (ft_countwords(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		j = 0;
		while (s[i] != c && s[i])
		{
			j++;
			i++;
		}
		if (j)
			tab[k++] = ft_strndup(&s[i - j], j);
	}
	return (tab);
}
