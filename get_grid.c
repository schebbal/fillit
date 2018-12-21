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

void	init_board(t_board board)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < board.size)
	{
		i = 0;
		while (i < board.size)
		{
			board.grid[j][i] = '.';
			i++;
		}
		j++;
	}
}

char	**ft_strnew_board(size_t size)
{
	char	**str;
	size_t	i;

	if (!(str = (char **)malloc(sizeof(char *) * size + 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = ft_strnew(size);
		i++;
	}
	return (str);
}

void	delete_grid(char **grid)
{
	ft_memdel((void **)grid);
}

void	print_board(t_board board)
{
	int i;
	int j;

	j = 0;
	while (j < board.size)
	{
		i = 0;
		while (i < board.size)
		{
			ft_putchar(board.grid[j][i]);
			i++;
		}
		ft_putchar('\n');
		j++;
	}
}

void	get_grid(int nb_tetriminos, t_tetriminos tetriminos[nb_tetriminos],
int board_size)
{
	t_board		board;
	int			vld;
	int			j;

	if (!(board.grid = ft_strnew_board(board_size)))
		return ;
	board.size = board_size;
	j = 0;
	vld = 0;
	init_board(board);
	while (solve_board(board, nb_tetriminos, tetriminos, &j) == 0)
	{
		delete_grid(board.grid);
		board_size++;
		if (!(board.grid = ft_strnew_board(board_size)))
			return ;
		board.size = board_size;
		init_board(board);
		j = 0;
	}
	print_board(board);
}
