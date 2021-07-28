/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:14:37 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/09 20:07:31 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static void	redir_in_out(t_pipx *pipx, int	in_out)
{
	int	fd;

	fd = -1;
	if (in_out == STDIN_FILENO)
		fd = open(pipx->infile, O_RDONLY);
	else if (in_out == STDOUT_FILENO)
		fd = open(pipx->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit_err_text(pipx, NULL, NULL, "\n");
	}
	close(in_out);
	dup2(fd, in_out);
	close(fd);
}

static void	exec_cmd_pipe(t_pipx *pipx)
{
	pipx->pid = fork();
	if (!pipx->pid)
	{
		if (pipx->n_els_left < pipx->n_els)
		{
			close(0);
			dup2(pipx->fd[pipx->cmd_ind - 1][0], 0);
		}
		else
			redir_in_out(pipx, STDIN_FILENO);
		if (pipx->els->next)
		{
			close(1);
			dup2(pipx->fd[pipx->cmd_ind][1], 1);
		}
		else
			redir_in_out(pipx, STDOUT_FILENO);
		close_all_fds(pipx);
		close(pipx->fds[0]);
		close(pipx->fds[1]);
		exit_no_err(pipx, exec_bin_pipe(pipx));
	}
}

static void	wait_children(t_pipx *pipx)
{
	int	i;

	i = 0;
	waitpid(pipx->pid, NULL, 0);
	while (i < pipx->n_els - 1)
	{
		wait(0);
		++i;
	}
}

void	exec_pipe(t_pipx *pipx)
{
	int	i;

	i = 0;
	while (i < pipx->n_els - 1)
	{
		if (pipe(pipx->fd[i]) == -1)
			exit_err_pipe(pipx, NULL, NULL);
		++i;
	}
	while (pipx->els)
	{
		exec_cmd_pipe(pipx);
		--pipx->n_els_left;
		++pipx->cmd_ind;
		pipx->els = pipx->els->next;
	}
	close_all_fds(pipx);
	dup2(pipx->fds[0], 0);
	dup2(pipx->fds[1], 1);
	close(pipx->fds[0]);
	close(pipx->fds[1]);
	wait_children(pipx);
}
