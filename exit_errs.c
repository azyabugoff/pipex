/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:41:14 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/08 22:29:51 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	exit_err_malloc(t_pipx *pipx, char **arr, char *str)
{
	free_pipx(pipx);
	free_2dim_arr(arr);
	if (str)
		free(str);
	ft_putstr_fd("Error.\nMalloc error.\n", 2);
	exit(1);
}

void	exit_err_pipe(t_pipx *pipx, char **arr, char *str)
{
	free_pipx(pipx);
	free_2dim_arr(arr);
	if (str)
		free(str);
	ft_putstr_fd("Error.\nPipe error.\n", 2);
	exit(1);
}

void	exit_err_text(t_pipx *pipx, char **arr, char *str, char *text)
{
	free_pipx(pipx);
	free_2dim_arr(arr);
	if (str)
		free(str);
	ft_putstr_fd(text, 2);
	exit(1);
}

void	exit_no_err(t_pipx *pipx, int ret)
{
	free_pipx(pipx);
	exit(ret);
}
