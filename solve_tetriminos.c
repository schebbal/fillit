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

static void	remove_tetri(t_board *board, char ch)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (i <= 3 && board->grid[y])
	{
		x = 0;
		while (board->grid[y][x])
		{
			if (i > 3)
				return ;
			if (board->grid[y][x] == ch)
			{
				board->grid[y][x] = '.';
				i++;
			}
			x++;
		}
		y++;
	}
}

static int	valid_pos(t_board *board, t_tetriminos tetri)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (i < 4)
	{
		k = tetri.y[i];
		while (i < 4 && tetri.y[i] == k)
		{
			if ((board->x + tetri.x[i] >= board->size) ||
				(board->y + tetri.y[i] >= board->size) ||
				(board->grid[board->y + tetri.y[i]][board->x +
				tetri.x[i]] != '.'))
				return (0);
			i++;
		}
	}
	return (1);
}

static int	put_tetri_to_pos(t_board *board, t_tetriminos tetri)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if ((valid_pos(board, tetri)) == 0)
		return (0);
	while (i < 4)
	{
		k = tetri.y[i];
		while (i < 4 && tetri.y[i] == k)
		{
			board->grid[board->y + tetri.y[i]][board->x + tetri.x[i]] =
			tetri.car;
			i++;
		}
	}
	if (i >= 3)
		return (1);
	return (0);
}

int			solve_board(t_board board, int nb_tetri,
t_tetriminos tetri[nb_tetri], int *j)
{
	int		k;

	k = 0;
	if (*j >= nb_tetri || !board.grid)
		return (1);
	board.y = 0;
	while (board.y < board.size)
	{
		board.x = 0;
		while (board.x < board.size)
		{
			if ((put_tetri_to_pos(&board, tetri[*j])) != 0)
			{
				k = *j + 1;
				if (solve_board(board, nb_tetri, tetri, &k) == 1)
					return (1);
				remove_tetri(&board, tetri[*j].car);
			}
			board.x++;
		}
		board.y++;
	}
	return (0);
}
