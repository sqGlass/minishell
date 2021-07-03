/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:59:49 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/09 00:21:13 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			rfdf_count(char **arg, t_cmd *cmd, int z)
{
	int	i;

	i = 0;
	cmd[z].fd[0] = 1;
	cmd[z].rd[0] = 0;
	while (arg[i])
		i++;
	return (i);
}

int			is_redir(char **arg, int i)
{
	if (ft_strncmp(arg[i], ">", 2) == 0)
		return (1);
	else if (ft_strncmp(arg[i], ">>", 3) == 0)
		return (1);
	else if (ft_strncmp(arg[i], ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(arg[i], ">", 1) == 0)
		return (1);
	else if (ft_strncmp(arg[i], "<", 2) == 0)
		return (1);
	else if (ft_strncmp(arg[i], "<", 1) == 0)
		return (1);
	return (0);
}

int			open_close(char **arg, t_cmd *cmd, int z, int i)
{
	if (ft_strncmp(arg[i], ">", 2) == 0)
		i = open_file(arg, cmd[z].fd, i, 1);
	else if (ft_strncmp(arg[i], ">>", 3) == 0)
		i = open_file(arg, cmd[z].fd, i, 3);
	else if (ft_strncmp(arg[i], ">>", 2) == 0)
		i = open_file(arg, cmd[z].fd, i, 4);
	else if (ft_strncmp(arg[i], ">", 1) == 0)
		i = open_file(arg, cmd[z].fd, i, 2);
	else if (ft_strncmp(arg[i], "<", 2) == 0)
		i = open_read_file(arg, cmd[z].rd, i, 1);
	else if (ft_strncmp(arg[i], "<", 1) == 0)
		i = open_read_file(arg, cmd[z].rd, i, 2);
	return (i);
}

int			is_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == 0)
		return (0);
	return (1);
}
