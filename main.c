/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:06:34 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/09 19:38:22 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static int	empty_or_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

void	parse_pipx(t_pipx *pipx, char **argv)
{
	int		i;
	char	**tmp_ar;

	tmp_ar = NULL;
	malloc_fds(pipx, pipx->n_els, 0, 0);
	i = 2;
	while (argv && argv[i] && i < pipx->n_els + 3 - 1)
	{
		if (empty_or_only_spaces(argv[i]))
		{
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd(": command not found", 2);
		}
		tmp_ar = ft_split(argv[i], ' ');
		if (!tmp_ar)
			exit_err_malloc(pipx, NULL, NULL);
		pipx_push_el(pipx, tmp_ar);
		free_2dim_arr(tmp_ar);
		tmp_ar = NULL;
		++i;
	}
	pipx->start_el = pipx->els;
	pipx->infile = ft_strdup(argv[1]);
	pipx->outfile = ft_strdup(argv[pipx->n_els + 3 - 1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipx	pipx;

	if (argc < 5)
		exit_err_text(NULL, NULL, NULL, "Error.\nNumber of args less than 5.\n");
	pipx.els = NULL;
	pipx.start_el = NULL;
	pipx.pid = 1;
	pipx.envs = copy_2dim_arr(&pipx, envp);
	pipx.n_els = count_els_2dim_arr(argv) - 3;
	pipx.n_els_left = pipx.n_els;
	parse_pipx(&pipx, argv);
	pipx.fds[0] = dup(0);
	pipx.fds[1] = dup(1);
	exec_pipe(&pipx);
	free_pipx(&pipx);
	return (0);
}
