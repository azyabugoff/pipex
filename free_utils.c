/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 21:43:33 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/09 19:10:41 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	close_all_fds(t_pipx *pipx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < pipx->n_els - 1)
	{
		j = 0;
		while (j < 2)
		{
			if (pipx->fd[i][j] != -1)
				close(pipx->fd[i][j]);
			++j;
		}
		++i;
	}
}

void	free_els_list(t_pipx *pipx)
{
	t_els	*el;

	el = NULL;
	if (pipx->start_el)
	{
		while (pipx->start_el)
		{
			el = pipx->start_el->next;
			free_2dim_arr(pipx->start_el->args);
			free(pipx->start_el);
			pipx->start_el = el;
		}
	}
}

void	free_fds_arr(t_pipx *pipx)
{
	int	i;

	i = 0;
	if (pipx->fd)
	{
		while (i < pipx->n_els - 1)
		{
			free(pipx->fd[i]);
			pipx->fd[i] = NULL;
			++i;
		}
		free(pipx->fd);
		pipx->fd = NULL;
	}
}

static void	close_2fds(t_pipx *pipx)
{
	if (pipx->fds[0] != -1)
		close(pipx->fds[0]);
	if (pipx->fds[1] != -1)
		close(pipx->fds[1]);
}

void	free_pipx(t_pipx *pipx)
{
	if (pipx)
	{
		if (pipx->envs)
		{
			free_2dim_arr(pipx->envs);
			pipx->envs = NULL;
		}
		close_2fds(pipx);
		close_all_fds(pipx);
		free_fds_arr(pipx);
		free_els_list(pipx);
		if (pipx->infile)
		{
			free(pipx->infile);
			pipx->infile = NULL;
		}
		if (pipx->outfile)
		{
			free(pipx->outfile);
			pipx->outfile = NULL;
		}
	}
}
