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
	if ((!line && (nbline % 5 == 0 && line[0] != '\n')) ||
	(nbline % 5 != 0 && ft_strlen(line) != 4))
		return (0);
	while (line[vcar])
	{
		if (nbline % 5 != 0 && line[vcar] == '#')
			(*nbloc)++;
		if ((nbline % 5 == 0 && line[vcar] != '\n') ||
		(nbline % 5 != 0 && (vcar > 3 || (line[vcar] != '.' &&
						line[vcar] != '#'))))
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

int		fillit(int fd, t_tetriminos tetriminos[MAX_TETRI],
int *nbtetri, int nb_blocs)
{
	char	*line;
	int		nbline;
	int		vld;
	int		nbloc;

	nbline = 1;
	vld = 1;
	nbloc = 0;
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
	*nbtetri = ((nbline > 1) ? *nbtetri += 1 : 0);
	return (vld && (*nbtetri != 0 && ((nbline + 1) / (*nbtetri) % 5 == 0)));
}
