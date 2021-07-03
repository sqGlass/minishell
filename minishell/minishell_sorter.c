/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_sorter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:54:51 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 13:33:07 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sorter1(t_cmd command, t_col *col)
{
	col->envval = NULL;
	col->envvar = NULL;
	if (ft_strncmpmy(command.name, "echo") == 0)
		sorter_echo(command);
	else if (ft_strncmpmy(command.name, "cd") == 0)
		sorter_cd(command, col);
	else if (ft_strncmpmy(command.name, "pwd") == 0)
		sorter_pwd(command);
	else if (ft_strncmpmy(command.name, "export") == 0)
		sorter_export(command, col);
	else if (ft_strncmpmy(command.name, "env") == 0)
		sorter_env(command, col);
	else if (ft_strncmpmy(command.name, "unset") == 0)
		sorter_unset(command, col);
	else if (ft_strncmpmy(command.name, "exit") == 0)
		my_exit(col, command);
	else
		search_command(col, command);
}

void	sorter_echo(t_cmd command)
{
	int oldstdout;

	if (command.fd[0] != 1)
	{
		oldstdout = dup(1);
		dup2(command.fd[0], 1);
		close(command.fd[0]);
		myecho(command);
		dup2(oldstdout, 1);
		close(oldstdout);
		close(command.fd[0]);
	}
	else
		myecho(command);
}

void	sorter_cd(t_cmd command, t_col *col)
{
	int oldstdout;

	if (command.fd[0] != 1)
	{
		oldstdout = dup(1);
		dup2(command.fd[0], 1);
		close(command.fd[0]);
		mycd(command, col);
		dup2(oldstdout, 1);
		close(oldstdout);
		close(command.fd[0]);
	}
	else
		mycd(command, col);
}

void	sorter_pwd(t_cmd command)
{
	int oldstdout;

	if (command.fd[0] != 1)
	{
		oldstdout = dup(1);
		dup2(command.fd[0], 1);
		close(command.fd[0]);
		mypwd();
		dup2(oldstdout, 1);
		close(oldstdout);
		close(command.fd[0]);
	}
	else
		mypwd();
}

void	sorter_export(t_cmd command, t_col *col)
{
	int c;
	int oldstdout;

	c = 1;
	while (command.arg[c])
	{
		if (command.fd[0] != 1)
		{
			oldstdout = dup(1);
			dup2(command.fd[0], 1);
			close(command.fd[0]);
			myexport(command, col, c);
			dup2(oldstdout, 1);
			close(oldstdout);
			close(command.fd[0]);
		}
		else
			myexport(command, col, c);
		c++;
	}
	if (command.arg[1] == NULL)
	{
		show_export(col);
		return ;
	}
}
