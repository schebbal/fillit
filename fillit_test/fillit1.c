/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fillit.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 10:39:41 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 18:03:35 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fillit.h"

int		ft_abs(int a, int b)
{
	return ((a - b > 0) ? a - b : b - a);
}

int		read_file(const int fd, char **line)
{
	int	ret;

	ret = get_next_line(fd, line);
	return (ret);
}

void	load_tetriminos(char *line, int nbline,
		t_tetriminos tetriminos[MAX_TETRI], int *j)
{
	int				vcar;
	int				iy;
	int				i;

	vcar = 0;
	i = nbline / 5;
	iy = nbline % 5 - 1;
	if (nbline % 5 != 0)
	{
		while (line[vcar])
		{
			if (line[vcar] == '#')
			{
				tetriminos[i].x[*j] = vcar;
				tetriminos[i].y[*j] = iy;
				tetriminos[i].car = i + 'A';
				tetriminos[i].pos = i;
				tetriminos[i].xmin = 3;
				tetriminos[i].ymin = 3;
				(*j)++;
			}
			vcar++;
		}
	}
}

int		valid_line(char *line, int nbline, int *nbloc)
{
	int vcar;
	int	vline;

	vline = 1;
	vcar = 0;
	while (line[vcar])
	{
		if (nbline % 5 != 0 && line[vcar] == '#')
			(*nbloc)++;
		if (nbline % 5 == 0 && line[vcar] != '\n')
		{
			vline = 0;
			break ;
		}
		if (nbline % 5 != 0 && (vcar > 3 || (line[vcar] != '.' &&
						line[vcar] != '#')))
		{
			vline = 0;
			break ;
		}
		vcar++;
	}
	if (nbline % 5 == 0)
		(*nbloc) = 0;
	return (vline);
}

void	ft_put_up_left(t_tetriminos *tetriminos)
{
	int		i;
	int		xmax;
	int		ymax;

	i = 0;
	xmax = 0;
	ymax = 0;
	while (i < 4)
	{
		tetriminos->xmin = ((tetriminos->x[i] < tetriminos->xmin) ? tetriminos->x[i] : tetriminos->xmin);
		tetriminos->ymin = ((tetriminos->y[i] < tetriminos->ymin) ? tetriminos->y[i] : tetriminos->ymin);
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

int		ctrl_adjacent_blocs(t_tetriminos tetriminos)
{
	int		i;		
	int		j;

	j = 0;
	i = 0;
	while (i < 4)
	{
		if (tetriminos.x[i % 4] == tetriminos.x[(i + 1) % 4] && 
			ft_abs(tetriminos.y[i % 4], tetriminos.y[(i + 1) % 4]) < 2)
			j++;
		if (tetriminos.x[i % 4] == tetriminos.x[(i + 2) % 4] && 
			ft_abs(tetriminos.y[i % 4], tetriminos.y[(i + 2) % 4]) < 2)
			j++;
		if (tetriminos.x[i % 4] == tetriminos.x[(i + 3) % 4] && 
			ft_abs(tetriminos.y[i % 4], tetriminos.y[(i + 3) % 4]) < 2)
			j++;
		if (tetriminos.y[i % 4] == tetriminos.y[(i + 1) % 4] && 
			ft_abs(tetriminos.x[i % 4], tetriminos.x[(i + 1) % 4]) < 2)
			j++;
		if (tetriminos.y[i % 4] == tetriminos.y[(i + 2) % 4] && 
			ft_abs(tetriminos.x[i % 4], tetriminos.x[(i + 2) % 4]) < 2)
			j++;
		if (tetriminos.y[i % 4] == tetriminos.y[(i + 3) % 4] && 
			ft_abs(tetriminos.x[i % 4], tetriminos.x[(i + 3) % 4]) < 2)
			j++;
		i++;
	}
	return (j);
}

int		get_board_size(int n_tetriminos)
{
	int res;

	res = 2;
	while (res * res < n_tetriminos * 4)
		res++;
	res++;
	return (res);
}

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

int		put_one_tetri_to_board(t_board *board, t_tetriminos tetri)
{
	int i;
	int	k;
	int	x;
	int	y;

	i = 0;
	k = 0;
	x = board->x;
	y = board->y;
	printf(">>>>>1-OK,y=%d, x=%d, k=%d, h=%d, l=%d, size=%d\n", y, x, k, tetri.h, tetri.l, board->size);
	while (i < 4)
	{
		if ((x + tetri.x[i]) > board->size)
		{
			y += 1;
			x = board->x;
			x = 0;
		}
		if ((y + tetri.y[i]) >= board->size)
			return (1);
		printf(">>>>>2-OK,y=%d, yi=%d,x=%d, xi=%d,k=%d,h=%d,l=%d,size=%d, car=%c\n", y, tetri.y[i], x, tetri.x[i], k, tetri.h, tetri.l, board->size, tetri.car);
		board->grid[y + tetri.y[i]][x + tetri.x[i]] = tetri.car;
		i++;
	}
	if (x + tetri.l < board->size)
		board->x += tetri.l;
	else
		board->y += tetri.h;
	printf(">>>>>3-OK,x=%d, y=%d<>xi=%d,yi=%d<>k=%d,h=%d,l=%d,size=%d\n", board->x, board->y, tetri.x[i-1], tetri.y[i-1], k, tetri.h, tetri.l, board->size);
	return (0);
}

int		put_tetriminos_to_board(t_board board, int nb_tetri, t_tetriminos tetri[nb_tetri])
{
	int	j;

	j = 0;
	board.x = 0;
	board.y = 0;
	while (j < nb_tetri)
	{
		printf(">>>>>>>>>>>>>>>tetriminos No =%d\n",j + 1);
		if (put_one_tetri_to_board(&board, tetri[j]) == 1)
			return (1);

		j++;
	}
	return (0);
}

char	**ft_strnew_tab(size_t size)
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

void	backtrack(int nb_tetriminos, t_tetriminos tetriminos[nb_tetriminos], int board_size)
{
	t_board		board;

	if(!(board.grid = ft_strnew_tab(board_size)))
		return ;
	board.size = board_size;
	printf("1-board_size=%d\n", board.size);
	init_board(board);
	if (put_tetriminos_to_board(board, nb_tetriminos, tetriminos) == 1)
	{
		backtrack(nb_tetriminos, tetriminos, board_size + 1);
	}
	print_board(board);
}

int		valid_tetriminos(int nb_tetriminos, t_tetriminos *tetriminos)
{
	int		i;
	int		j;
	int		board_size;

	i = 0;
	j = 0;
	board_size = 0;
	while (i < nb_tetriminos)
	{
		j += ctrl_adjacent_blocs(tetriminos[i]);
		if (j < 6)
			return (0);
		ft_put_up_left(&tetriminos[i]);
		i++;
	}
	if (nb_tetriminos == 1)
	{
		board_size = (ft_abs(tetriminos[0].x[3], tetriminos[0].x[0]) > 
		ft_abs(tetriminos[0].y[3], tetriminos[0].y[0]) ? ft_abs(tetriminos[0].x[3], tetriminos[0].x[0]) + 1 :
		ft_abs(tetriminos[0].y[3], tetriminos[0].y[0]) + 1);
	}
	else
		board_size = get_board_size(nb_tetriminos);
	backtrack(nb_tetriminos, tetriminos, board_size);
	return (1);
}

int		fillit(int fd, t_tetriminos tetriminos[MAX_TETRI], int *nbtetri, int n)
{
	char	*line;
	int		nbline;
	int		vld;
	int		nbloc;

	nbline = 1;
	nbloc = 0;
	vld = 1;
	while (vld && (fd > 0 && (read_file(fd, &line) > 0)))
	{
		vld = valid_line(line, nbline, &nbloc);
		if (nbline % 5 == 0)
		{
			n = 0;
			(*nbtetri)++;
		}
		if ((nbline + 1) % 5 == 0 && nbloc != 4)
			vld = 0;
		if (vld)
			load_tetriminos(line, nbline, tetriminos, &n);
		nbline++;
	}
	close(fd);
	if (nbline > 1)
		(*nbtetri)++;
	printf(">>nbtetriminos=%d\n", *nbtetri);
	return (vld);
}

int		main(int argc, char **argv)
{
	int				fd;
	int				nb_tetriminos;
	t_tetriminos	tetriminos[MAX_TETRI];
	int				nbdieze;

	nb_tetriminos = 0;
	fd = 0;
	nbdieze = 0;
	if (argc != 2)
	{
		ft_putendl("Usage : ./fillit fichier");
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) > 0)
	{
		if (fillit(fd, tetriminos, &nb_tetriminos, nbdieze))
		{
			if(valid_tetriminos(nb_tetriminos, tetriminos))
				ft_putendl("Map solution");
			else
				ft_putendl("Error");
		}
		else
			ft_putendl("Error");
	}
	write(1, "\n", 1);
	return (0);
}
