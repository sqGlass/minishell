/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:35:39 by sglass            #+#    #+#             */
/*   Updated: 2021/03/09 00:37:07 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	change_shlvl_exp(t_col *col)
{
	int i;

	i = 0;
	while (col->exp[i])
	{
		if (ft_strncmp("declare -x SHLVL=", col->exp[i], 17) == 0)
		{
			free(col->exp[i]);
			col->exp[i] = ft_strdup(find_shlvl_env(col));
			add_declare(&col->exp[i]);
			add_quot(&col->exp[i]);
			sort_exp(col);
			return ;
		}
		i++;
	}
}

char	*find_shlvl_env(t_col *col)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		if (ft_strncmp("SHLVL=", col->env[i], 6) == 0)
			return (col->env[i]);
		i++;
	}
	return (NULL);
}

void	change_shlvl(t_col *col)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		if (ft_strncmpmy("SHLVL=", col->env[i]) == 0)
		{
			free(col->env[i]);
			col->env[i] = ft_strdup("SHLVL=1");
			return ;
		}
		if (ft_strncmp("SHLVL=", col->env[i], 6) == 0)
		{
			add_new_shlvl(&col->env[i]);
			return ;
		}
		i++;
	}
	col->env = myrealloc(col->env);
	col->env[count_arr(col->env)] = ft_strdup("SHLVL=1");
	col->exp = myrealloc(col->exp);
	col->exp[count_arr(col->exp)] = ft_strdup("declare -x SHLVL=""1""");
}

void	add_new_shlvl(char **str)
{
	int		i;
	char	*c;

	i = 6;
	if (str[0][i] == '-' || str[0][i] == '+')
		i++;
	if (check_symbols_shlvl(&str[0][i]) == 1)
	{
		c = try_iter_shlvl(&str[0][6]);
		free(*str);
		if (ft_strncmpmy(c, "1000") == 0)
			*str = ft_strdup("SHLVL=");
		else
			*str = ft_strjoin("SHLVL=", c);
		if (c != NULL)
			free(c);
	}
	else
	{
		free(*str);
		*str = ft_strdup("SHLVL=1");
	}
}

int		check_symbols_shlvl(char *str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}
