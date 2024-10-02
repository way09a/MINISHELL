/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:52:23 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/04 02:52:59 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sixth_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	closing_fds(c);
	if (builtins_pipes(p, c, c->fd[0][1], v->j) == 0)
		exit(0);
	c->cmd_exec = check_command_existence(p[v->j].cmd[0], c->m_path);
	if (execve(c->cmd_exec, p[v->j].cmd, NULL) < 0)
	{
		write(2, p[v->j].cmd[0], ft_strlen(p[v->j].cmd[0]));
		write(2, ": command not found\n", 21);
		free(c->cmd_exec);
		closing_fds(c);
		g_exit_code = 127;
		free_and_exit(c, p);
	}
}

void	closing_pipe(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (v->i % 2 == 1 && v->i != 0)
	{
		close(c->fd[0][0]);
		close(c->fd[0][1]);
		if (v->j == p->cmd_len - 1)
		{
			close(c->fd[1][1]);
			close(c->fd[1][0]);
		}
		v->i = -1;
	}
	else if (v->i % 2 == 0 && v->j != 0)
	{
		close(c->fd[1][0]);
		close(c->fd[1][1]);
		v->i = 0;
	}
}

void	before_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (c->pid == 0)
	{
		if (v->j == 0)
			first_cmd(c, p, v);
		else if (v->j == p->cmd_len - 1)
			third2_cmd(c, p, v);
		else
		{
			if (v->i % 2 == 1)
				fourth_cmd(c, p, v);
			else
				fifth_cmd(c, p, v);
			sixth_cmd(c, p, v);
		}
	}
}

void	init1(t_vars *v)
{
	v->i = 0;
	v->j = 0;
	v->h = 0;
	v->i = 0;
}

void	multiple_pipes(t_cmds *p, t_pipe *c)
{
	t_vars	v;

	init1(&v);
	c->cmd_exec = NULL;
	while (v.j < p->cmd_len)
	{
		if (v.i % 2 == 0 || v.i == 0)
			pipe(c->fd[0]);
		else if (v.i % 2 == 1)
			pipe(c->fd[1]);
		if (check_heredoc(p, c) == 1)
			exec_heredoc(p, c, v.j);
		c->pid = fork();
		before_cmd(c, p, &v);
		closing_pipe(c, p, &v);
		v.i++;
		v.j++;
	}
	v.h = 0;
	closing_fds(c);
	while (v.h < p->cmd_len)
	{
		wait(NULL);
		v.h++;
	}
}
