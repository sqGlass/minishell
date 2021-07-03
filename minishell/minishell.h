/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:27:31 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 23:38:58 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct	s_cmd
{
	char		*name;
	int			flag;
	char		**arg;
	int			redir_count;
	char		**redir;
	int			fd[2];
	int			rd[2];
}				t_cmd;

typedef struct	s_all
{
	int			cmd_count;
	int			err_flag;
	t_cmd		*cmd;
}				t_all;

typedef struct	s_col
{
	char		**env;
	char		**exp;
	char		*envvar;
	char		*envval;
	char		*actual_d;
	char		*currend_d;
	char		*old_d;
	char		*old_pwd;
	int			flag_equ;
	int			flag_cd;
	int			flag_pwd;
	int			flag_old;
	int			flag_exist;
	int			flag_unset_strt;
	int			flag_first_pwd;
	int			flag_minus;
}				t_col;

/*
** PARSER FUNCS
*/

int				main(int argc, char **argv, char **envp);
int				parser(char *line, t_col *col);
char			**ft_split2(char const *s, char c);
char			*preparse(char *line);
int				line_check(char *line);
int				starter(int	argc, char **argv, t_col *col);
int				er(char *s);
int				quotes(char *line);
int				back_slash(char *line);
int				r_c(char *line);
char			*redit_space(char *line);
char			*doll_parse(char *line);
char			*line_doll(char *env);
int				symb_count(char *line, char **envp);
char			*dollar(char *line, t_col *col);
int				inside_quotes(char *line, int c, int z);
char			*arrow_content(char **arg);
char			**file_check(char **arg, t_cmd *cmd, int z);
int				wd_count(char *line, char c);
int				split_counter(char **buffer);
void			freesher(char **str);
char			*true_content(t_all *all, int i, int j, int z);
int				cmd_parser(t_all *all, char *pipe_split, int i, int j);
int				big_free(t_all *all, int all_count);
int				error_exit2();
int				token(char *line);
int				inside_quotes2(char *line, int c, int z);
int				open_close(char **arg, t_cmd *cmd, int z, int i);
int				is_redir(char **arg, int i);
int				rfdf_count(char **arg, t_cmd *cmd, int z);
int				open_file(char **arg, int *fd, int i, int flag);
int				open_read_file(char **arg, int *rd, int i, int flag);
char			*error_parse(char *line);
int				reveal_magic(char *arg, int f, int g, char *str);
int				is_spaces(char *str);
/*
** PIPES FUNCS
*/

int				check_exec(t_cmd command, char **paths);
int				cmd_exist_check(t_col *col, t_cmd command);
int				prev_exec(char **paths);
int				prev_fail(t_col *col, t_cmd command);
void			exec_cmd(t_col *col, t_cmd command, char **paths);
void			fail_exit_status_ret(t_col *col, t_cmd command);
void			exec_found_cmd(t_col *col, t_cmd command);
int				dup_func(int **pfd, int i, int all_count, t_cmd cmd);
void			export2(t_cmd command, t_col *col);
void			roll_commands(t_all all, t_col *col);
void			pfd_free(int count, int **pfd);
int				is_my_cmd(char *name);
int				**create_pipefd(int count);
char			**path_redact(t_col *col, char *name);

/*
** COMMANDS
*/

void			roll_parts(t_all all, t_col *col);
void			roll_commands(t_all all, t_col *col);
void			myecho(t_cmd command);
void			myecho2(t_cmd command, int i, int flag);
int				check_redir(t_cmd command, int i);
void			scipredirs(t_cmd command, int i);
void			create_files(t_cmd command, int flag, int i);
int				fillarr(t_col *col, char **envp);
void			initstruct(t_col *col, char **envp);
void			initstruct2(t_col *col);
void			initstruct3(t_col *col);
void			fillenv(t_col *col, char **envp);
void			direction(t_all all, t_col *col);
void			mycd(t_cmd command, t_col *col);
void			cd_message(t_cmd command);
void			change_pwd(t_col *col);
void			change_env(t_col *col);
void			change_env2(t_col *col, char *old);
void			change_env3(t_col *col, char *old);
void			change_env4(t_col *col, char *old);
void			change_env5(t_col *col);
void			change_env6(t_col *col);
void			change_env2_1(t_col *col, int i);
void			change_env2_2(t_col *col, int i);
void			change_env2_3(t_col *col);
int				count_pwd(t_col *col);
void			change_exp(t_col *col);
void			change_exp2(t_col *col, int i);
void			change_exp3(t_col *col, int i);
void			mypwd();
void			myexport(t_cmd command, t_col *col, int c);
void			myexport2(t_cmd command, t_col *col, int c);
void			myexport3(t_cmd command, t_col *col, int c);
int				find_envvar(t_cmd command, t_col *col, int c);
void			find_envval(t_cmd command, t_col *col, int count, int c);
void			show_export(t_col *col);
void			add_to_exp(t_col *col);
void			update_exp(char **str, t_col *col);
void			sort_exp(t_col *col);
void			add_declare(char **str);
void			add_quot(char **str);
void			add_quot2(char **str, int count);
char			**myrealloc(char **arr);
void			add_new_exp(t_col *col);
void			add_to_env(t_col *col);
void			update_env(char **str, t_col *col);
void			add_new_env(t_col *col);
void			myenv(t_col *col);
int				chek_exp_err(char *str);
int				chek_exp_err2(char *str);
char			*find_value(t_col *col);
void			add_oldpwd(t_cmd command, t_col *col);
void			free_struct(t_col *col);
void			my_unset(char *str, t_col *col);
void			my_unset_pwd(t_col *col);
void			try_unset_env(char *str, t_col *col);
void			unset_env(t_col *col, char *str);
void			try_unset_exp(char *str, t_col *col);
void			unset_exp(t_col *col, char *str);
void			freesh(char **arr);
int				count_arr(char **arr);
int				is_in_env(t_col *col, char *str);
void			change_shlvl(t_col *col);
void			add_new_shlvl(char **str);
int				check_symbols_shlvl(char *str);
char			*try_iter_shlvl(char *str);
void			cd_home(t_col *col);
void			cd_home2(t_col *col, int i);
void			cd_minus(t_col *col);
void			roll_commands2(t_all all, t_col *col);
void			roll_commands(t_all all, t_col *col);
void			fre(t_col *col);
void			sorter1(t_cmd command, t_col *col);
void			sorter_echo(t_cmd command);
void			sorter_cd(t_cmd command, t_col *col);
void			sorter_pwd(t_cmd command);
void			sorter_export(t_cmd command, t_col *col);
void			sorter_env(t_cmd command, t_col *col);
void			sorter_unset(t_cmd command, t_col *col);
void			search_command(t_col *col, t_cmd command);
void			search_command22(t_col *col, t_cmd command);
void			search_command33(t_col *col, t_cmd command);
void			search_command44(t_cmd command);
char			*mypath(t_col *col);
void			try_exec(t_col *col, t_cmd command, char **paths);
void			try_exec_message(t_cmd command);
void			my_exit(t_col *col, t_cmd command);
void			check_exit_arg1(char **arg, t_col *col);
void			check_exit_arg2(char **arg, t_col *col, int j);
void			dev_mod(char *arg);
void			cleaner(t_col *col);
void			invis_oldpwd(t_col *col);
void			change_shlvl_exp(t_col *col);
char			*find_shlvl_env(t_col *col);

extern int		g_error;
extern int		g_quit;
extern int		g_sig;

#endif
