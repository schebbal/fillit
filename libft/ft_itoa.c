/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/10 18:30:05 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 18:03:31 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long f)
{
	int	i;

	i = 0;
	if (f < 0)
	{
		f = -f;
		i++;
	}
	if (f == 0)
		i++;
	while (f > 0)
	{
		f /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	f;

	f = n;
	i = ft_nbrlen(f);
	if (!(str = (char *)malloc(sizeof(*str) * i + 1)))
		return (NULL);
	str[i] = '\0';
	if (n < 0)
		f = -f;
	while (i > 0)
	{
		str[--i] = (f % 10) + '0';
		f /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
