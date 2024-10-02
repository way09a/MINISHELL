/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 04:10:18 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/04 04:10:37 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	changing_the_env_v(t_cmds *p, int i, int j, t_pipe *c)
{
	t_vars	v;

	v.k = 0;
	v.tmp = c->m_env;
	v.tmp2 = v.tmp;
	v.tmp3 = NULL;
	ch_the_env(p, i, j, &v);
	if (v.tmp2->content != v.tmp->content)
		v.tmp2->next = v.tmp3;
	if (v.k == 0)
	{
		c->m_export = v.tmp3;
		free(v.tmp->content);
		free(v.tmp);
	}
}

void	unset_cmp(t_cmds *p, t_list *lst, int i, int j)
{
	t_list	*tmp3;
	t_list	*tmp2;
	t_list	*tmp;

	tmp = lst;
	tmp2 = tmp;
	while (tmp)
	{
		if (strncmp_orginal(tmp->content, p[i].cmd[j + 1],
				len_till_equal(p[i].cmd[j + 1])) == 0)
		{
			tmp3 = tmp->next;
			tmp2->next = tmp3;
			free(tmp->content);
			free(tmp);
			return ;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}
