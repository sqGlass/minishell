/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:41:40 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 15:28:57 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_to_exp(t_col *col)
{
	int i;

	i = 0;
	while (col->exp[i])
	{
		if ((ft_strncmp(col->envvar, &col->exp[i][11], ft_strlen(col->envvar))
		== 0 && col->flag_equ == 1) || (ft_strncmp(col->envvar, &col->exp[i][11]
		, ft_strlen(col->envvar) - 1) == 0 && (ft_strlen(col->envvar) - 1 ==
		ft_strlen(&col->exp[i][11])) && col->flag_equ == 1))
		{
			update_exp(&col->exp[i], col);
			return ;
		}
		if ((ft_strncmp(col->envvar, &col->exp[i][11], ft_strlen(col->envvar))
		== 0 && col->flag_equ == 0 && (ft_strlen(col->envvar) == ft_strlen(
		&col->exp[i][11]))) || (ft_strncmp(col->envvar, &col->exp[i][11],
		ft_strlen(col->envvar)) == 0 &&
		ft_strlen(&col->exp[i][11]) > ft_strlen(col->envvar) &&
		col->exp[i][ft_strlen(col->envvar) + 11] == '='))
			return ;
		i++;
	}
	add_new_exp(col);
}

void	update_exp(char **str, t_col *col)
{
	free(*str);
	*str = ft_strjoin(col->envvar, col->envval);
	if (*str == NULL)
		exit(1);
	add_declare(str);
	if (ft_strncmpmy("\"\"", col->envval) != 0)
		add_quot(str);
}

void	add_new_exp(t_col *col)
{
	int i;

	i = 0;
	col->exp = myrealloc(col->exp);
	while (col->exp[i])
		i++;
	if (col->flag_equ == 1)
	{
		if ((col->exp[i] = ft_strjoin(col->envvar, col->envval)) == 0)
			exit(0);
		add_declare(&col->exp[i]);
		if (ft_strncmpmy("\"\"", col->envval) != 0)
			add_quot(&col->exp[i]);
	}
	else
	{
		col->exp[i] = ft_calloc(ft_strlen(col->envvar) + 1, sizeof(char));
		if (col->exp[i] == NULL)
			exit(1);
		ft_strlcpy(col->exp[i], col->envvar, ft_strlen(col->envvar) + 1);
		add_declare(&col->exp[i]);
	}
}
