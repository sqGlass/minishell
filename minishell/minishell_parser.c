/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:55:06 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/09 00:20:04 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_parser(t_all *all, char *pipe_split, int i, int j)
{
	int		z;

	z = -1;
	if (pipe_split == 0)
	{
		all[i].cmd[j].arg = ft_calloc(1, sizeof(char *));
		all[i].cmd[j].name = ft_calloc(1, sizeof(char *));
		return (0);
	}
	if ((all[i].cmd[j].arg = ft_split(pipe_split, ' ')) == 0)
		return (-1);
	while (all[i].cmd[j].arg[++z])
		all[i].cmd[j].arg[z] = true_content(all, i, j, z);
	z = -1;
	all[i].cmd[j].arg = file_check(all[i].cmd[j].arg, all[i].cmd, j);
	while (all[i].cmd[j].arg[++z])
		all[i].cmd[j].arg[z] = arrow_content(&all[i].cmd[j].arg[z]);
	if (all[i].cmd[j].arg[0] != 0)
		all[i].cmd[j].name = ft_strdup(all[i].cmd[j].arg[0]);
	else
		all[i].cmd[j].name = 0;
	return (0);
}

int		cmd_filler(t_all *all, int i, t_col *col, char **semi_split)
{
	char	**pipe_split;
	int		j;

	j = -1;
	all[i].cmd_count = wd_count(semi_split[i], '|');
	if ((semi_split[i] = dollar(semi_split[i], col)) == 0)
		return (error_exit2());
	if ((pipe_split = ft_split(semi_split[i], '|')) == 0)
		return (-1);
	if ((all[i].cmd = (t_cmd *)ft_calloc(sizeof(t_cmd),
		all[i].cmd_count + 1)) == 0)
		return (-1);
	while (++j < all[i].cmd_count)
	{
		if ((cmd_parser(all, pipe_split[j], i, j)) == -1)
			return (-1);
	}
	freesher(pipe_split);
	direction(all[i], col);
	return (0);
}

int		parser(char *line, t_col *col)
{
	int		i;
	t_all	*all;
	char	**semi_split;
	int		all_count;

	i = -1;
	all_count = wd_count(line, ';');
	if ((semi_split = ft_split(line, ';')) == 0)
		return (-1);
	if ((all = (t_all *)ft_calloc(sizeof(t_all), all_count + 1)) == 0)
		return (-1);
	while (++i < all_count)
		if (cmd_filler(all, i, col, semi_split) == -1)
			return (-1);
	freesher(semi_split);
	big_free(all, all_count);
	return (0);
}

int		starter(int argc, char **argv, t_col *col)
{
	char	*line;

	(void)argc;
	(void)argv;
	while ((write(1, "minishell-0.1$ ", 15) && (get_next_line(0, &line) != 0)))
	{
		if (line[0] != '\0' && token(line) != -1 && quotes(&line[0]) != -1 &&
	back_slash(&line[0]) != -1 && line_check(line) != -1 && r_c(line) != -1 &&
	is_spaces(line) != 0)
		{
			if ((line = redit_space(line)) == 0)
				return (error_exit2());
			if ((line = ft_strtrim(line, " ")) == 0)
				return (error_exit2());
			if ((line = error_parse(line)) == 0)
				return (error_exit2());
			if (parser(line, col) == -1)
				return (error_exit2());
			free(line);
		}
		else
			free(line);
	}
	return (0);
}
