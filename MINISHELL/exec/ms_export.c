/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:04:59 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_equal(t_cmds *p, int i, int j)
{
	int		k;

	k = 0;
	while (p[i].cmd[j][k])
	{
		if (p[i].cmd[j][k] == '=')
			return (1);
		k++;
	}
	return (0);
}

void	ch_t_val(t_cmds *p, int i, int j, t_vars *v)
{
	while (v->tmp)
	{
		if (strncmp_orginal(v->tmp->content, p[i].cmd[j],
				len_till_equal(p[i].cmd[j])) == 0)
		{
			v->tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
			v->tmp3->next = v->tmp->next;
			if (v->tmp2->content != v->tmp->content)
				v->tmp2->next = v->tmp3;
			break ;
		}
		v->tmp2 = v->tmp;
		v->tmp = v->tmp->next;
		v->k++;
	}
}

void	changing_the_value(t_cmds *p, int i, int j, t_pipe *c)
{
	t_vars	v;

	v.k = 0;
	v.tmp = c->m_export;
	v.tmp2 = v.tmp;
	v.tmp3 = NULL;
	ch_t_val(p, i, j, &v);
	if (v.tmp2->content != v.tmp->content)
		v.tmp2->next = v.tmp3;
	if (v.k == 0)
	{
		c->m_export = v.tmp3;
		free(v.tmp->content);
		free(v.tmp);
	}
}

char	*env_index(int index, t_list *env)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = env;
	while (i < index && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp)
		return (tmp->content);
	else
		return (NULL);
}

void	ch_the_env(t_cmds *p, int i, int j, t_vars *v)
{
	while (v->tmp)
	{
		if (strncmp_orginal(v->tmp->content, p[i].cmd[j],
				len_till_equal(p[i].cmd[j])) == 0)
		{
			v->tmp3 = ft_lstnew(ft_strdup(p[i].cmd[j]));
			v->tmp3->next = v->tmp->next;
			if (v->tmp2->content != v->tmp->content)
				v->tmp2->next = v->tmp3;
			break ;
		}
		v->tmp2 = v->tmp;
		v->tmp = v->tmp->next;
		v->k++;
	}
}
