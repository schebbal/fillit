/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fillit.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 10:40:21 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 17:13:23 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include "get_next_line.h"

# define MAX_TETRI 26

typedef	struct		s_tetriminos
{
	char			car;
	int				pos;
	int				x[4];
	int				y[4];
	int				xmin;
	int				ymin;
	int				l;
	int				h;
}					t_tetriminos;

typedef struct		s_board
{
	char			**grid;
	int				x;
	int				y;
	int				size;
}					t_board;

int					fillit(int fd, t_tetriminos *tetriminos, int *n, int i);
int					valid_tetriminos(int nb_tetriminos, t_tetriminos *tetri);
void				get_grid(int nb_tetriminos, t_tetriminos *tetri,
int board_size);
int					solve_board(t_board board, int nb_tetri,
t_tetriminos *tetri, int *d);

#endif
