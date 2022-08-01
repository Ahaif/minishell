/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:25:21 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 03:22:01 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_contain(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	pipe_contain(char *str, char c)
{
	while (*str)
	{
		if (*str == c && *(++str) != '|')
			return (1);
		str++;
	}
	return (0);
}

void	handle_absolute_path(char *cmd, char **args)
{
	char	*result;

	result = handle_quotes(cmd);
	execute_single_cmd(result, "", args);
}

void	parser_and_execute(char *str)
{
	char	*trimed_str;

	if (str == NULL)
		ctrl_d_handler(1);
	trimed_str = ft_strtrim(str, " ");
	if (trimed_str[0] == '\0')
		return ;
	if (!str_str(str, "<<"))
		add_history(trimed_str);
	if ((not_contain(str, '>') || cmd_contain(str, '<')
			|| str_str(str, ">>") || str_str(str, "<<"))
		&& (!cmd_contain(str, '|')))
		handlle_redirections(str);
	else if (pipe_contain(str, '|'))
		handlle_pipe(str);
	else if (str_str(str, "<<"))
		return (handlle_redirections(str));
	else
		execute_handler(trimed_str);
	free(str);
	free(trimed_str);
}

void	execute_handler(char *str)
{
	char	**args;
	char	*cmd;
	int		i;

	i = 0;
	args = bring_args_in(str);
	cmd = args[0];
	cmd = handle_quotes(cmd);
	if (cmd == NULL)
		return ;
	while (args[i])
	{
		args[i] = handle_quotes(args[i]);
		if (args[i] == NULL)
			return ;
		i++;
	}
	if (cmd_contain(cmd, '/'))
		handle_absolute_path(cmd, args);
	else
		execute_single_cmd_handler(str, g_env_var.env);
	free_double_char(args);
}
