/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdeclerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:48:12 by fdeclerc          #+#    #+#             */
/*   Updated: 2016/12/22 16:24:41 by fdeclerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_check_line(int fd, char *buff, char *ch[1], char **line)
{
	int			rd;
	char		*c;
	char		*tmp;

	while (!(c = ft_strchr(*ch, '\n')) &&
			(rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = '\0';
		tmp = *ch;
		*ch = ft_strjoin(tmp, buff);
		ft_strdel(&tmp);
	}
	ft_strdel(&buff);
	if (rd == -1)
		return (-1);
	if (!c && rd == 0)
	{
		if (*ch[0] == '\0')
			*line = ft_strdup("");
		return (0);
	}
	return (1);
}

static char		**ft_new_line(int fd, char *ch[1])
{
	static char *line[BUFF_SIZE + 1];

	if (ch != NULL)
		line[fd] = *ch;
	*line = line[fd];
	return (line);
}

static int		ft_end_line(char **ch, int fd, char **line)
{
	if (*ch[0] == '\0')
	{
		ft_new_line(fd, ch);
		return (0);
	}
	*line = *ch;
	ch[0] = NULL;
	ft_new_line(fd, ch);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char		**ch;
	int			back;
	char		*buff;
	char		*tmp;

	if (fd < 0 || line == NULL || (buff = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	ch = ft_new_line(fd, NULL);
	if (*ch == NULL)
		*ch = ft_strnew(1);
	if ((back = ft_check_line(fd, buff, ch, line)) == 0)
		return (ft_end_line(ch, fd, line));
	if (back == -1)
	{
		ft_new_line(fd, ch);
		return (-1);
	}
	*line = ft_strsub(*ch, 0, (ft_strchr(*ch, '\n') - *ch));
	tmp = *ch;
	*ch = ft_strdup(ft_strchr(tmp, '\n') + 1);
	ft_strdel(&tmp);
	ft_new_line(fd, ch);
	return (1);
}
