/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_roll_pipes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:38:11 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/09 00:28:14 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	fail_exec(t_col *col, t_all all, int i, int **pfd)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		close(pfd[i][1]);
	else
	{
		dup_func(pfd, i, all.cmd_count, all.cmd[i]);
		fail_exit_status_ret(col, all.cmd[i]);
	}
	return (pid);
}

static pid_t	out_own_cmd(t_col *col, t_all all, int i, int **pfd)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		close(pfd[i][1]);
	else
	{
		dup_func(pfd, i, all.cmd_count, all.cmd[i]);
		if (ft_strncmpmy(all.cmd[i].name, "export") == 0)
			export2(all.cmd[i], col);
		else if (ft_strncmpmy(all.cmd[i].name, "pwd") == 0)
			mypwd();
		else if (ft_strncmpmy(all.cmd[i].name, "echo") == 0)
			myecho(all.cmd[i]);
		else if (ft_strncmpmy(all.cmd[i].name, "cd") == 0)
		{
			mycd(all.cmd[i], col);
			if (g_error == 1)
				exit(1);
			else
				exit(0);
		}
		exit(0);
	}
	return (pid);
}

static pid_t	out_cmd(t_col *col, t_all all, int i, int **pfd)
{
	pid_t	pid;

	pid = 0;
	if (i != 0 && prev_fail(col, all.cmd[i - 1]) == 0
	&& (ft_strncmpmy(all.cmd[i].name, "cat") == 0 || ft_strncmpmy(all.cmd[i].
	name, "grep") == 0 || ft_strncmpmy(all.cmd[i].name, "/bin/cat") == 0 ||
	ft_strncmpmy(all.cmd[i].name, "/bin/grep") == 0))
		write(1, "", 0);
	else if ((all.cmd[i - 1].fd[0] == -1 || all.cmd[i - 1].rd[0] == -1) &&
	(ft_strncmpmy(all.cmd[i].name, "cat") == 0 || ft_strncmpmy(all.cmd[i].name,
	"grep") == 0 || ft_strncmpmy(all.cmd[i].name, "/bin/cat") == 0 ||
	ft_strncmpmy(all.cmd[i].name, "/bin/grep") == 0))
		write(1, "", 0);
	else
	{
		if ((pid = fork()) != 0)
			close(pfd[i][1]);
		else
		{
			dup_func(pfd, i, all.cmd_count, all.cmd[i]);
			exec_found_cmd(col, all.cmd[i]);
		}
	}
	return (pid);
}

static pid_t	executor(t_col *col, t_all all, int i, int **pfd)
{
	pid_t	pid;

	if (is_my_cmd(all.cmd[i].name) == 1)
		pid = out_own_cmd(col, all, i, pfd);
	else if (cmd_exist_check(col, all.cmd[i]) != 0)
		pid = out_cmd(col, all, i, pfd);
	else
		pid = fail_exec(col, all, i, pfd);
	return (pid);
}

void			roll_commands(t_all all, t_col *col)
{
	int		i;
	int		**pfd;
	pid_t	pid;
	int		error_status;

	pid = 0;
	error_status = 0;
	i = -1;
	pfd = create_pipefd(all.cmd_count);
	while (++i < all.cmd_count && all.cmd[i].name != 0)
	{
		if (all.cmd[i].fd[0] != -1 && all.cmd[i].rd[0] != -1)
			pid = executor(col, all, i, pfd);
		else if (i + 1 < all.cmd_count && (ft_strncmpmy(all.cmd[i + 1].name,
	"cat") == 0 || ft_strncmpmy(all.cmd[i + 1].name, "grep") == 0 ||
	ft_strncmpmy(all.cmd[i + 1].name, "/bin/cat") == 0 ||
	ft_strncmpmy(all.cmd[i + 1].name, "/bin/grep") == 0))
			all.cmd[i + 1].fd[0] = -1;
	}
	waitpid(pid, &error_status, 0);
	g_error = error_status / 256;
	i = -1;
	while (++i < all.cmd_count)
		wait(0);
	pfd_free(all.cmd_count, pfd);
}
