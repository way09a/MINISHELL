/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:52:45 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/07 05:44:03 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_code = 0;

void	clean_quotes(char *str)
{
	int	i;
	int	j;
	int	quote;

	j = 0;
	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

int	ms_main_helper(t_pipe *pipe, t_cmds *cmds, char *read)
{
	if (is_space(read))
		return (1);
	if (!check_redirect(read))
	{
		printf("syntax error near unexpected token \n");
		add_history(read);
		g_exit_code = 258;
		return (1);
	}
	else if (!check_pipes(pipe, read, cmds))
	{
		printf("Error\n");
		add_history(read);
		g_exit_code = 258;
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipe;
	t_cmds	*cmds;
	char	*read;

	cmds = NULL;
	(void)av;
	if (ac != 1)
		return (0);
	get_env(&pipe, envp);
	fill_export(&pipe);
	g_exit_code = 0;
	pipe.m_path = NULL;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		read = readline("minishell$ ");
		if (!read)
			return (free_and_exit_2(&pipe, cmds), printf("exit\n"), 0);
		if (ms_main_helper(&pipe, cmds, read))
			continue ;
		files_saving(&pipe, &cmds);
		ms_exec(cmds, &pipe);
		add_history(read);
	}
}
