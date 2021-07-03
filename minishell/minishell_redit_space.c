/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redit_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:06:48 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 12:19:49 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ret_copy(char **red, char *line, int i, int j)
{
	while (line[++i])
	{
		if (line[i] == '>' && line[i + 1] == '>')
		{
			red[0][j++] = ' ';
			red[0][j++] = '>';
			red[0][j++] = '>';
			i++;
		}
		else if (line[i] == '>' && line[i - 1] != ' ')
		{
			red[0][j++] = ' ';
			red[0][j++] = '>';
		}
		else if (line[i] == '<' && line[i - 1] != ' ')
		{
			red[0][j++] = ' ';
			red[0][j++] = '<';
		}
		else
			red[0][j++] = line[i];
	}
}

static int	red_count(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '>' && line[i + 1] != ' ')
			i++;
		i++;
	}
	return (i);
}

char		*redit_space(char *line)
{
	int		i;
	char	*red;
	int		j;

	i = -1;
	j = 0;
	if ((red = ft_calloc((red_count(line) + 1), sizeof(char))) == 0)
		return (0);
	ret_copy(&red, line, i, j);
	free(line);
	return (red);
}
