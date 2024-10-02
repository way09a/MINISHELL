/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:36:16 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/05 05:18:28 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strings(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		free(av[i]);
		av[i] = NULL;
		i++;
	}
	if (av)
	{
		free(av);
		av = NULL;
	}
}

void	free_helper(t_cmds *cmd, int i, int j)
{
	if (cmd[i].red_len > 0)
	{
		while (++j < cmd[i].red_len)
		{
			if (cmd[i].outs[j].file_name)
			{
				free(cmd[i].outs[j].file_name);
				cmd[i].outs[j].file_name = NULL;
			}
		}
		if (cmd[i].outs)
		{
			free(cmd[i].outs);
			cmd[i].outs = NULL;
		}
	}
}

void	free_all(t_pipe *pipe, t_cmds *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < pipe->cmd_len)
	{
		j = -1;
		free_helper(cmd, i, j);
		free_strings(cmd[i].cmd);
	}
	free_strings(pipe->cmds);
	pipe->cmds = NULL;
	free(cmd);
	cmd = NULL;
}
