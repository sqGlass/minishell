/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:04:42 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 15:41:39 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mycd(t_cmd command, t_col *col)
{
	int flag;

	if (command.arg[1] == NULL || ft_strncmpmy(command.arg[1], "--") == 0)
	{
		cd_home(col);
		return ;
	}
	if (ft_strncmpmy(command.arg[1], "-") == 0)
	{
		cd_minus(col);
		return ;
	}
	flag = chdir(command.arg[1]);
	if (flag == -1)
		cd_message(command);
	else
	{
		col->flag_minus = 2;
		change_pwd(col);
		sort_exp(col);
		g_error = 0;
	}
}

void	cd_message(t_cmd command)
{
	write(1, "minishell: ", 11);
	write(1, command.name, ft_strlen(command.name));
	write(1, ": ", 2);
	write(1, command.arg[1], ft_strlen(command.arg[1]));
	write(1, ": ", 2);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
	g_error = 1;
}

void	cd_minus(t_col *col)
{
	int i;
	int flag;

	i = 0;
	if (col->flag_minus == 1)
	{
		write(1, "cd: OLDPWD not set\n", 19);
		g_error = 1;
		return ;
	}
	flag = chdir(col->old_d);
	if (flag == -1)
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
		g_error = 1;
	}
	else
	{
		col->flag_minus = 2;
		change_pwd(col);
		sort_exp(col);
		mypwd();
		g_error = 0;
	}
}

void	cd_home(t_col *col)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		if (ft_strncmpmy("HOME=", col->env[i]) == 0)
		{
			g_error = 0;
			return ;
		}
		if (ft_strncmp("HOME=", col->env[i], 5) == 0 &&
			ft_strlen(col->env[i]) > 5)
		{
			cd_home2(col, i);
			return ;
		}
		i++;
	}
	write(1, "cd: HOME not set\n", 17);
	g_error = 1;
}

void	cd_home2(t_col *col, int i)
{
	int flag;

	flag = chdir(&col->env[i][5]);
	if (flag == -1)
	{
		write(1, "cd: ", 4);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, ": ", 2);
		write(1, &col->env[i][5], ft_strlen(&col->env[i][5]));
		write(1, "\n", 1);
		g_error = 1;
	}
	else
	{
		col->flag_minus = 2;
		change_pwd(col);
		sort_exp(col);
		g_error = 0;
	}
}
