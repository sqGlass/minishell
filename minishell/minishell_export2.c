/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:24:39 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 15:06:47 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_to_env(t_col *col)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		if (ft_strncmp(col->envvar, col->env[i],
			ft_strlen(col->envvar)) == 0 && col->flag_equ == 1)
		{
			update_env(&col->env[i], col);
			return ;
		}
		i++;
	}
	if (col->flag_equ == 1)
		add_new_env(col);
}

void	update_env(char **str, t_col *col)
{
	free(*str);
	if (ft_strncmpmy("\"\"", col->envval) != 0)
	{
		*str = ft_strjoin(col->envvar, col->envval);
		if (*str == NULL)
			exit(1);
	}
	else
	{
		*str = ft_strdup(col->envvar);
		if (*str == NULL)
			exit(1);
	}
}

void	add_new_env(t_col *col)
{
	int i;

	i = 0;
	col->env = myrealloc(col->env);
	while (col->env[i])
		i++;
	if (ft_strncmpmy("\"\"", col->envval) != 0)
	{
		col->env[i] = ft_strjoin(col->envvar, col->envval);
		if (col->env[i] == NULL)
			exit(1);
	}
	else
	{
		col->env[i] = ft_strdup(col->envvar);
		if (col->env[i] == NULL)
			exit(1);
	}
}

void	find_envval(t_cmd command, t_col *col, int count, int c)
{
	if ((int)ft_strlen(command.arg[c]) > count)
	{
		col->envval = ft_calloc(ft_strlen(command.arg[c]) - count + 1,
		sizeof(char));
		ft_strlcpy(col->envval, &command.arg[c][count],
		ft_strlen(command.arg[c]) - count + 1);
	}
	else
		col->envval = ft_strdup("\"\"");
}

int		find_envvar(t_cmd command, t_col *col, int c)
{
	int i;

	i = 0;
	while (command.arg[c][i])
	{
		if (command.arg[c][i] == '=')
		{
			col->envvar = ft_calloc(i + 3, sizeof(char));
			if (col->envvar == NULL)
				exit(1);
			ft_strlcpy(col->envvar, command.arg[c], i + 2);
			col->flag_equ = 1;
			return (i + 1);
		}
		i++;
	}
	col->envvar = ft_calloc(ft_strlen(command.arg[c]) + 1, sizeof(char));
	ft_strlcpy(col->envvar, command.arg[c], i + 1);
	col->flag_equ = 0;
	return (-1);
}
