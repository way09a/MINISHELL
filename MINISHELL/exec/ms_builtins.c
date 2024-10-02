/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:27:44 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmds *p, int x, int y, t_pipe *c)
{
	y += 1;
	c->fd2 = check_input_redirect(p, c, 0, x);
	c->fd1 = check_exec_rederict(p, c, 0, x);
	if (c->fd1 == -1 || c->fd2 == -1)
		return ;
	if (!p[x].cmd[y] || !p[x].cmd[y][0])
	{
		if (c->fd1 > 2)
		{
			write(c->fd1, "\n", 1);
			close(c->fd1);
		}
		else
			printf("\n");
	}
	else if (check_for_flag(p[x].cmd[y]) && !p[x].cmd[y - 1][4])
		echo_new_line(p, x, y, c);
	else if (check_for_flag(p[x].cmd[y]) == 0)
		echo_flag(p, x, y, c);
	g_exit_code = 0;
}

void	int_pwd(t_cmds *p, t_pipe *c)
{
	c->fd2 = check_input_redirect(p, c, 0, 0);
	c->fd1 = check_exec_rederict(p, c, 0, 0);
	if (c->fd1 == -1 || c->fd2 == -1)
	{
		g_exit_code = 1;
		return ;
	}
}

void	ft_pwd(t_cmds *p, t_pipe *c, int fd)
{
	char	*pwd;

	(void)fd;
	pwd = NULL;
	int_pwd(p, c);
	pwd = getcwd(p[0].cmd[1], 1024);
	if (pwd != NULL)
	{
		if (c->fd1 > 2)
		{
			ft_putstr_fd(pwd, c->fd1, 1);
			close(c->fd2);
		}
		else
			printf("%s\n", pwd);
	}
	else
	{
		perror("pwd");
		g_exit_code = 1;
	}
	g_exit_code = 0;
}

void	ft_env(t_cmds *p, t_pipe *c, int fd)
{
	t_list	*tmp;

	(void)p;
	(void)c;
	tmp = c->m_env;
	c->fd2 = check_input_redirect(p, c, 0, 0);
	c->fd1 = check_exec_rederict(p, c, 0, 0);
	if (c->fd1 == -1 || c->fd2 == -1)
	{
		g_exit_code = 1;
		return ;
	}
	while (tmp)
	{
		if (fd > 2)
			ft_putstr_fd(tmp->content, fd, 1);
		else if (p[0].red_len > 0)
			ft_putstr_fd(tmp->content, c->fd1, 1);
		else
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	if (c->fd1 > 2)
		close(c->fd1);
	g_exit_code = 0;
}

void	ft_cd(t_cmds *p, int x, int y, t_pipe *c)
{
	(void)c;
	y += 1;
	c->fd2 = check_input_redirect(p, c, 0, 0);
	c->fd1 = check_exec_rederict(p, c, 0, 0);
	if (c->fd1 == -1 || c->fd2 == -1)
	{
		g_exit_code = 1;
		return ;
	}
	update_pwd(c, getcwd(NULL, 1024), "OLDPWD", 1);
	update_export(c, getcwd(NULL, 1024), "OLDPWD", 1);
	if (chdir(p[x].cmd[y]) < 0)
	{
		printf("%s: No such file or directory\n", p[x].cmd[y]);
		g_exit_code = 1;
	}
	else
		g_exit_code = 0;
	if (c->fd1 > 2)
		close(c->fd1);
	update_pwd(c, getcwd(NULL, 1024), "PWD", 0);
	update_export(c, getcwd(NULL, 1024), "PWD", 0);
}
