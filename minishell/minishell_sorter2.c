/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_sorter2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:06:25 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 13:16:22 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sorter_env(t_cmd command, t_col *col)
{
	int oldstdout;

	if (command.fd[0] != 1)
	{
		oldstdout = dup(1);
		dup2(command.fd[0], 1);
		close(command.fd[0]);
		myenv(col);
		dup2(oldstdout, 1);
		close(oldstdout);
		close(command.fd[0]);
	}
	else
		myenv(col);
}

void	sorter_unset(t_cmd command, t_col *col)
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
			my_unset(command.arg[c], col);
			dup2(oldstdout, 1);
			close(oldstdout);
			close(command.fd[0]);
		}
		else
			my_unset(command.arg[c], col);
		c++;
	}
}
