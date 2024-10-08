/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:45:07 by ahussein          #+#    #+#             */
/*   Updated: 2023/04/04 05:45:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*rest_less(char *buf, int j)
{
	int		len;
	char	*tmp;

	if (buf == NULL || !buf)
		return (NULL);
	if (buf[0] == '\n')
		j--;
	tmp = malloc(j + 1);
	if (!tmp)
		return (NULL);
	len = 0;
	while (len < j)
	{
		tmp[len] = buf[len];
		len++;
	}
	tmp[len] = '\0';
	return (tmp);
}

char	*handle(char *buf, int j)
{
	int		len;
	char	*tmp;
	int		i;

	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (buf[i] == '\n')
		i++;
	tmp = malloc(j - i + 1);
	if (!tmp)
		return (NULL);
	len = 0;
	while (len < j - i)
	{
		tmp[len] = buf[len + 1];
		len++;
	}
	tmp[len] = '\0';
	return (tmp);
}

char	*saving(char *buf, int d)
{
	char		*str1;
	int			i;
	size_t		j;

	i = 0;
	if (!buf)
		return (NULL);
	j = ft_strlen_and_ft_strchr(buf, 0, 1);
	while (buf[i] && buf[i] != '\n')
		i++;
	if ((!buf[i]) || (i + 1 == d && buf[i] == '\n'))
		return (NULL);
	if (buf[0] == '\n' && buf[i + 1])
		return (handle(buf, d));
	i++;
	str1 = malloc(j - i + 1);
	j = 0;
	if (!buf[0] || !str1)
		return (free(str1), NULL);
	while (buf[i] != '\0')
		str1[j++] = buf[i++];
	str1[j] = '\0';
	if (*str1 == '\0')
		return (free(str1), NULL);
	return (str1);
}

char	*reading_loop(char *tmp, char *str, char **buf, int fd)
{
	int	j;

	j = 0;
	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	j = read(fd, tmp, BUFFER_SIZE);
	if (j <= -1)
		return (free(str), free(tmp), NULL);
	tmp[j] = '\0';
	while (j > 0)
	{
		str = joining(str, tmp, j);
		if (ft_strlen_and_ft_strchr(tmp, '\n', 0) != 0)
		{
			*buf = saving(tmp, j);
			return (free(tmp), str);
		}
		j = read(fd, tmp, BUFFER_SIZE);
	}
	if ((j == 0 && *tmp != '\0'))
		return (free(tmp), str);
	else if (j == 0 && *tmp == '\0' && str == NULL && buf == NULL)
		return (free(tmp), free(str), free(buf), NULL);
	return (free(tmp), str);
}

char	*get_next_line(int fd)
{
	t_rvars			vars;
	static char		*buf;

	vars.str = NULL;
	vars.tmp = NULL;
	vars.n_pos = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf)
	{
		vars.str = joining(vars.str, buf, 1);
		if (ft_strlen_and_ft_strchr(buf, '\n', 0) != 0)
		{
			vars.tmp = buf;
			while (buf[vars.n_pos] && buf[vars.n_pos] != '\n')
				++vars.n_pos;
			vars.n_pos += (buf[vars.n_pos] == '\n');
			buf = ft_strdup_get(&(buf[vars.n_pos]));
			return (free(vars.tmp), vars.str);
		}
		if (!check_eof(&vars.str, &buf, NULL, -1) && buf == NULL)
			return (NULL);
	}
	vars.str = reading_loop(vars.tmp, vars.str, &buf, fd);
	return (free(vars.tmp), vars.str);
}
