/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:38:35 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 20:57:56 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

char	**grep_env_name(char *line)
{
	char	**args;
	int		i;

	i = 0;
	args = bring_args_in(line);
	while (args[i])
	{
		args[i] = remove_quotes_if_exists(args[i]);
		if (args[i] == NULL)
		{
			args[0] = NULL;
			return (NULL);
		}
		i++;
	}
	return (args);
}

void	my_unset(char *line)
{
	char	**env_name;
	int		i;
	char	*new;

	i = 0;
	new = remove_unset(line);
	env_name = grep_env_name(new);
	if (env_name[0] == NULL)
		return ;
	else
	{
		if (check_unset_errors(env_name) == 1)
			time_to_unset(env_name);
	}
	free(new);
}

int	check_unset_errors(char **env_name)
{
	int	i;

	i = 0;
	while (env_name[i])
	{
		if (cmd_contain(env_name[i], ' ') || check_alpha_n(env_name[i]) == 0
			|| (ft_isdigit(env_name[i][0])))
		{
			printf("unset: `%s': not a valid identifier\n", env_name[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	time_to_unset(char **env_name)
{
	int	i;
	int	world_len;
	int	j;

	j = 0;
	i = 0;
	while (g_env_var.env[i])
	{
		world_len = ft_strlen(env_name[j]);
		if (!ft_strncmp(env_name[j], g_env_var.env[i], world_len)
			&& g_env_var.env[i][world_len] == '=')
		{
			free(g_env_var.env[i]);
			g_env_var.env[i] = g_env_var.env[i + 1];
			while (g_env_var.env[i])
			{
				g_env_var.env[i] = g_env_var.env[i + 1];
				i++;
			}
			j++;
			i = 0;
		}
		i++;
	}
}
