/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:59:28 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 16:11:24 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		prev_fail(t_col *col, t_cmd command)
{
	struct stat	sb;
	char		**paths;
	int			i;

	i = 0;
	paths = NULL;
	if (ft_strncmpmy(command.name, "export") == 0)
		return (1);
	if (ft_strncmpmy(command.name, "unset") == 0)
		return (0);
	if (mypath(col) != NULL && ft_strchr(command.name, '/') == 0)
	{
		paths = path_redact(col, command.name);
		if (prev_exec(paths) == 1)
		{
			freesh(paths);
			return (1);
		}
		freesh(paths);
	}
	else if (stat(command.name, &sb) == 0 && sb.st_mode & S_IXUSR &&
	sb.st_mode & 0100000)
		return (1);
	return (0);
}

void	exec_cmd(t_col *col, t_cmd command, char **paths)
{
	struct stat	sb;
	int			i;

	i = 0;
	while (paths[i])
	{
		if (stat(paths[i], &sb) == 0 && sb.st_mode & S_IXUSR)
			execve(paths[i], command.arg, col->env);
		i++;
	}
}

void	exec_found_cmd(t_col *col, t_cmd command)
{
	struct stat	sb;
	char		**paths;
	int			i;

	i = 0;
	paths = NULL;
	if (mypath(col) != NULL && ft_strchr(command.name, '/') == 0)
	{
		paths = path_redact(col, command.name);
		exec_cmd(col, command, paths);
		freesh(paths);
	}
	else if (stat(command.name, &sb) == 0 && sb.st_mode & S_IXUSR &&
	sb.st_mode & 0100000)
		execve(command.name, command.arg, col->env);
	else
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(command.name, 1);
		write(1, ": ", 2);
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
}

void	export2(t_cmd command, t_col *col)
{
	if (command.arg[1] == NULL)
		show_export(col);
}
