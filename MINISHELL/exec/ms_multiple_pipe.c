/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:00:16 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	c->fd2 = check_input_redirect(p, c, 1, v->j);
	if (c->fd2 > 2)
	{
		if (dup2(c->fd2, STDIN_FILENO) == -1)
			exit(0);
		close(c->fd2);
	}
	if (dup2(c->fd[0][1], STDOUT_FILENO) == -1)
		exit(0);
	close(c->fd[0][1]);
	close(c->fd[0][0]);
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

void	secon_hh(t_pipe *c, t_vars *v)
{
	if (v->i % 2 == 0 && v->j == 1)
	{
		if (dup2(c->fd[0][0], STDIN_FILENO) == -1)
			exit(0);
		closing_fds(c);
	}
	else if (v->i % 2 == 1)
	{
		if (dup2(c->fd[0][0], STDIN_FILENO) == -1)
			exit(0);
		close(c->fd[0][1]);
		close(c->fd[0][0]);
	}
	else
	{
		if (dup2(c->fd[1][0], STDIN_FILENO) == -1)
			exit(0);
		close(c->fd[1][1]);
		close(c->fd[1][0]);
	}
}

void	second_cmd(t_pipe *c, t_vars *v)
{
	if (c->fd2 > 2)
	{
		if (dup2(c->fd2, STDIN_FILENO) == -1)
			exit(0);
		close(c->fd2);
	}
	else
	{
		secon_hh(c, v);
	}
}

void	third2_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	c->fd2 = check_input_redirect(p, c, 1, v->j);
	second_cmd(c, v);
	if (builtins_pipes(p, c, c->fd[0][1], v->j) == 0)
		exit(0);
	c->fd1 = check_exec_rederict(p, c, 1, v->j);
	if (c->fd1 > 2)
	{
		if (dup2(c->fd1, STDOUT_FILENO) == -1)
		{
			printf("same shit\n");
			exit(0);
		}
		close(c->fd1);
	}
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

void	f_helper(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (c->fd2 > 2)
	{
		if (dup2(c->fd2, STDIN_FILENO) == -1)
			exit(0);
		close(c->fd2);
	}
	else
	{
		if (dup2(c->fd[0][0], STDIN_FILENO) == -1)
			exit(0);
	}
	c->fd2 = check_exec_rederict(p, c, 1, v->j);
	if (c->fd2 > 2)
	{
		if (dup2(c->fd2, STDOUT_FILENO) == -1)
			exit(0);
		close(c->fd2);
	}
	else
	{
		if (dup2(c->fd[1][1], STDOUT_FILENO) == -1)
			exit(0);
	}
}
