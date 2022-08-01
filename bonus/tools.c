/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 00:23:12 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 21:03:06 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	arg_strlen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	check_wild_car(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '*')
			return (1);
		i++;
	}
	return (0);
}

int	count_dirs(char **args)
{
	char			*cur_dir;
	DIR				*open_dir;
	struct dirent	*read_dir;
	int				i;

	(void )*args;
	i = 0;
	cur_dir = get_my_env("PWD");
	open_dir = opendir(cur_dir);
	read_dir = readdir(open_dir);
	while (1)
	{
		read_dir = readdir(open_dir);
		if (read_dir == NULL)
			break ;
		if (read_dir->d_name[0] == '.')
			continue ;
		i++;
	}
	closedir(open_dir);
	return (i);
}

char	*get_dir_name(char *name)
{
	char	*dir_name;

	dir_name = ft_strdup(name);
	return (dir_name);
}

void	dir_init(t_dir_args *var, char **args)
{
	var->count = count_dirs(args);
	var->dirs = malloc((var->count + 1) * sizeof(char *));
	var->i = 0;
	var->cur_dir = get_my_env("PWD");
	var->open_dir = opendir(var->cur_dir);
	var->read_dir = readdir(var->open_dir);
}
