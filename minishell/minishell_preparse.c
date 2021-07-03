/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_preparse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:33:20 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 19:23:31 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*doll_parse(char *line)
{
	int		i;
	char	*doll;

	i = 0;
	while (line[i] != 0 && line[i] != ' ' && line[i] != '!' && line[i] != '@'
	&& line[i] != '#' && line[i] != '%' && line[i] != '$' && line[i] != '^'
	&& line[i] != '&' && line[i] != '*' && line[i] != '-' && line[i] != '+'
	&& line[i] != -4 && line[i] != -5 && line[i] != -6 && line[i] != '=')
		i++;
	if ((doll = ft_calloc(i + 1, sizeof(char))) == 0)
		return (0);
	i = 0;
	while (line[i] != 0 && line[i] != ' ' && line[i] != '!' && line[i] != '@'
	&& line[i] != '#' && line[i] != '%' && line[i] != '$' && line[i] != '^'
	&& line[i] != '&' && line[i] != '*' && line[i] != '-' && line[i] != '+'
	&& line[i] != -4 && line[i] != -5 && line[i] != -6 && line[i] != '=')
	{
		doll[i] = line[i];
		i++;
	}
	return (doll);
}

char		*line_doll(char *env)
{
	int		i;
	int		j;
	char	*result;

	j = 0;
	i = 0;
	while (env[i] != '=')
		i++;
	i++;
	if ((result = ft_calloc(ft_strlen(&env[i]) + 1, sizeof(char))) == 0)
		return (0);
	ft_strlcpy(result, &env[i], ft_strlen(&env[i]) + 1);
	return (result);
}

static int	res_redact(char **env, char *doll, int flag, char *copy)
{
	int		j;
	int		z;
	char	*result;

	j = -1;
	z = 0;
	while (env[++j])
		if (ft_strncmpeq(env[j], doll, ft_strlen(doll)) == 0)
		{
			result = line_doll(env[j]);
			if (flag == 1)
				z += ft_strlen(result) + 1;
			else
				z += ft_strlcpy(&copy[z], result, ft_strlen(result) + 1);
			free(result);
			break ;
		}
	return (z);
}

int			symb_count(char *line, char **envp)
{
	int		i;
	int		z;
	char	*doll;

	i = -1;
	z = 0;
	while (line[++i])
	{
		while (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\0'
		&& line[i - 1] != -4)
		{
			doll = doll_parse(&line[i + 1]);
			i += ft_strlen(doll) + 1;
			z += res_redact(envp, doll, 1, 0);
			free(doll);
		}
		z++;
	}
	return (z);
}

char		*dollar(char *line, t_col *col)
{
	int		i;
	int		z;
	char	*doll;
	char	*copy;

	i = -1;
	z = 0;
	if ((copy = ft_calloc(symb_count(line, col->env) + 1, sizeof(char))) == 0)
		return (0);
	while (line[++i])
	{
		while (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\0'
		&& line[i - 1] != -4)
		{
			doll = doll_parse(&line[i + 1]);
			i += ft_strlen(doll) + 1;
			z += res_redact(col->env, doll, 2, &copy[z]);
			free(doll);
		}
		copy[z++] = line[i];
	}
	free(line);
	return (copy);
}
