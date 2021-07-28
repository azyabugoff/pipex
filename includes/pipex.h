/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:37:45 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/09 19:27:00 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "stdio.h"
# include <string.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_els
{
	char			**args;
	struct s_els	*next;
}	t_els;

typedef struct s_pipx
{
	int		fds[2];
	char	**envs;
	pid_t	pid;
	int		n_els;
	int		n_els_left;
	t_els	*start_el;
	t_els	*els;
	int		**fd;
	int		cmd_ind;
	char	*infile;
	char	*outfile;
}	t_pipx;

void			parse_pipx(t_pipx *pipx, char **argv);
void			exit_err_malloc(t_pipx *pipx, char **arr, char *str);
void			exit_err_pipe(t_pipx *pipx, char **arr, char *str);
void			exit_err_text(t_pipx *pipx, char **arr, char *str, char *text);
void			exit_no_err(t_pipx *pipx, int ret);
void			free_2dim_arr(char **arr);
int				count_els_2dim_arr(char **arr);
char			**copy_2dim_arr(t_pipx *pipx, char **arr);
char			*get_env(t_pipx *pipx, char *name);
t_els			*last_el(t_els *el);
void			pipx_push_el(t_pipx *pipx, char **args);
void			malloc_fds(t_pipx *pipx, int n_els, int i, int tmp);
void			close_all_fds(t_pipx *pipx);
void			free_els_list(t_pipx *pipx);
void			free_fds_arr(t_pipx *pipx);
void			free_pipx(t_pipx *pipx);
void			exec_pipe(t_pipx *pipx);
int				exec_bin_pipe(t_pipx *pipx);

#endif
