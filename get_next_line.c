/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:27:03 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/28 10:31:30 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char	*strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	ft_strdel((char **)&s1);
	return (new);
}

int		chr(char **s, char **line)
{
	char *tmp;

	if ((tmp = ft_strchr(*s, '\n')) != NULL)
	{
		*tmp = '\0';
		*line = ft_strdup(*s);
		tmp = ft_strdup(&tmp[1]);
		ft_strdel(s);
		*s = tmp;
		return (1);
	}
	return (0);
}

void	move_point(char **s)
{
	while (**s != '\0')
		(*s)++;
}

int		get_next_line(const int fd, char **line)
{
	char				buff[BUFF_SIZE + 1];
	static char			*s;
	int					r;

	if (fd < 0)
		return (-1);
	if (s == NULL)
		if (!(s = (char *)malloc(sizeof(char) * 1)))
			return (-1);
	if (chr(&s, line) == 1)
		return (1);
	if ((r = read(fd, buff, BUFF_SIZE)))
	{
		if (r < 0)
			return (-1);
		buff[r] = '\0';
		if (!(s = strjoin(s, buff)))
			return (-1);
		return (get_next_line(fd, line));
	}
	*line = s;
	if (*s == '\0')
		return (0);
	move_point(&s);
	return (1);
}
