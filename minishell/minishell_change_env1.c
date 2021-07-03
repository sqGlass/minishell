/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_change_env1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:12:27 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 16:14:55 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	change_env(t_col *col)
{
	char *old;

	old = find_value(col);
	if (col->flag_pwd != 1)
	{
		change_env2(col, old);
		change_env3(col, old);
		change_env4(col, old);
	}
	change_env5(col);
	change_env6(col);
	if (old != NULL)
		free(old);
}

void	change_env2(t_col *col, char *old)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		if (ft_strncmp(col->env[i], "OLDPWD=", 7) == 0)
		{
			if (old != NULL)
			{
				change_env2_1(col, i);
				break ;
			}
			if (old == NULL && col->flag_exist == 0)
			{
				change_env2_2(col, i);
				break ;
			}
			if (old == NULL && col->flag_exist == 1)
			{
				change_env2_3(col);
				break ;
			}
		}
		i++;
	}
}

void	change_env2_1(t_col *col, int i)
{
	free(col->env[i]);
	col->env[i] = ft_strdup(col->old_pwd);
	col->flag_old = 0;
}

void	change_env2_2(t_col *col, int i)
{
	free(col->env[i]);
	col->env[i] = ft_strjoin("OLDPWD=", col->old_d);
	col->flag_old = 0;
}

void	change_env2_3(t_col *col)
{
	my_unset("OLDPWD", col);
	col->flag_old = 1;
	col->flag_exist = 0;
}
