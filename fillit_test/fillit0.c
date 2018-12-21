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

#include <stdio.h>
#include <stdlib.h>
#include "fillit.h"
#include <sys/wait.h>

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
		t_tetriminos tetriminos[MAX_TETRI], int *nb_blocs)
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
				tetriminos[i].x[*nb_blocs] = vcar;
				tetriminos[i].y[*nb_blocs] = iy;
				tetriminos[i].car = i + 'A';
				tetriminos[i].pos = i;
				tetriminos[i].xmin = 3;
				tetriminos[i].ymin = 3;
				(*nb_blocs)++;
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
		//res++;
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

int		remove_tetri(t_board *board, char ch, int y, int x)
{
	int	i;

	i = 0;
	printf("ch=%c\n", ch);
	while (i < 3 && board->grid[y])
	{
		x = 0;
		while (board->grid[y][x])
		{
			if (i > 3)
				return (1);
			if (board->grid[y][x] == ch)
			{
				board->grid[y][x] = '.';
				i++;
			}
			x++;
		}
		y++;
	}
	return (0);
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
		//ft_putstr(board.grid[j]);
		ft_putchar('\n');
		j++;
	}
}

int     valid_pos(t_board *board, t_tetriminos tetri)
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
			//printf("2-OK, i=%d, yi=%d, xi=%d, y=%d, x=%d, size=%d, car=%c\n",i,tetri.y[i],tetri.x[i],board->y,board->x, board->size,tetri.car);
			if((board->x + tetri.x[i] >= board->size) ||
				(board->y + tetri.y[i] >= board->size) ||
				(board->grid[board->y + tetri.y[i]][board->x + tetri.x[i]] != '.'))
				return (0);
			i++;
		}
	}
	printf("4-OK, i=%d, yi=%d, xi=%d, y=%d, x=%d, size=%d\n",i,tetri.y[i],tetri.x[i],board->y,board->x, board->size);
	return (1);
}

int     find_pos_to_board(t_board *board, t_tetriminos tetri, int x, int y)
{
	y = 0;
	while (y < board->size)
	{
		x = 0;	
		while (x < board->size)
		{
			board->x = x;
			board->y = y;
			//printf(">>>>>>>>>>>>>1-OK, y=%d, x=%d, size=%d, car=%c\n", board->y,board->x, board->size,tetri.car);
			if (valid_pos(board, tetri) == 1)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int		put_tetri_to_pos(t_board *board, t_tetriminos tetri)
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
			board->grid[board->y + tetri.y[i]][board->x + tetri.x[i]] = tetri.car;
			//printf(">>>>>>01blocs No =%d, y+yi=%d, x+xi=%d\n", i, board->y + tetri.y[i], board->x + tetri.x[i]);
			i++;
		}
	}
	return (0);
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
	
	printf("ok5\n");
	ft_memdel((void **)grid);
	
	printf("ok6\n");
}

int     put_tetriminos_to_board(t_board board, int nb_tetri, t_tetriminos tetri[nb_tetri], int x, int y, int *j)
{
	int		vld;

	vld = 0;
	printf(">>>>>>       tetriminos No =%d, nbtetri=%d, x=%d, y=%d, size=%d\n", *j, nb_tetri, x, y, board.size);
	if (vld || *j >= nb_tetri || !board.grid || x >= board.size || y >= board.size)
		return (1);
	while (y < board.size)
	{	
		while (x < board.size)
		{
			printf(">>>>>>tetriminos No =%d, nb tetri=%d, x=%d, y=%d, car=%c\n", *j, nb_tetri, x, y, tetri[*j].car);
			if (find_pos_to_board(&board, tetri[*j], x, y) == 1)
			{	
				put_tetri_to_pos(&board, tetri[*j]);
				(*j)++;
				if (put_tetriminos_to_board(board, nb_tetri, tetri, x, y, j) == 1)
					return (1);
				else
					vld = remove_tetri(&board, tetri[*j - 1].car, x, y);
			}
			x++;
		}
		y++;
		x = 0;
	}
	printf("ok1\n");
	return (0);
}

void	get_grid(int nb_tetriminos, t_tetriminos tetriminos[nb_tetriminos], int board_size)
{
	t_board		board;
	int			vld;
	int			j;

	if(!(board.grid = ft_strnew_board(board_size)))
		return ;
	board.size = board_size;
	j = 0;
	vld = 0;
	init_board(board);
	while (put_tetriminos_to_board(board, nb_tetriminos, tetriminos, 0, 0, &j) == 0)
	{
		printf("ok2\n");
		delete_grid(board.grid);
		printf("ok3\n");
		board_size++;
		if(!(board.grid = ft_strnew_board(board_size)))
			return ;
		board.size = board_size;
		init_board(board);
		j = 0;
		printf("ok4\n");
	}
	print_board(board);
	//delete_grid(board.grid);
	return ;
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
	get_grid(nb_tetriminos, tetriminos, board_size);
	return (1);
}

int		fillit(int fd, t_tetriminos tetriminos[MAX_TETRI], int *nbtetri, int nb_blocs)
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
			nb_blocs = 0;
			(*nbtetri)++;
		}
		if (((nbline + 1) % 5 == 0 && nbloc != 4) || *nbtetri > MAX_TETRI)
			vld = 0;
		if (vld)
			load_tetriminos(line, nbline, tetriminos, &nb_blocs);
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
	int				nb_blocs;

	nb_tetriminos = 0;
	fd = 0;
	nb_blocs = 0;
	if (argc != 2)
	{
		ft_putendl("Usage : ./fillit input_fichier");
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) > 0)
	{
		if (!(fillit(fd, tetriminos, &nb_tetriminos, nb_blocs)))
		{
			ft_putendl("Error1");
			return (0);
		}
		if(!(valid_tetriminos(nb_tetriminos, tetriminos)))
		{
			ft_putendl("Error2");
			return (0);
		}
		ft_putendl("Map solution");
	}
	write(1, "\n", 1);
	return (0);
}
