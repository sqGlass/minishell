/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_change_env2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:14:25 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 16:14:52 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	change_env3(t_col *col, char *old)
{
	if (col->flag_old == 1 && col->flag_cd == 1)
	{
		if (col->flag_unset_strt != 1)
		{
			col->env = myrealloc(col->env);
			if (old != NULL && ft_strncmpmy(old, col->currend_d) != 0)
				col->env[count_arr(col->env)] = ft_strjoin("OLDPWD=", old);
			else
				col->env[count_arr(col->env)] = ft_strjoin("OLDPWD=",
				col->old_d);
			col->flag_old = 0;
		}
		else
		{
			col->flag_unset_strt = 2;
			col->flag_exist = 0;
		}
	}
}

void	change_env4(t_col *col, char *old)
{
	if (col->flag_old == 2)
	{
		col->env = myrealloc(col->env);
		if (old != NULL && ft_strncmpmy(old, col->currend_d) != 0)
			col->env[count_arr(col->env)] = ft_strjoin("OLDPWD=", old);
		else
			col->env[count_arr(col->env)] = ft_strjoin("OLDPWD=", col->old_d);
		col->flag_old = 0;
	}
	if (col->flag_old == 1)
		col->flag_old = 2;
	col->flag_unset_strt = 2;
}

void	change_env5(t_col *col)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		if (ft_strncmp(col->env[i], "PWD=", 4) == 0)
		{
			if (col->currend_d != NULL)
			{
				free(col->env[i]);
				col->env[i] = ft_strjoin("PWD=", col->currend_d);
			}
			col->flag_pwd = 0;
			break ;
		}
		i++;
	}
}

void	change_env6(t_col *col)
{
	if (col->flag_pwd == 1 && col->currend_d != NULL)
	{
		col->env = myrealloc(col->env);
		col->env[count_arr(col->env)] = ft_strjoin("PWD=", col->currend_d);
		col->flag_pwd = 0;
		write(1, "hel", 3);
	}
	if (col->flag_pwd == 2 && col->currend_d != NULL)
	{
		col->env = myrealloc(col->env);
		col->env[count_arr(col->env)] = ft_strjoin("PWD=", col->currend_d);
		col->flag_pwd = 0;
	}
	if (col->flag_pwd == 1)
	{
		col->flag_pwd = 2;
	}
}
