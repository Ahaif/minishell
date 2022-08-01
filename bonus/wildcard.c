/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 00:18:51 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 21:02:39 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	count_all(char **args)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (args[i])
	{
		i++;
	}
	return (i);
}

char	*get_this(char *name)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_strlen(name));
	while (name[i])
	{
		str[i] = name[i];
		i++;
	}
	return (str);
}

char	**merge_things(char **args, char **dirs)
{
	int		i;
	int		args_size;
	int		dirs_size;
	char	**all;
	int		j;

	args_size = arg_strlen(args);
	dirs_size = arg_strlen(dirs);
	all = malloc((args_size + dirs_size + 1) * sizeof(char *));
	i = -1;
	j = 0;
	while (args[++i])
	{
		if (args[i][0] == '*')
			;
		else
			all[j++] = ft_strdup(args[i]);
	}
	i = 0;
	while (dirs[i])
		all[j++] = ft_strdup(dirs[i++]);
	all[j] = 0;
	return (all);
}

char	**get_dir_files(char **arg, char **args, int index)
{
	t_dir_args	var;

	index = 0;
	dir_init(&var, args);
	while (1)
	{
		var.read_dir = readdir(var.open_dir);
		if (var.read_dir == NULL)
			break ;
		if (var.read_dir->d_name[0] == '.')
			continue ;
		var.dirs[var.i] = get_dir_name(var.read_dir->d_name);
		var.i++;
	}
	var.dirs[var.i] = 0;
	var.roles = merge_things(arg, var.dirs);
	return (var.roles);
}

char	**handle_wild_card(char *line, char **args)
{
	int		i;
	char	**roles;

	(void )line;
	i = 0;
	roles = get_dir_files(args, &args[i], i);
	return (roles);
}
