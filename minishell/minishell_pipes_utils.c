/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:00:30 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 15:11:29 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pfd_free(int count, int **pfd)
{
	int	i;

	i = 0;
	while (i < count)
		free(pfd[i++]);
	free(pfd);
}

int		is_my_cmd(char *name)
{
	if (ft_strncmpmy(name, "export") == 0)
		return (1);
	else if (ft_strncmpmy(name, "pwd") == 0)
		return (1);
	else if (ft_strncmpmy(name, "echo") == 0)
		return (1);
	else if (ft_strncmpmy(name, "cd") == 0)
		return (1);
	return (0);
}

int		**create_pipefd(int count)
{
	int		i;
	int		**pfd;

	i = 0;
	if ((pfd = ft_calloc(count, sizeof(int *))) == 0)
		exit(0);
	while (i < count)
		pfd[i++] = ft_calloc(3, sizeof(int));
	i = 0;
	while (i < count && count != 1)
		pipe(pfd[i++]);
	return (pfd);
}

int		dup_func(int **pfd, int i, int all_count, t_cmd cmd)
{
	if (i == 0)
	{
		close(pfd[i][0]);
		dup2(pfd[i][1], 1);
		close(pfd[i][1]);
	}
	else if (i < all_count - 1)
	{
		close(pfd[i - 1][1]);
		dup2(pfd[i - 1][0], 0);
		close(pfd[i][0]);
		dup2(pfd[i][1], 1);
	}
	else
	{
		close(pfd[i - 1][1]);
		dup2(pfd[i - 1][0], 0);
		close(pfd[i - 1][1]);
	}
	if (cmd.rd[0] != 0)
		dup2(cmd.rd[0], 0);
	if (cmd.fd[0] != 1)
		dup2(cmd.fd[0], 1);
	return (0);
}

void	fail_exit_status_ret(t_col *col, t_cmd command)
{
	struct stat sb;

	if (mypath(col) != NULL && ft_strchr(command.name, '/') == 0)
		exit(127);
	else if (stat(command.name, &sb) == 0 && sb.st_mode & S_IXUSR
		&& sb.st_mode & 0100000)
		write(1, "", 0);
	else
	{
		if (errno == 2)
			exit(127);
		else
			exit(1);
	}
}
