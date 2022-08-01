/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:01:17 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 03:21:43 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
// #include <readline/readline.h>
// #include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include "../readline/8.1.2/include/readline/readline.h"
# include "../readline/8.1.2/include/readline/history.h"
# include <string.h>
# include <limits.h>
# include <termios.h>
# include <fcntl.h>

# define STD_INPUT 0
# define STD_OUTPUT 1

typedef struct s_env
{
	char	**env;
	int		status;
}	t_env;

t_env	g_env_var;

typedef struct s_vars
{
	int		i;
	int		single_quote;
	int		double_quote;
	int		count;
	int		j;
	int		start;
	int		and;
	int		k;
	int		or;
	int		end;
	char	**args;
	char	**result;
	int		pipe_counter;
}	t_vars;

typedef struct s_var
{
	int		heredoc_index;
	int		index;
	char	**parsed_pipe;
	int		pipe_fd[2];
	int		old_pipe;
	int		*here_doc;
	int		pid;
	int		i;
}	t_var;

typedef struct s_role
{
	int		i;
	char	**spltd_str;
	char	*del;
	char	*line;
	int		fd_pipe[2];
	char	*temp1;
}	t_role;

typedef struct s_dir_args
{
	int				count;
	char			**dirs;
	char			*cur_dir;
	DIR				*open_dir;
	struct dirent	*read_dir;
	int				i;
	char			**roles;
}	t_dir_args;

void	dir_init(t_dir_args *var, char **args);
void	parser_and_execute(char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putnbr(int nb);
void	ft_putchar(char c);
void	execute_single_cmd(char *path, char *cmd, char **args);
void	execute_single_cmd_handler(char *line, char **envp);
int		cmd_contain(char *str, char c);
void	my_cd(char *path);
void	my_echo(char *arg);
void	my_export(char *line);
void	my_env(char *line, char **envp);
void	my_pwd(char *line);
void	my_exit(char *line);
void	my_unset(char *line);
void	set_old_path(void);
int		old_path_not_set(void);
int		check_surrounded(char *str, int pos);
int		check_forward_s(char *str, int pos);
void	ctrl_c_handler(int sig);
void	disable_signals_terminos(void);
void	ctrl_d_handler(int sig);
void	enable_signals_and_terminos(void);
void	mini_enable_signals_and_terminos(void);
void	disable_signals(void);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char const *s);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);
char	*ft_solution(char *line, int pos);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	my_cd_v1(char *str, char *path, char *home);
void	handle_single_minus(char *path);
void	change_pwd(char *path);
void	chane_old_pwd(char *path);
void	my_cd_v1(char *str, char *path, char *home);
void	my_cd_v2(char *str, char *path, char *home);
void	get_copy(char **envp);
int		count_lines(char **envp);
int		env_checker(char *line);
void	env(char *line, char **envp);
void	free_double_char(char **str);
void	free_single(char *str);
int		argument_check(char *path);
int		check_builtin(char *cmd, char **args, char *line, char **envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	handle_cd_dollar(char *path);
char	*str_to_uppercase(char *str);
char	*env_searcher(char *var);
char	*str_to_lowercase(char *str);
int		check_echo_option(char *line);
char	*remove_echo(char *str, int option_check);
int		line_arg_count(char *str);
char	*get_my_env(char *env_name);
int		check_env_print(char *arg, char *str, int pos);
int		print_env(int start, int end, char *arg);
void	cd_handler(char **args, char *cmd, char *line);
char	*remove_first_quotes(char *str);
char	*remove_export_word(char *line);
int		var_contain_space(char *str);
char	*remove_all_quotes(char *str);
int		count_without_quotes(char *str);
int		check_if_not_valid(char *str);
char	*get_first_arg(char *str);
char	*get_export_elem(char *str);
void	export_var_to_env(char *var, char *value);
char	*parse_var(char *var, char *value);
char	**get_my_env_copy(char *var, char *value);
int		count_my_env(void);
void	modify_env_var_value(char *var, char *value);
void	time_to_export(char *line);
char	*remove_quotes_if_exists(char *str);
int		count_no_quotes_str(char *str);
char	*remove_first_last_quotes(char *str);
int		check_same_type_quotes(char *str);
int		check_quotes(char *str, int index, char *arg);
void	ctrl_back_slash(int sig);
void	handle_multiple_cmd(char *str, char **envp);
int		check_self(char *arg);
char	*handle_quotes(char *str);
char	*remove_unset(char *line);
int		check_alpha_n(char *env_name);
void	show_prompt(void);
void	making_fun(void);
void	execute_handler(char *str);
char	**bring_args_in(char *str);
int		check_space(char *str, int pos, char *arg);
int		check_errors(char *str);
int		check_valid_var(char *str);
int		ft_isalpha(char c);
void	enable_child_termios_s(void);
void	mini_enable_child_termios_s(void);
void	handle_mini_exe(void);
void	time_to_unset(char **args);
int		check_unset_errors(char **env_name);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isalpha(char c);
char	**bring_export_args(char *line);
int		quote_is_open(char *line, int start, int i);
int		count_export_args(char *line);
char	*get_export_value(char *str);
char	*get_export_var(char *str);
char	*parse_value(char *var);
char	**handle_exe_args(char **args);
int		check_plus(char *str);
char	*remove_plus(char *str);
void	handle_point(char *str);
void	handle_cd_opt(char *cmd, char *str, char **args);
void	cd_helper(char *home);
void	handle_and_or(char *line);
int		check_and_or_op(char **args);
char	**bring_commandes_in(char *line);
int		count_commands(char *line);
char	*bring_which_op(char *line, char **args);
char	*ft_itoa(int n);
void	inc_bash_lvl(void);
void	dec_bash_lvl(void);
int		get_status_code(int status);
char	*get_dollar_value(char *str);
int		check_too_many_args(char **args);
int		get_cd_path(char *str);
int		okey(void);
void	time_to_execute(char *path, char *cmd, char **args);
void	exe_args_helper(int i, char **args);
void	exe_args_helper1(int i, char **args);
void	status_helper(int status, int sign, int exit_status);
int		line_arg_count_h_2(char *str, int i, int *count);
int		line_arg_count_h_3(char *str, int i, int *count);
void	var_init(t_vars *vars);
int		place_help_s_q_1(char **args, int i, char *str);
int		place_help_s_q_2(char **args, int i, char *str);
void	place_arg(char **args, char *str, int start, int end);
int		arg_count(char **args);
void	echo_helper_1(char *result);
void	echo_helper_2(char *result);
void	echo_helpr_3(char *result);
void	echo_helper_4(char *result);
int		echo_helper_5(char *result);
char	*remove_dollar(char *str);
int		args_quoted_h(char *str, int pos, char *arg);
int		is_valid_echo(char c);
void	exe_echo(char *str, int option_check);
int		get_first_index(char *str, char *arg, char **args, int i);
char	*handle_option_check(char *result);
void	time_to_exit(void);
int		check_exported_var(char *str);
void	handle_solo_export(void);
char	*path_search(char *cmd);
int		check_wild_car(char **args);
char	**handle_wild_card(char *line, char **args);
void	push_to_garbage(void *garbage);
int		arg_strlen(char **args);
char	*get_dir_name(char *name);
int		count_dirs(char **args);
char	*parse_line(char *line);
int		count_line(char *line);
int		count_commands(char *line);
void	and_or_exe(char **args, char *which_op);
void	b_init(t_vars *var, char *line);
void	handlle_pipe(char *str);
char	*op_strjoin(char const *s1, char const *s2);
int		str_len(char const *str);
void	handlle_redirections(char *str);
void	execute_cmd(char *str);
int		check_access(char *str);
char	**op_split(char *str, char *charset);
char	*str_str(char *str, char *to_find);
int		get_infile_fd(char *str);
int		open_files_appe(char *str);
int		open_files(char *str);
char	*get_cmd_heredoc(char *str);
char	*get_cmmd(char *str);
int		handle_heredoc(char *str);
char	**get_path(void);
void	execute_cmd_without_redirect(char **parsed_pipe, int index,
			int fd_old_input, int fd_heredoc);
void	check_acces(char *str);
int		*check_str(char *str);
char	*get_cmd(char *str);
void	redirect_input(char **parsed_pipe, int i, int *fd_pp);
char	*splt_str(char *str, char c, char *red);
int		not_contain(char *str, char c);
void	handle_fd_error(int f1);
int		escape_cmd_open_file(char *str);
int		only_rd_fd(char *str);
int		only_open_append(char *str);
int		only_open(char *str, char c);
int		append_to_first_file(char *str);
int		special_open_for_append(char *str);
int		get_fd_input(char *str);
char	*str_join_heredoc(char *s1, char *s2);
int		open_heredoc(char *str);
int		open_files_heredoc(char *str);
int		open_another_heredoc(char *str_heredoc);
void	execute_cmd_heredoc(char *str, int fd_heredoc);
char	**ft_split22(char *s, char *set);
char	**pipe_spliter(char *str);
int		check_quotes_open(char *str, int i, int index_finish);
int		ft_pipe_counter(char *str);
int		one_word_check(char *str);
void	child_process(t_var *var, int i);
char	*splt_str(char *str, char c, char *red);
void	process_pipes(char **parsed_pipe, int i, int *pipe_fd, int old_pipe);
int		output_redirect(char *str);
int		input_redirect(char *str);
char	*open_other_files(char *str);
int		parent_process(t_var var, int i);
char	*get_cmd_io(char *str, char c);
char	*get_cmd_app(char *str);
int		open_files(char *str);
int		only_append_fd(char *str);
int		input_output_redirect(char *str);
int		*get_heredoc_content(char *str);
int		open_normal_file(char *spltd_str, char c, char *append);
void	here_doc_process(t_var *var, int i);
void	process_redirections(char **parsed_pipe, int i,
			int old_pipe, int *pipe_fd);
int		open_append_mode(char *str);
char	*get_delimetr(char *str);
int		get_count_hd(char *str);
char	*ft_strjoin2_2(char const *s1, char *s2);
int		open_file_greater(char *str, int index);
void	open_file_less(char *str, int index);
char	*get_special_cmd(char *str);
int		truncat_mod_fd(char *str);
int		grammer_check(char *str);
int		one_word_check(char *str);
int		second_word_check(char *str);
int		third_word_check(char *str);
int		and_or_not_quoted(char *str, int index);
void	read_from_pipe(char *parsed_pipe, int old_pipe);
void	helper1_1(t_vars *var, char *which_op);
void	helper2_2(t_vars *var);
void	helper3_3(t_vars *var);
void	help3_3_3(t_vars *var);
void	new_var_init(t_vars *var);

#endif
