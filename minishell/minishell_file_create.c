/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_file_create.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:03:27 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 17:39:23 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_fd_msg(char *arg, int skip_flag)
{
	ft_putstr_fd("minishell: ", 1);
	if (skip_flag == 2)
		ft_putstr_fd(&arg[1], 1);
	else if (skip_flag == 4)
		ft_putstr_fd(&arg[2], 1);
	else
		ft_putstr_fd(arg, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	write(1, "\n", 1);
	errno = 0;
	g_error = 1;
}

char		*arrow_content(char **arg)
{
	int		f;
	int		g;
	char	*str;

	f = 0;
	g = 0;
	if ((str = ft_calloc(ft_strlen(arg[0]) + 1, sizeof(char))) == 0)
		return (0);
	while (arg[0][f])
	{
		if (arg[0][f] == -8)
			str[g++] = '>';
		else if (arg[0][f] == -9)
			str[g++] = '<';
		else
			str[g++] = arg[0][f];
		f++;
	}
	free(arg[0]);
	return (str);
}

int			open_read_file(char **arg, int *rd, int i, int flag)
{
	if (flag == 1)
		free(arg[i++]);
	if (*rd == -1)
	{
		free(arg[i++]);
		return (i);
	}
	if (*rd != 0)
		close(*rd);
	arg[i] = arrow_content(&arg[i]);
	if (flag == 1)
		*rd = open(arg[i], O_RDONLY);
	else if (flag == 2)
		*rd = open(&arg[i][1], O_RDONLY);
	if (*rd == -1)
		error_fd_msg(arg[i], flag);
	free(arg[i++]);
	return (i);
}

int			open_file(char **arg, int *fd, int i, int flag)
{
	if (flag == 1 || flag == 3)
		free(arg[i++]);
	if (*fd == -1)
	{
		free(arg[i++]);
		return (i);
	}
	if (*fd != 1)
		close(*fd);
	arg[i] = arrow_content(&arg[i]);
	if (flag == 1)
		*fd = open(arg[i], O_CREAT | O_TRUNC | O_RDWR, 0666);
	else if (flag == 2)
		*fd = open(&arg[i][1], O_CREAT | O_TRUNC | O_RDWR, 0666);
	else if (flag == 4)
		*fd = open(&arg[i][2], O_CREAT | O_APPEND | O_RDWR, 0666);
	else
		*fd = open(arg[i], O_CREAT | O_APPEND | O_RDWR, 0666);
	if (*fd == -1)
		error_fd_msg(arg[i], flag);
	free(arg[i++]);
	return (i);
}

char		**file_check(char **arg, t_cmd *cmd, int z)
{
	int		i;
	int		j;
	char	**red;

	i = 0;
	j = 0;
	if ((red = ft_calloc(rfdf_count(arg, cmd, z) + 1, sizeof(char *))) == 0)
		return (0);
	while (arg[i])
	{
		if (is_redir(arg, i) == 1)
			i = open_close(arg, cmd, z, i);
		else
		{
			red[j++] = ft_strdup(arg[i]);
			free(arg[i++]);
		}
	}
	free(arg[i]);
	free(arg);
	return (red);
}
