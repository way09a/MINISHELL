/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:12:58 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:19 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(t_pipe *c, char *str, char *p, int k)
{
	c->tmpp = c->m_env;
	while (c->tmpp)
	{
		if (strncmp_orginal(p, c->tmpp->content, \
			len_till_equal(c->tmpp->content)) == 0)
		{
			free(c->tmpp->content);
			if (k == 0)
				c->tmpp->content = ft_strjoin("PWD=", str);
			else
				c->tmpp->content = ft_strjoin("OLDPWD=", str);
			break ;
		}
		c->tmpp = c->tmpp->next;
	}
	free(str);
}

void	update_export(t_pipe *c, char *str, char *p, int k)
{
	c->tmpp = c->m_export;
	while (c->tmpp)
	{
		if (strncmp_orginal(p, c->tmpp->content, \
			len_till_equal(c->tmpp->content)) == 0)
		{
			free(c->tmpp->content);
			if (k == 0)
				c->tmpp->content = ft_strjoin("PWD=", str);
			else
				c->tmpp->content = ft_strjoin("OLDPWD=", str);
			break ;
		}
		c->tmpp = c->tmpp->next;
	}
	free(str);
}
