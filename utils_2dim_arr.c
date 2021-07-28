/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2dim_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:27:30 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/08 17:33:26 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	free_2dim_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}

int	count_els_2dim_arr(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr && arr[i])
		++i;
	return (i);
}

char	**copy_2dim_arr(t_pipx *pipx, char **arr)
{
	char	**cp_arr;
	int		i;

	cp_arr = NULL;
	i = 0;
	while (arr && arr[i])
		++i;
	cp_arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cp_arr)
		exit_err_malloc(pipx, NULL, NULL);
	i = 0;
	while (arr && arr[i])
	{
		cp_arr[i] = ft_strdup(arr[i]);
		if (!cp_arr[i])
			exit_err_malloc(pipx, NULL, NULL);
		++i;
	}
	cp_arr[i] = NULL;
	return (cp_arr);
}
