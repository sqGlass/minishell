/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:06:13 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/07 15:25:53 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin2(char *s1, char s2)
{
	size_t	i;
	size_t	j;
	char	*fin;

	i = 0;
	j = 0;
	if ((fin = ft_calloc(ft_strlen(s1) + 2, sizeof(char))) == 0)
		return (NULL);
	while (s1[i] != 0)
	{
		fin[i] = s1[i];
		i++;
	}
	fin[i++] = s2;
	fin[i] = '\0';
	free(s1);
	return (fin);
}

int		get_next_line(int fd, char **line)
{
	char	buf;
	int		rd;

	*line = ft_calloc(1, sizeof(char));
	while ((rd = read(fd, &buf, 1)) != -1)
	{
		if (rd == 0)
		{
			write(1, "  \b\b", 4);
			if (line[0][0] == '\0')
			{
				write(1, "exit\n", 5);
				*line = ft_strdup("exit");
				return (1);
			}
		}
		else
		{
			if (buf == '\n')
				break ;
			*line = ft_strjoin2(*line, buf);
		}
	}
	return (rd);
}
