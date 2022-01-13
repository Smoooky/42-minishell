/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 01:12:03 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/12 03:08:25 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

int	find_path(char **paths_tmp, char **cmd_args, char **new_path)
{
	int		i;
	char	*tmp;

	i = -1;
	while (paths_tmp[++i])
	{
		tmp = ft_strjoin(paths_tmp[i], "/");
		if (!tmp)
			return (-1);
		*new_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (!*new_path)
			return (-1);
		if (access(*new_path, F_OK & X_OK) == 0)
			return (1);
		free(*new_path);
	}
	*new_path = NULL;
	return (0);
}

int		find_exec(char **cmd_args, char **env)
{
	int		i;
	char	**paths_tmp;
	char	*exec_path;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			break ;
	paths_tmp = ft_split(env[i] + 5, ':');
	if (!paths_tmp || find_path(paths_tmp, cmd_args, &exec_path) < 0)
	{
		ft_free_charmtrx(paths_tmp);
		return (-1);
	}
	ft_free_charmtrx(paths_tmp);
	if (exec_path)
		execve(exec_path, cmd_args, env);
	return (0);
}

void	exec_cmd(char **cmd_args, t_data *all)
{
	if (cmd_args[0][0] != '/' && cmd_args[0][0] != '.')
	{
		if (find_exec(cmd_args, all->env) < 0)
			return ;
		all->error_message = ft_strdup("command not found");
	}
	else
	{
		/*this variant doesn't provide for an explanation explicit enough:
		for example, if instead of a binary file there is a directory;
		open() could have resolved this problem but!
		it doesnt work on binary files, jokes on you
		i guess it should be done using stat(), i'll try it later*/
		if (access(cmd_args[0], F_OK & X_OK) == 0)
			execve(cmd_args[0], cmd_args, all->env);
	}
	all->error_ident = ft_strdup(cmd_args[0]);
}