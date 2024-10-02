/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 01:18:17 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_red(t_cmds *p, t_pipe *c)
{
	c->t = 0;
	if (input_check(p, c) == 1)
	{
		if (check_heredoc(p, c) == 1)
			exec_heredoc(p, c, 0);
		c->t = check_input_redirect(p, c, 1, 0);
		if (c->t > 2)
		{
			if (dup2(c->t, STDIN_FILENO) == -1)
			{
				printf("kkkk\n");
				exit(EXIT_FAILURE);
			}
			close(c->t);
		}
	}
}

void	output_red(t_cmds *p, t_pipe *c, char *cmd)
{
	if (output_check(p, c) == 1)
	{
		c->fd2 = check_exec_rederict(p, c, 1, 0);
		printf("c = %d\n", c->fd2);
		if (c->fd2 > 2)
		{
			if (cmd)
			{
				if (dup2(c->fd2, STDOUT_FILENO) == -1)
				{
					printf("same shit\n");
					exit(EXIT_FAILURE);
				}
				close(c->fd2);
			}
		}
		return ;
	}
	helper_func(p, c, cmd);
}

void	echo_new_line(t_cmds *p, int x, int y, t_pipe *c)
{
	while (p[x].cmd[y])
	{
		if (p[x].red_len == 0)
		{
			printf("%s", p[x].cmd[y]);
			if (p[x].cmd[y + 1])
				printf(" ");
		}
		else
		{
			write_in_fd(p, x, y, c);
			write(c->fd1, "\n", 1);
			close(c->fd1);
			return ;
		}
		y++;
	}
	printf("\n");
}

void	echo_flag(t_cmds *p, int x, int y, t_pipe *c)
{
	y += 1;
	if (!p[x].cmd[y])
		return ;
	while (p[x].cmd[y + 1])
	{
		if (c->fd1 > 2)
		{
			write_in_fd(p, x, y, c);
			close(c->fd1);
			return ;
		}
		else
			printf("%s ", p[x].cmd[y]);
		y++;
	}
	if (c->fd1 > 2)
	{
		write_in_fd(p, x, y, c);
		close(c->fd1);
		return ;
	}
	else
		printf("%s", p[x].cmd[y]);
}

int	heredoc_condition(int fd)
{
	if (fd == 0)
		return (0);
	return (fd);
}
