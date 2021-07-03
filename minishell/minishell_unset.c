/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:07:49 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 16:49:40 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	my_unset(char *str, t_col *col)
{
	int err;

	if (ft_strncmpmy("PWD", str) == 0)
		my_unset_pwd(col);
	if (ft_strncmpmy("OLDPWD", str) == 0)
	{
		col->flag_cd = 0;
		col->flag_minus = 1;
	}
	if (str == NULL)
	{
		g_error = 0;
		return ;
	}
	err = chek_exp_err2(str);
	if (err == 1)
	{
		g_error = 1;
		return ;
	}
	try_unset_env(str, col);
	try_unset_exp(str, col);
	sort_exp(col);
}

void	my_unset_pwd(t_col *col)
{
	if (col->currend_d != NULL)
	{
		free(col->currend_d);
		col->currend_d = NULL;
	}
	col->flag_exist = 1;
	if (col->flag_unset_strt == 0)
	{
		col->flag_unset_strt = 1;
		col->flag_old = 1;
	}
}

void	try_unset_env(char *str, t_col *col)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		if ((ft_strncmp(str, col->env[i], ft_strlen(str)) == 0) &&
			ft_strlen(str) < ft_strlen(col->env[i]))
		{
			if (col->env[i][ft_strlen(str)] == '=')
			{
				unset_env(col, col->env[i]);
				return ;
			}
		}
		i++;
	}
}

void	unset_env(t_col *col, char *str)
{
	int		i;
	int		j;
	char	**newarr;

	i = 0;
	j = 0;
	newarr = NULL;
	while (col->env[i])
		i++;
	newarr = ft_calloc(i, sizeof(char*));
	if (newarr == NULL)
		exit(1);
	i = 0;
	while (col->env[i])
	{
		if (ft_strncmpmy(col->env[i], str) == 0)
			i++;
		if (col->env[i] == 0)
			break ;
		newarr[j] = ft_strdup(col->env[i]);
		i++;
		j++;
	}
	freesh(col->env);
	col->env = newarr;
}
