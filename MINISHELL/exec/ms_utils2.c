/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:36:08 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_env(t_pipe *p, char **envp)
{
	int		i;

	i = 0;
	p->m_env = NULL;
	if (!envp[0])
	{
		write(2, "don't play with me(env -i)\n", 27);
		exit(1);
	}
	while (envp[i])
	{
		ft_lstadd_back(&p->m_env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	p->env_count = i;
}

void	fill_export(t_pipe *c)
{
	int		i;
	t_list	*tmp;
	int		index;

	i = 0;
	c->m_export = NULL;
	tmp = c->m_env;
	index = c->env_count;
	fill_tmp_env(c);
	while (tmp->next)
	{
		index = found_first(c->tmp_env, index, c);
		ft_lstadd_front(&c->m_export,
			ft_lstnew(ft_strdup(env_index(index, c->m_env))));
		c->tmp_env[index][0] = '0';
		tmp = tmp->next;
		if (!tmp)
			break ;
		i++;
	}
	last_sorting(c);
}

void	update_env(t_pipe *c)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = c->m_env;
	free_strings(c->tmp_env);
	c->tmp_env = malloc((c->env_count + 1) * sizeof(char *));
	while (tmp)
	{
		c->tmp_env[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	c->tmp_env[i] = NULL;
}
