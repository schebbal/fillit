/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/22 12:00:04 by schebbal     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 16:31:18 by schebbal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*strjoindel(char *s1, char *s2)
{
	char	*dst;

	if (!(dst = ft_strnew(ft_strlen(s2) + ft_strlen(s1))))
		return (NULL);
	ft_strcpy(dst, s1);
	ft_strcpy(dst + ft_strlen(s1), s2);
	ft_strdel(&s1);
	return (dst);
}

t_file		*ft_lstnew_or_lstadd(t_file **begin, int fd)
{
	t_file	*file;

	file = *begin;
	while (file)
	{
		if (file->fd == fd)
			return (file);
		else
			file = file->next;
	}
	if (!(file = (t_file *)ft_memalloc(sizeof(t_file))))
		return (NULL);
	file->fd = fd;
	file->content = NULL;
	file->next = *begin;
	return (*begin = file);
}

static int	ft_line_or_eof(t_file *file, char **line)
{
	int		size;
	char	*tmp;

	size = 0;
	while ((file->content[size] != '\n') &&
			(file->content[size] != '\0'))
		size++;
	if (file->content[size] == '\n')
	{
		tmp = file->content;
		*line = ft_strsub(tmp, 0, size);
		file->content = ft_strdup(tmp + size + 1);
		ft_strdel(&tmp);
	}
	else if (file->content[size] == '\0')
	{
		*line = ft_strdup(file->content);
		ft_strdel(&file->content);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_file	*file = NULL;
	t_file			*tmp;
	char			buf[BUFF_SIZE + 1];
	int				ret;

	ft_bzero(buf, BUFF_SIZE + 1);
	if (fd < 0 || !line || read(fd, buf, 0) == -1 ||
			(tmp = ft_lstnew_or_lstadd(&file, fd)) == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (tmp->content == NULL)
			tmp->content = ft_strnew(ret);
		if (!(tmp->content = strjoindel(tmp->content, buf)))
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	ft_strclr(buf);
	if (ret == 0 && (tmp->content == NULL ||
				tmp->content[0] == '\0'))
		return (0);
	return (ft_line_or_eof(tmp, line));
}
