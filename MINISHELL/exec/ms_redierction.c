/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redierction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 06:50:12 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/05 05:15:09 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_func(t_cmds *p, t_vars *v, int j, int pm)
{
	if (p[j].outs[v->i].flag == 1)
	{
		v->fd = open(p[j].outs[v->i].file_name, O_WRONLY | \
			O_CREAT | O_TRUNC, 0644);
		if (v->fd < 0)
		{
			perror("open");
			g_exit_code = 1;
			return (1 - 2 * (pm == 1));
		}
	}
	else if (p[j].outs[v->i].flag == 2)
	{
		v->fd = open(p[j].outs[v->i].file_name, O_WRONLY | \
			O_CREAT | O_APPEND, 0644);
		if (v->fd < 0)
		{
			perror("open");
			g_exit_code = 1;
			return (-1);
		}
	}
	return (0);
}

int	check_exec_rederict(t_cmds *p, t_pipe *c, int pm, int j)
{
	t_vars	v;

	v.i = 0;
	v.fd = 0;
	c->fd1 = 0;
	(void)pm;
	while (v.i < p[j].red_len)
	{
		if (my_func(p, &v, j, pm) == -1)
			free_and_exit(c, p);
		else if (my_func(p, &v, j, pm) == 1)
			return (-1);
		if (v.i == p[j].red_len - 1)
			return (v.fd);
		if ((p[j].outs[v.i].flag == 1 && p[j].outs[v.i + 1].flag != 1) && \
			(p[j].outs[v.i].flag == 1 && p[j].outs[v.i + 1].flag != 2))
		{
			if (v.fd == 0)
				return (0);
			return (v.fd);
		}
		v.i++;
		close(v.fd);
	}
	return (0);
}

void	write_in_fd(t_cmds *p, int x, int y, t_pipe *c)
{
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (p[x].cmd[y])
	{
		i = 0;
		if (k != 0)
			write(c->fd1, " ", 1);
		while (p[x].cmd[y][i])
		{
			write(c->fd1, &p[x].cmd[y][i], 1);
			i++;
		}
		y++;
		k++;
	}
}

int	check_input_redirect(t_cmds *p, t_pipe *c, int pm, int j)
{
	c->i = 0;
	c->fd1 = 0;
	while (c->i < p[j].red_len)
	{
		if (p[j].outs[c->i].flag == 0)
		{
			c->fd1 = open(p[c->j].outs[c->i].file_name, O_RDONLY, 0644);
			if (c->fd1 < 0)
			{
				perror("open");
				g_exit_code = 1;
				if (pm == 1)
					free_and_exit(c, p);
				else
					return (-1);
			}
		}
		if (c->i == p[j].red_len - 1)
			return (c->fd1);
		if (p[j].outs[c->i++ + 1].flag != 0)
			return (heredoc_condition(c->fd1));
		if (c->fd1 > 2)
			close(c->fd1);
	}
	return (0);
}
