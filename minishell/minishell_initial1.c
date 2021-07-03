/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initial1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:05:37 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 11:37:05 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initstruct(t_col *col, char **envp)
{
	col->exp = NULL;
	col->env = NULL;
	col->envval = NULL;
	col->envvar = NULL;
	col->flag_equ = 0;
	col->flag_cd = 0;
	col->flag_pwd = 0;
	col->flag_old = 0;
	col->flag_exist = 0;
	col->flag_unset_strt = 0;
	col->actual_d = getcwd(NULL, 0);
	col->currend_d = getcwd(NULL, 0);
	col->old_d = getcwd(NULL, 0);
	col->old_pwd = NULL;
	col->flag_first_pwd = 0;
	col->flag_minus = 0;
	fillarr(col, envp);
	sort_exp(col);
	initstruct2(col);
}

void	initstruct2(t_col *col)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = getcwd(NULL, 0);
	while (col->exp[i])
	{
		add_declare(&col->exp[i]);
		add_quot(&col->exp[i]);
		i++;
	}
	my_unset("OLDPWD", col);
	my_unset("PWD", col);
	i = 0;
	while (col->env[i])
		i++;
	col->env = myrealloc(col->env);
	col->exp = myrealloc(col->exp);
	col->env[i] = ft_strjoin("PWD=", tmp);
	free(tmp);
	tmp = getcwd(NULL, 0);
	col->exp[i] = ft_strjoin("declare -x PWD=", tmp);
	free(tmp);
	initstruct3(col);
}

void	initstruct3(t_col *col)
{
	int i;

	i = 0;
	while (col->exp[i])
		i++;
	col->exp = myrealloc(col->exp);
	col->exp[i] = ft_strdup("declare -x OLDPWD");
	sort_exp(col);
	col->flag_old = 2;
	change_shlvl(col);
	change_shlvl_exp(col);
}
