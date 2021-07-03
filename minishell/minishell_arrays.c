/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_arrays.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:39:39 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 12:03:45 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		fillarr(t_col *col, char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	col->exp = ft_calloc((i + 1), sizeof(char *));
	if (col->exp == NULL)
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	col->env = ft_calloc((i + 1), sizeof(char *));
	if (col->env == NULL)
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	while (j < i)
	{
		col->exp[j] = ft_strdup(envp[j]);
		col->env[j] = ft_strdup(envp[j]);
		j++;
	}
	return (i);
}

void	sort_exp(t_col *col)
{
	int		j;
	int		i;
	char	*temp;

	j = 0;
	i = -1;
	temp = NULL;
	while (col->exp[j])
		j++;
	while (i++ < j - 2)
	{
		if (ft_strncmpmy(col->exp[i], col->exp[i + 1]) > 0)
		{
			temp = strdup(col->exp[i]);
			free(col->exp[i]);
			col->exp[i] = ft_strdup(col->exp[i + 1]);
			free(col->exp[i + 1]);
			col->exp[i + 1] = ft_strdup(temp);
			free(temp);
			i = -1;
		}
	}
}

void	add_declare(char **str)
{
	char *temp;

	if (*str == 0)
		return ;
	temp = ft_strdup(*str);
	free(*str);
	*str = ft_strjoin("declare -x ", temp);
	free(temp);
}

void	add_quot(char **str)
{
	int i;
	int count;

	i = 0;
	count = ft_strlen(*str);
	while (str[0][i])
	{
		if (str[0][i] == '=')
		{
			add_quot2(str, i);
			return ;
		}
		i++;
	}
}

void	add_quot2(char **str, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = strdup(*str);
	free(*str);
	*str = ft_calloc(ft_strlen(temp) + 3, sizeof(char));
	while (temp[j])
	{
		str[0][i] = temp[j];
		if (j == count)
		{
			str[0][j + 1] = '"';
			i++;
		}
		i++;
		j++;
	}
	free(temp);
	str[0][i] = '"';
}
