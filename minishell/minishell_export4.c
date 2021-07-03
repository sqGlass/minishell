/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:27:23 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 16:31:44 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_value(t_col *col)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	while (col->env[i])
	{
		if (ft_strncmp(col->env[i], "PWD=", 4) == 0 &&
		ft_strlen(col->env[i]) > 4)
		{
			value = ft_strdup(&col->env[i][4]);
			return (value);
		}
		if (ft_strncmpmy(col->env[i], "PWD=") == 0)
		{
			value = ft_strdup("OLDPWD=");
			return (value);
		}
		i++;
	}
	return (value);
}

void	change_pwd(t_col *col)
{
	if (col->currend_d != NULL)
		free(col->currend_d);
	col->currend_d = getcwd(NULL, 0);
	col->flag_cd = 1;
	if (col->old_d != NULL)
		free(col->old_d);
	col->old_d = ft_strdup(col->actual_d);
	if (col->actual_d != NULL)
		free(col->actual_d);
	col->actual_d = getcwd(NULL, 0);
	invis_oldpwd(col);
	change_env(col);
	change_exp(col);
}

void	invis_oldpwd(t_col *col)
{
	char *pwd;

	pwd = find_value(col);
	if (col->old_pwd != NULL)
		free(col->old_pwd);
	if (pwd != NULL)
	{
		if ((ft_strncmpmy("OLDPWD=", pwd) == 0))
			col->old_pwd = ft_strdup("OLDPWD=");
		else
		{
			col->old_pwd = ft_strjoin("OLDPWD=", pwd);
			{
				free(pwd);
				if (col->old_pwd == NULL)
					exit(1);
			}
		}
		return ;
	}
	col->old_pwd = ft_strjoin("OLDPWD=", col->old_d);
	if (col->old_pwd == NULL)
		exit(1);
}

int		is_in_env(t_col *col, char *str)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		if (ft_strncmpmy(str, col->env[i]) == 0)
			return (1);
		if (ft_strncmp(str, col->env[i], ft_strlen(str)) == 0
		&& (ft_strlen(col->env[i]) > ft_strlen(str)))
			if (col->env[i][ft_strlen(str)] == '=')
				return (1);
		i++;
	}
	return (0);
}
