/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdeclerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:18:34 by fdeclerc          #+#    #+#             */
/*   Updated: 2017/01/07 16:34:31 by fdeclerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_read_file(const int fd, char *str)
{
	int			rd;
	char		buff[BUFF_SIZE + 1];
	char		*tmp;

	rd = 0;
	while (!(ft_strchr(str, '\n')) && (rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = '\0';
		tmp = str;
		if (!(str = ft_strjoin(tmp, buff)))
			return (NULL);
		free(tmp);
	}
	if (rd == -1)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	return (str);
}

static int		ft_new_line(char *buff, char **line)
{
	int			i;
	char		*tmp;

	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	*line = ft_strsub(buff, 0, i);
	tmp = ft_strnew(sizeof(tmp) * (ft_strlen(buff)));
	if (tmp == NULL)
		return (-1);
	tmp = ft_strcpy(tmp, &buff[i + 1]);
	ft_strclr(buff);
	buff = ft_strcpy(buff, tmp);
	free(tmp);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*buff[SIZE_FD];

	if (BUFF_SIZE <= 0 || fd < 0 || fd > 2147483647 || line == NULL
			|| BUFF_SIZE >= 10000000)
		return (-1);
	if (!buff[fd] && (buff[fd] = ft_strnew(sizeof(buff[fd]) * 2)) == NULL)
		return (-1);
	if ((buff[fd] = ft_read_file(fd, buff[fd])) == NULL)
		return (-1);
	if (buff[fd][0] == '\0')
	{
		*line = NULL;
		return (0);
	}
	if (ft_new_line(buff[fd], line) < 0)
		return (-1);
	return (1);
}
