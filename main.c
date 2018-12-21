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

int		open_file(char *str, int fd)
{
	int				nb_tetriminos;
	t_tetriminos	tetriminos[MAX_TETRI];
	int				nb_blocs;
	int				board_size;

	nb_tetriminos = 0;
	nb_blocs = 0;
	board_size = 0;
	if ((fd = open(str, O_RDONLY)) > 0)
	{
		if (!(fillit(fd, tetriminos, &nb_tetriminos, nb_blocs)))
		{
			ft_putendl("error");
			return (0);
		}
		board_size = valid_tetriminos(nb_tetriminos, tetriminos);
		if (board_size < 2)
		{
			ft_putendl("error");
			return (0);
		}
		get_grid(nb_tetriminos, tetriminos, board_size);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;

	fd = 0;
	if (argc != 2)
	{
		ft_putendl("Usage : ./fillit input_fichier");
		return (0);
	}
	open_file(argv[1], fd);
	write(1, "\n", 1);
	return (0);
}
