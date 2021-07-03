/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:13:58 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 20:05:18 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	try_unset_exp(char *str, t_col *col)
{
	int i;

	i = 0;
	while (col->exp[i])
	{
		if ((ft_strncmp(str, &col->exp[i][11], ft_strlen(str)) == 0) &&
			ft_strlen(str) < ft_strlen(&col->exp[i][11]))
		{
			if (col->exp[i][ft_strlen(str) + 11] == '=')
			{
				unset_exp(col, col->exp[i]);
				return ;
			}
		}
		if (ft_strncmpmy(str, &col->exp[i][11]) == 0)
		{
			unset_exp(col, col->exp[i]);
			return ;
		}
		i++;
	}
}

void	unset_exp(t_col *col, char *str)
{
	int		i;
	int		j;
	char	**newarr;

	i = 0;
	j = 0;
	newarr = NULL;
	while (col->exp[i])
		i++;
	newarr = ft_calloc(i, sizeof(char*));
	if (newarr == NULL)
		exit(1);
	i = 0;
	while (col->exp[i])
	{
		if (ft_strncmpmy(col->exp[i], str) == 0)
			i++;
		if (col->exp[i] == 0)
			break ;
		newarr[j] = ft_strdup(col->exp[i]);
		i++;
		j++;
	}
	freesh(col->exp);
	col->exp = newarr;
}

int		chek_exp_err2(char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
	{
		write(1, "minishell: unset: `", 19);
		write(1, str, ft_strlen(str));
		write(1, "': not a valid identifier\n", 26);
		return (1);
	}
	if (ft_strncmpmy(str, "_") == 0 || ft_strncmp(str, "_=", 2) == 0)
		return (1);
	while (str[i])
	{
		if (str[i] != '_' && ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0)
		{
			write(1, "minishell: unset: `", 19);
			write(1, str, ft_strlen(str));
			write(1, "': not a valid identifier\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}
