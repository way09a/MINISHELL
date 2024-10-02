/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:14:04 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	h_add_to_ex(t_cmds *p, t_pipe *c, int i, int j)
{
	c->tmp2 = ft_lstnew(ft_strdup(p[0].cmd[j]));
	c->tmp2->next = c->tmpp;
	if (i != 0)
		c->tmp3->next = c->tmp2;
	c->env_count += 1;
	ft_lstadd_back(&c->m_env, ft_lstnew(ft_strdup(p[0].cmd[j])));
	if (i == 0)
		c->m_export = c->tmp2;
}

void	h_add2(t_cmds *p, t_pipe *c, int j)
{
	ft_lstadd_back(&c->m_export, ft_lstnew(ft_strdup(p[0].cmd[j])));
	ft_lstadd_back(&c->m_env, ft_lstnew(ft_strdup(p[0].cmd[j])));
	c->env_count += 1;
}

void	add_to_export(t_cmds *p, t_pipe *c, int i, int j)
{
	c->tmp2 = NULL;
	c->tmpp = c->m_export;
	c->tmp3 = c->tmpp;
	if (check_if_exist(p, i, j, c) == 0 && check_for_equal(p, i, j) == 0)
		return ;
	else if (check_if_exist(p, i, j, c) == 0 && check_for_equal(p, i, j) == 1)
		return (changing_the_value(p, i, j, c), changing_the_env_v(p, i, j, c));
	if (strncmp_orginal(p[0].cmd[j], "=", 1) != 0)
	{
		while (c->tmpp)
		{
			if (strncmp_orginal(c->tmpp->content, p[0].cmd[j], \
				ft_strlen(c->tmpp->content)) > 0)
			{
				h_add_to_ex(p, c, i, j);
				break ;
			}
			c->tmp3 = c->tmpp;
			c->tmpp = c->tmpp->next;
			i++;
		}
		if (!c->tmpp)
			h_add2(p, c, j);
	}
}

void	insert_the_node(t_cmds *p, t_pipe *c)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (p[i].cmd[j])
	{
		if (ft_strncmp(p[i].cmd[j], "=", 1) != 0
			&& ft_isexportable(p[i].cmd[j], len_till_equal(p[i].cmd[j])) == 0)
			add_to_export(p, c, i, j);
		else if (ft_isexportable(p[i].cmd[j], len_till_equal(p[i].cmd[j])) == 1 \
			|| ft_strncmp(p[i].cmd[j], "=", 1) == 0)
		{
			write (2, p[i].cmd[j], ft_strlen(p[i].cmd[j]));
			write(2, ": not a valid identifier\n", 25);
			g_exit_code = 1;
		}
		j++;
	}
}

int	check_if_exist(t_cmds *p, int i, int j, t_pipe *c)
{
	int		len;
	t_list	*t_e;

	len = len_till_equal(p[i].cmd[j]);
	t_e = c->m_export;
	while (t_e)
	{
		if (strncmp_orginal(t_e->content, p[i].cmd[j], len) == 0)
			return (0);
		t_e = t_e->next;
	}
	return (1);
}
