/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:49:09 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 16:45:36 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_symb(char *line)
{
	int		i;

	i = 1;
	if (line[i] == '>' || line[i] == '<')
		i++;
	while (line[i] == ' ')
		i++;
	return (i);
}

static int	error_ret(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd("'\n", 1);
	free(token);
	return (-1);
}

int			token(char *line)
{
	int		i;
	int		j;
	char	*token;

	i = -1;
	j = 0;
	if ((token = ft_calloc(ft_strlen(line) + 1, sizeof(char))) == 0)
		return (-2);
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			i += skip_symb(&line[i]);
			while (line[i] != 0 && line[i] != ' ')
			{
				if ((line[i] == '>' || line[i] == '<') &&
				(line[i - 1] >= '0' && line[i - 1] <= '9'))
					return (error_ret(token));
				token[j++] = line[i++];
			}
		}
	}
	free(token);
	return (0);
}
