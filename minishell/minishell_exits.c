/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:00:29 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 14:47:03 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	my_exit(t_col *col, t_cmd command)
{
	int i;

	i = 1;
	if (command.arg[i] == NULL)
	{
		cleaner(col);
		exit(g_error);
	}
	if (command.arg[i] != NULL)
		check_exit_arg1(command.arg, col);
}

void	check_exit_arg1(char **arg, t_col *col)
{
	int j;
	int i;
	int flag_minus;

	flag_minus = 0;
	i = 1;
	j = 0;
	while (arg[i])
	{
		if (arg[i][j] == '-' || arg[i][j] == '+')
		{
			if (arg[i][j] == '-')
				flag_minus = 1;
			j++;
		}
		check_exit_arg2(arg, col, j);
		if (arg[++i] != NULL)
		{
			write(1, "exit: too many arguments\n", 25);
			g_error = 1;
			return ;
		}
	}
	cleaner(col);
	dev_mod(arg[1]);
}

void	check_exit_arg2(char **arg, t_col *col, int j)
{
	while (arg[1][j])
	{
		if (ft_isdigit(arg[1][j]) == 0)
		{
			write(1, "exit: ", 6);
			write(1, arg[1], ft_strlen(arg[1]));
			write(1, ": numeric argument required\n", 28);
			g_error = 255;
			cleaner(col);
			exit(255);
		}
		j++;
	}
}

void	dev_mod(char *arg)
{
	int i;
	int iarg;

	i = 0;
	iarg = ft_atoi(arg);
	if (iarg >= 0 && iarg <= 255)
	{
		g_error = iarg;
		exit(iarg);
	}
	while (iarg >= 256)
		iarg = iarg % 256;
	g_error = iarg;
	exit(iarg);
}

void	cleaner(t_col *col)
{
	if (col->actual_d != NULL)
		free(col->actual_d);
	if (col->currend_d != NULL)
		free(col->currend_d);
	if (col->envval != NULL)
		free(col->envval);
	if (col->envvar != NULL)
		free(col->envvar);
	if (col->old_d != NULL)
		free(col->old_d);
	freesh(col->env);
	freesh(col->exp);
}
