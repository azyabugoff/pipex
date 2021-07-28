/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:59:13 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/08 23:15:32 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static char	*find_cmd_dir(t_pipx *pipx, char **dirs, char *cmd)
{
	int		i;
	char	*pth;

	i = 0;
	pth = NULL;
	while (dirs && dirs[i])
	{
		pth = ft_strjoin(dirs[i], "/");
		if (!pth)
			exit_err_malloc(pipx, dirs, NULL);
		pth = ft_strjoin1(pth, cmd);
		if (!pth)
			exit_err_malloc(pipx, dirs, NULL);
		if (access(pth, F_OK) == 0)
			return (pth);
		free(pth);
		pth = NULL;
		++i;
	}
	return (NULL);
}

static int	print_errs_126_127(int num_err, char *path, char **dirs)
{
	ft_putstr_fd(path, 2);
	if (num_err == 1)
	{
		if (!ft_strcmp(strerror(errno), "Not a directory"))
			ft_putendl_fd(": Premission denied", 2);
		else
			ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	else if (num_err == 3)
	{
		free_2dim_arr(dirs);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	return (-1);
}

static int	check_bin_exec(char *path, t_pipx *pipx)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_errs_126_127(1, path, NULL));
	close(fd);
	exit_no_err(pipx, execve(path, pipx->els->args, pipx->envs));
	return (0);
}

static int	join_path_to_cmd(t_pipx *pipx, char **path)
{
	char	*path_env;
	char	**dirs;

	path_env = NULL;
	dirs = NULL;
	path_env = get_env(pipx, "PATH");
	if (!path_env)
		exit_err_text(pipx, NULL, NULL, "Error.\nPATH is unset.\n");
	dirs = ft_split(path_env, ':');
	if (!dirs)
		exit_err_malloc(pipx, NULL, path_env);
	free(path_env);
	*path = find_cmd_dir(pipx, dirs, pipx->els->args[0]);
	if (!(*path))
		return (print_errs_126_127(3, pipx->els->args[0], dirs));
	free_2dim_arr(dirs);
	return (-1);
}

int	exec_bin_pipe(t_pipx *pipx)
{
	char	*path;
	int		check;

	path = NULL;
	check = 0;
	if (ft_strchr(pipx->els->args[0], '/') == NULL)
	{
		check = join_path_to_cmd(pipx, &path);
		if (check != -1)
			return (check);
		check = check_bin_exec(path, pipx);
		if (check)
		{
			free(path);
			return (check);
		}
		free(path);
	}
	else
	{
		check = check_bin_exec(pipx->els->args[0], pipx);
		if (check)
			return (check);
	}
	return (0);
}
