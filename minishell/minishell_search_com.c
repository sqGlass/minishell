/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_search_com.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:56:43 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 18:08:40 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	search_command(t_col *col, t_cmd command)
{
	struct stat sb;

	if (mypath(col) != NULL && ft_strchr(command.name, '/') == 0)
		search_command22(col, command);
	else if (stat(command.name, &sb) == 0 && sb.st_mode &
	S_IXUSR && sb.st_mode & 0100000)
	{
		search_command33(col, command);
		return ;
	}
	else
		search_command44(command);
}

void	search_command22(t_col *col, t_cmd command)
{
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	paths = ft_split(mypath(col), ':');
	while (paths[i])
	{
		temp = ft_strdup(paths[i]);
		free(paths[i]);
		paths[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		temp = ft_strdup(paths[i]);
		free(paths[i]);
		paths[i] = ft_strjoin(temp, command.name);
		free(temp);
		i++;
	}
	try_exec(col, command, paths);
	freesh(paths);
}

void	search_command33(t_col *col, t_cmd command)
{
	int pid;
	int status;

	status = 0;
	if (ft_strnstr(command.name, "minishell", ft_strlen(command.name)) != 0)
	{
		g_quit = 2;
		g_sig = 2;
	}
	pid = fork();
	if (pid != 0)
		wait(&status);
	else
	{
		dup2(command.fd[0], 1);
		dup2(command.rd[0], 0);
		if ((execve(command.name, command.arg, col->env)) == -1)
			g_error = 1;
	}
	g_error = status / 256;
}

void	search_command44(t_cmd command)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(command.name, 1);
	write(1, ": ", 2);
	ft_putstr_fd(strerror(errno), 1);
	write(1, "\n", 1);
	if (errno == 2)
		g_error = 127;
	else
		g_error = 1;
}
