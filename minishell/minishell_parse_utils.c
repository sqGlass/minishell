/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:00:59 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 17:21:47 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freesher(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = 0;
	}
	free(str);
	str = 0;
}

int		split_counter(char **buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		i++;
	return (i);
}

int		wd_count(char *line, char c)
{
	int	i;
	int	semi_counter;

	i = -1;
	semi_counter = 1;
	while (line[++i])
		if (line[i] == c && line[i + 1] != 0)
			semi_counter++;
	return (semi_counter);
}

int		big_free(t_all *all, int all_count)
{
	int	i;
	int	j;
	int	v;

	i = -1;
	while (++i < all_count)
	{
		j = -1;
		while (++j < all[i].cmd_count)
		{
			v = -1;
			while (all[i].cmd[j].arg[++v])
				free(all[i].cmd[j].arg[v]);
			free(all[i].cmd[j].arg);
			free(all[i].cmd[j].name);
		}
		free(all[i].cmd);
	}
	free(all);
	return (0);
}

int		error_exit2(void)
{
	ft_putstr_fd("Malloc error. Program will be stopeed\n", 2);
	exit(0);
}
