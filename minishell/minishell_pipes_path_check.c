/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipes_path_check.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:44:02 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 16:14:40 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_msg(char *name)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(name, 1);
	write(1, ": ", 2);
	ft_putstr_fd(strerror(errno), 1);
	write(1, "\n", 1);
}

int			check_exec(t_cmd command, char **paths)
{
	struct stat	sb;
	int			i;

	i = -1;
	while (paths[++i])
		if (stat(paths[i], &sb) == 0 && sb.st_mode & S_IXUSR)
			return (1);
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(command.name, 1);
	ft_putstr_fd(": command not found\n", 1);
	return (0);
}

char		**path_redact(t_col *col, char *name)
{
	char	**paths;
	int		i;
	char	*temp;

	i = -1;
	if ((paths = ft_split(mypath(col), ':')) == 0)
		exit(0);
	while (paths[++i])
	{
		temp = ft_strdup(paths[i]);
		free(paths[i]);
		paths[i] = ft_strjoin(temp, "/");
		free(temp);
	}
	i = -1;
	while (paths[++i])
	{
		temp = ft_strdup(paths[i]);
		free(paths[i]);
		paths[i] = ft_strjoin(temp, name);
		free(temp);
	}
	return (paths);
}

int			cmd_exist_check(t_col *col, t_cmd command)
{
	struct stat	sb;
	char		**paths;
	int			i;

	i = 0;
	paths = NULL;
	if (ft_strncmpmy(command.name, "unset") == 0)
		return (0);
	if (mypath(col) != NULL && ft_strchr(command.name, '/') == 0)
	{
		paths = path_redact(col, command.name);
		if (check_exec(command, paths) == 1)
		{
			freesh(paths);
			return (1);
		}
		freesh(paths);
	}
	else if (stat(command.name, &sb) == 0 && sb.st_mode & S_IXUSR &&
		sb.st_mode & 0100000)
		return (1);
	else
		error_msg(command.name);
	return (0);
}

int			prev_exec(char **paths)
{
	struct stat	sb;
	int			i;
	int			status;

	i = 0;
	status = 0;
	while (paths[i])
	{
		if (stat(paths[i], &sb) == 0 && sb.st_mode & S_IXUSR)
			return (1);
		i++;
	}
	return (0);
}
