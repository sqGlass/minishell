/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:59:21 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 16:51:59 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	myexport(t_cmd command, t_col *col, int c)
{
	int err;

	col->envvar = NULL;
	col->envval = NULL;
	col->flag_equ = 0;
	if (command.arg[c] == NULL)
	{
		show_export(col);
		g_error = 0;
		return ;
	}
	myexport2(command, col, c);
	err = chek_exp_err(command.arg[c]);
	if (err == 1)
	{
		g_error = 1;
		return ;
	}
	myexport3(command, col, c);
}

void	myexport2(t_cmd command, t_col *col, int c)
{
	if (ft_strncmpmy(command.arg[c], "PWD") == 0)
	{
		col->flag_pwd = 1;
		change_env(col);
		change_exp(col);
	}
	if (ft_strncmpmy(command.arg[c], "OLDPWD") == 0)
	{
		col->flag_old = 1;
		change_env(col);
		change_exp(col);
	}
}

void	myexport3(t_cmd command, t_col *col, int c)
{
	int count;

	count = find_envvar(command, col, c);
	if (col->flag_equ == 1)
		find_envval(command, col, count, c);
	add_to_exp(col);
	add_to_env(col);
	sort_exp(col);
	if (col->envvar != NULL)
	{
		free(col->envvar);
		col->envvar = NULL;
	}
	if (col->envval != NULL)
	{
		free(col->envval);
		col->envval = NULL;
	}
	g_error = 0;
}

void	show_export(t_col *col)
{
	int i;

	i = 0;
	while (col->exp[i])
	{
		write(1, col->exp[i], ft_strlen(col->exp[i]));
		write(1, "\n", 1);
		i++;
	}
}

int		chek_exp_err(char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
	{
		write(1, "minishell: export: `", 20);
		write(1, str, ft_strlen(str));
		write(1, "': not a valid identifier\n", 26);
		return (1);
	}
	if (ft_strncmpmy(str, "_") == 0 || ft_strncmp(str, "_=", 2) == 0)
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0)
		{
			write(1, "minishell: export: `", 20);
			write(1, str, ft_strlen(str));
			write(1, "': not a valid identifier\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}
