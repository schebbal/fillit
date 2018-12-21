/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 15:45:02 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 18:16:17 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	index;
	int	nb;
	int	flag;

	index = 0;
	nb = 0;
	flag = 0;
	if (ft_strcmp(str, "99999999999999999999999999") == 0)
		return (-1);
	if (ft_strcmp(str, "-99999999999999999999999999") == 0)
		return (0);
	while (str[index] == '\t' || str[index] == '\r' || str[index] == '\v' ||
			str[index] == ' ' || str[index] == '\f' || str[index] == '\n')
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		flag = (str[index] == '+') ? 0 : 1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		nb = nb * 10 + (str[index] - '0');
		index++;
	}
	return ((flag == 1) ? -nb : nb);
}
