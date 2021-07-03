/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_change_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:18:36 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 16:23:26 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	change_exp(t_col *col)
{
	int i;
	int flag_pwd;
	int flag_old;

	i = 0;
	flag_pwd = 0;
	flag_old = 0;
	while (col->env[i])
	{
		if (ft_strncmp("PWD=", col->env[i], 4) == 0)
		{
			change_exp2(col, i);
			flag_pwd = 1;
		}
		if (ft_strncmp("OLDPWD=", col->env[i], 7) == 0)
		{
			change_exp3(col, i);
			flag_old = 1;
		}
		i++;
	}
	sort_exp(col);
}

void	change_exp2(t_col *col, int i)
{
	try_unset_exp("PWD", col);
	col->exp = myrealloc(col->exp);
	col->exp[count_arr(col->exp)] = ft_strdup(col->env[i]);
	add_declare(&col->exp[count_arr(col->exp) - 1]);
	add_quot(&col->exp[count_arr(col->exp) - 1]);
}

void	change_exp3(t_col *col, int i)
{
	try_unset_exp("OLDPWD", col);
	col->exp = myrealloc(col->exp);
	col->exp[count_arr(col->exp)] = ft_strdup(col->env[i]);
	add_declare(&col->exp[count_arr(col->exp) - 1]);
	add_quot(&col->exp[count_arr(col->exp) - 1]);
}
