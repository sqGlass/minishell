/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:48:20 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 15:00:50 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	myecho(t_cmd command)
{
	int i;
	int j;
	int	flag;

	i = 1;
	j = 1;
	flag = 0;
	if (command.arg[i] != NULL && ft_strncmp(command.arg[i],
		"-n", ft_strlen("-n")) == 0)
		while (command.arg[i] != NULL && ft_strncmp(command.arg[i],
			"-n", ft_strlen("-n")) == 0)
		{
			j = 1;
			while (command.arg[i][j] == 'n')
				j++;
			if (command.arg[i][j] != 'n' && command.arg[i][j] != 0)
				break ;
			else
			{
				i++;
				flag = 1;
			}
		}
	myecho2(command, i, flag);
}

void	myecho2(t_cmd command, int i, int flag)
{
	while (command.arg[i] != NULL)
	{
		if (command.arg[i][0] == 0)
		{
			i++;
			continue ;
		}
		write(1, command.arg[i], ft_strlen(command.arg[i]));
		if (command.arg[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	g_error = 0;
	if (flag != 1)
		write(1, "\n", 1);
}
