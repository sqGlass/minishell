/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:11:59 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 19:41:06 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	try_exec(t_col *col, t_cmd command, char **paths)
{
	int			i;
	int			pid;
	int			status;
	struct stat sb;

	i = -1;
	status = 0;
	while (paths[++i])
		if (stat(paths[i], &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			pid = fork();
			if (pid != 0)
				wait(&status);
			else
			{
				dup2(command.fd[0], 1);
				dup2(command.rd[0], 0);
				execve(paths[i], command.arg, col->env);
			}
			g_error = status / 256;
			return ;
		}
	try_exec_message(command);
}

void	try_exec_message(t_cmd command)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(command.name, 1);
	ft_putstr_fd(": command not found\n", 1);
	g_error = 127;
}

char	*mypath(t_col *col)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		if (ft_strncmp(col->env[i], "PATH=", 5) == 0)
		{
			if (ft_strlen(col->env[i]) > 5)
				return (&col->env[i][5]);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
