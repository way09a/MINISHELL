/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:59 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:19 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_list **lst)
{
	t_list	*tmp;

	while ((*lst)->next)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
	free((*lst)->content);
	free(*lst);
}

void	free_and_exit(t_pipe *c, t_cmds *p)
{
	(void)p;
	if (c->m_env)
		free_list(&c->m_env);
	if (c->m_export)
		free_list(&c->m_export);
	if (c->tmp_env)
		free_strings(c->tmp_env);
	if (c->m_path != NULL)
		free_strings(c->m_path);
	free_all(c, p);
	exit(g_exit_code);
}

void	free_and_exit_2(t_pipe *c, t_cmds *p)
{
	(void)p;
	if (c->m_env)
		free_list(&c->m_env);
	if (c->m_export)
		free_list(&c->m_export);
	if (c->tmp_env)
		free_strings(c->tmp_env);
	if (c->m_path != NULL)
		free_strings(c->m_path);
}

void	ft_exit(t_pipe *c, t_cmds *p)
{
	if (p[0].cmd[1] && !p[0].cmd[2])
		g_exit_code = ft_atoi(p[0].cmd[1]);
	else if (p[0].cmd[1] && p[0].cmd[2])
	{
		ft_putendl_fd("too many arguments", 2);
		g_exit_code = 1;
		return ;
	}
	if (c->m_env)
		free_list(&c->m_env);
	if (c->m_export)
		free_list(&c->m_export);
	if (c->tmp_env)
		free_strings(c->tmp_env);
	if (c->m_path != NULL)
		free_strings(c->m_path);
	free_all(c, p);
	exit(g_exit_code);
}
