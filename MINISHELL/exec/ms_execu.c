/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:11:09 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/04 02:48:40 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_pipe *c, t_cmds *p, int i, int fd)
{
	(void)fd;
	c->tmp = NULL;
	c->tmpp = c->m_export;
	c->fd2 = check_input_redirect(p, c, 0, 0);
	c->fd1 = check_exec_rederict(p, c, 0, 0);
	if (c->fd1 == -1 || c->fd2 == -1)
	{
		g_exit_code = 1;
		return ;
	}
	c->j = 1;
	if (p[i].cmd[c->j])
		insert_the_node(p, c);
	else
		ex_helper(c, p);
	if (c->fd1 > 2)
		close(c->fd1);
}

void	helper_func(t_cmds *p, t_pipe *c, char *cmd)
{
	if ((!cmd && !p[0].cmd)
		|| (cmd == NULL && p[0].red_len > 0 && !p[0].cmd[0]))
		free_and_exit(c, p);
	else if (cmd == NULL && !p[0].cmd)
	{
		write(2, &p[0].cmd[0], ft_strlen(p[0].cmd[0]));
		write(2, "command not found :\n", 22);
		free_and_exit(c, p);
	}
}

void	ft_unset(t_cmds *p, int i, int fd, t_pipe *c)
{
	int	j;

	j = 0;
	(void)fd;
	c->fd2 = check_input_redirect(p, c, 0, 0);
	c->fd1 = check_exec_rederict(p, c, 0, 0);
	if (c->fd1 == -1 || c->fd2 == -1)
	{
		g_exit_code = 1;
		return ;
	}
	if (!p[i].cmd[j + 1])
		return ;
	unset_cmp(p, c->m_env, i, j);
	unset_cmp(p, c->m_export, i, j);
	c->env_count -= 1;
	if (c->fd1 > 2)
		close(c->fd1);
}

void	normal_exec(t_cmds *p, t_pipe *c)
{
	int		i;
	int		status;

	c->cmd_exec = check_command_existence(p[0].cmd[0], c->m_path);
	i = fork();
	signal(SIGINT, child_sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	if (i == 0)
		n_exec_he(p, c);
	waitpid(i, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_code = get_sig_status(WTERMSIG(status));
	free(c->cmd_exec);
}

void	ex_helper(t_pipe *c, t_cmds *p)
{
	while (c->tmpp)
	{
		if (p[0].red_len > 0)
			ft_putstr_fd(c->tmpp->content, c->fd1, 1);
		else
			printf("declare -x %s\n", (char *)c->tmpp->content);
		c->tmpp = c->tmpp->next;
	}
	g_exit_code = 0;
}
