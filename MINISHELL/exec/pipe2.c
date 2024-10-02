/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 03:02:10 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/05 05:16:16 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fourth_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
	if (p[v->j].red_len > 0)
	{
		c->fd2 = check_input_redirect(p, c, 1, v->j);
		f_helper(c, p, v);
	}
	else
	{
		if (dup2(c->fd[0][0], STDIN_FILENO) == -1)
			exit(0);
		if (dup2(c->fd[1][1], STDOUT_FILENO) == -1)
			exit(0);
		close(c->fd[0][0]);
		close(c->fd[1][1]);
	}
}

void	fifth_cmd(t_pipe *c, t_cmds *p, t_vars *v)
{
		c->fd2 = check_input_redirect(p, c, 1, v->j);
	if (c->fd2 > 2)
	{
		if (dup2(c->fd2, STDIN_FILENO) == -1)
			exit(0);
		close(c->fd2);
	}
	else
	{
		if (dup2(c->fd[1][0], STDIN_FILENO) == -1)
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
		if (dup2(c->fd[0][1], STDOUT_FILENO) == -1)
			exit(0);
	}
}

int	len_till_equal(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	check_for_flag(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == 'n')
			j++;
		else
			return (1);
		i++;
	}
	return (0);
}

int	count_cmds(char ***str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
