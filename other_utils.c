/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:38:35 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/08 21:02:59 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	malloc_fds(t_pipx *pipx, int n_els, int i, int tmp)
{
	pipx->fd = (int **)malloc(sizeof(int *) * (n_els - 1));
	if (!pipx->fd)
		exit_err_malloc(pipx, NULL, NULL);
	while (i < n_els - 1)
	{
		pipx->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipx->fd[i])
		{
			tmp = 0;
			while (tmp < i)
			{
				free(pipx->fd[tmp]);
				++tmp;
			}
			free(pipx->fd);
			pipx->fd = NULL;
			exit_err_malloc(pipx, NULL, NULL);
		}
		pipx->fd[i][0] = -1;
		pipx->fd[i][1] = -1;
		++i;
	}
}

static char	*parse_env_val(t_pipx *pipx, int i, int j, char *var_to_free)
{
	char	*val;

	free(var_to_free);
	val = NULL;
	if (pipx->envs[i][j + 1] == '\0')
	{
		val = ft_strdup("\0");
		if (!val)
			exit_err_malloc(pipx, NULL, NULL);
	}
	else
	{
		val = ft_substr(pipx->envs[i], j + 1, ft_strlen(pipx->envs[i]) - j - 1);
		if (!val)
			exit_err_malloc(pipx, NULL, NULL);
	}
	return (val);
}

char	*get_env(t_pipx *pipx, char *name)
{
	int		i;
	int		j;
	char	*name1;

	i = 0;
	j = 0;
	name1 = NULL;
	while (pipx->envs && pipx->envs[i])
	{
		j = 0;
		while (pipx->envs[i][j] && pipx->envs[i][j] != '=')
			++j;
		if (j < (int)ft_strlen(pipx->envs[i]))
		{
			name1 = ft_substr(pipx->envs[i], 0, j);
			if (!name1)
				exit_err_malloc(pipx, NULL, NULL);
			if (!ft_strcmp(name1, name))
				return (parse_env_val(pipx, i, j, name1));
			free(name1);
			name1 = NULL;
		}
		++i;
	}
	return (NULL);
}

t_els	*last_el(t_els *el)
{
	if (el)
	{
		while (el->next)
			el = el->next;
		return (el);
	}
	return (NULL);
}

void	pipx_push_el(t_pipx *pipx, char **args)
{
	t_els	*el;
	t_els	*neww;

	el = NULL;
	neww = (t_els *)malloc(sizeof(t_els));
	if (!neww)
		exit_err_malloc(pipx, NULL, NULL);
	neww->args = copy_2dim_arr(pipx, args);
	neww->next = NULL;
	if (pipx->els)
	{
		el = last_el(pipx->els);
		el->next = neww;
		neww->next = NULL;
	}
	else
	{
		pipx->els = neww;
		neww->next = NULL;
	}
}
