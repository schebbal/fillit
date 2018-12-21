/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fillit.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 10:39:41 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 14:23:49 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"

int		ft_abs(int a, int b)
{
	return ((a - b > 0) ? a - b : b - a);
}

int		get_board_size(int n_tetriminos)
{
	int res;

	res = 2;
	while (res * res < n_tetriminos * 4)
		res++;
	return (res);
}

void	ft_put_up_left(t_tetriminos *tetriminos, int xmax, int ymax)
{
	int		i;

	i = 0;
	xmax = 0;
	ymax = 0;
	while (i < 4)
	{
		tetriminos->xmin = ((tetriminos->x[i] < tetriminos->xmin) ?
		tetriminos->x[i] : tetriminos->xmin);
		tetriminos->ymin = ((tetriminos->y[i] < tetriminos->ymin) ?
		tetriminos->y[i] : tetriminos->ymin);
		xmax = ((tetriminos->x[i] > xmax) ? tetriminos->x[i] : xmax);
		ymax = ((tetriminos->y[i] > ymax) ? tetriminos->y[i] : ymax);
		i++;
	}
	tetriminos->l = xmax - tetriminos->xmin + 1;
	tetriminos->h = ymax - tetriminos->ymin + 1;
	i = 0;
	while (i < 4)
	{
		tetriminos->x[i] -= tetriminos->xmin;
		tetriminos->y[i] -= tetriminos->ymin;
		i++;
	}
}

int		ctrl_adjacent_blocs(t_tetriminos ter, int j)
{
	int		i;

	i = 0;
	while (i++ < 4)
	{
		if (ter.x[i % 4] == ter.x[(i + 1) % 4] &&
		ft_abs(ter.y[i % 4], ter.y[(i + 1) % 4]) < 2)
			j++;
		if (ter.x[i % 4] == ter.x[(i + 2) % 4] &&
		ft_abs(ter.y[i % 4], ter.y[(i + 2) % 4]) < 2)
			j++;
		if (ter.x[i % 4] == ter.x[(i + 3) % 4] &&
		ft_abs(ter.y[i % 4], ter.y[(i + 3) % 4]) < 2)
			j++;
		if (ter.y[i % 4] == ter.y[(i + 1) % 4] &&
		ft_abs(ter.x[i % 4], ter.x[(i + 1) % 4]) < 2)
			j++;
		if (ter.y[i % 4] == ter.y[(i + 2) % 4] &&
		ft_abs(ter.x[i % 4], ter.x[(i + 2) % 4]) < 2)
			j++;
		if (ter.y[i % 4] == ter.y[(i + 3) % 4] &&
		ft_abs(ter.x[i % 4], ter.x[(i + 3) % 4]) < 2)
			j++;
	}
	return (j);
}

int		valid_tetriminos(int nb_tetriminos, t_tetriminos *tetriminos)
{
	int		i;
	int		l;
	int		board_size;

	i = 0;
	board_size = 0;
	while (i < nb_tetriminos)
	{
		l = ctrl_adjacent_blocs(tetriminos[i], 0);
		if (l < 6)
			return (0);
		ft_put_up_left(&tetriminos[i], 0, 0);
		i++;
	}
	if (nb_tetriminos == 1)
	{
		board_size = (ft_abs(tetriminos[0].x[3], tetriminos[0].x[0]) >
		ft_abs(tetriminos[0].y[3], tetriminos[0].y[0]) ?
		ft_abs(tetriminos[0].x[3], tetriminos[0].x[0]) + 1 :
		ft_abs(tetriminos[0].y[3], tetriminos[0].y[0]) + 1);
	}
	else
		board_size = get_board_size(nb_tetriminos);
	return (board_size);
}
