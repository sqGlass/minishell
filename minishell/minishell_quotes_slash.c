/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes_slash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:04:43 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 17:34:17 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			quotes(char *line)
{
	int		i;
	int		j;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 && line[i - 1] != 92)
		{
			if ((j = inside_quotes(&line[i], 34, -5)) == -1)
				return (-1);
			i += j;
			line[i++] = -5;
		}
		else if (line[i] == 39 && line[i - 1] != 92)
		{
			if ((j = inside_quotes2(&line[i], 39, -6)) == -1)
				return (-1);
			i += j;
			line[i++] = -6;
		}
		else
			i++;
	}
	return (0);
}

static void	line_red(char *line)
{
	if (line[0] == ' ')
		line[0] = -1;
	if (line[0] == '|')
		line[0] = -2;
	if (line[0] == ';')
		line[0] = -3;
	if (line[0] == '>')
		line[0] = -8;
	if (line[0] == '<')
		line[0] = -9;
}

int			inside_quotes(char *line, int c, int z)
{
	int		i;

	i = 0;
	line[i] = z;
	while (line[++i] != c)
	{
		if ((line[i] == 92 && line[i + 1] == '$') ||
		(line[i] == 92 && line[i + 1] == '"'))
			line[i++] = -4;
		else if (line[i] == 92 && line[i + 1] == 92)
			line[i++] = -7;
		else if (line[i] == 92)
			line[i] = -7;
		line_red(&line[i]);
		if (line[i] == '\0')
		{
			ft_putstr_fd("Multiline command.\n", 1);
			return (-1);
		}
	}
	return (i);
}

int			inside_quotes2(char *line, int c, int z)
{
	int		i;

	i = 0;
	line[i++] = z;
	while (line[i] != c)
	{
		if (line[i] == 92)
			line[i] = -7;
		line_red(&line[i]);
		if (line[i] == '$')
			line[i] = -10;
		if (line[i] == '\0')
		{
			ft_putstr_fd("Multiline command.\n", 1);
			return (-1);
		}
		i++;
	}
	return (i);
}

int			back_slash(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 92)
		{
			line[i++] = -4;
			line_red(&line[i]);
			if (line[i] == '\0')
			{
				ft_putstr_fd("Multiline command.\n", 1);
				return (-1);
			}
		}
	}
	return (0);
}
