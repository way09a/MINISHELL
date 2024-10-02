/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:46:46 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:19 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closing_fds(t_pipe *c)
{
	close(c->fd[0][0]);
	close(c->fd[0][1]);
	close(c->fd[1][0]);
	close(c->fd[1][1]);
}

void	close_first_pipe(t_cmds *p, t_pipe *c)
{
	close(c->fd[0][0]);
	close(c->fd[0][1]);
	if (c->j == p->cmd_len - 1)
	{
		close(c->fd[1][1]);
		close(c->fd[1][0]);
	}
}

void	close_second_pipe(t_pipe *c)
{
	close(c->fd[1][0]);
	close(c->fd[1][1]);
	c->i = 0;
}
