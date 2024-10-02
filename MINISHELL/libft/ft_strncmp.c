/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:44:33 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/04 05:40:00 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

static int	cut_nl(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	compare(const unsigned char *s1, const unsigned char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i != n && s1[i] != '\0')
		return (s1[i]);
	else if (i != n && s2[i] != '\0')
		return (-s2[i]);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL)
		return (-1);
	if (*s1 == '\0' || *s2 == '\0')
		return (-1);
	if ((ft_strlen(s2) != (size_t)cut_nl(s1) && ft_strlen(s2) != 0) || n == 0)
		return (1);
	if (ft_strchr(s1, '\n') != NULL)
		return (compare((unsigned char *)s1, (unsigned char *)s2, n - 1));
	return (compare((unsigned char *)s1, (unsigned char *)s2, n));
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t			i;
// 	int				c;
// 	int				k;
// 	unsigned char	*ns1;
// 	unsigned char	*ns2;

// 	if (!s1 || !s2 || s1[0] == '\0' || s2[0] == '\0')
// 		return (-1);
// 	ns1 = (unsigned char *)s1;
// 	ns2 = (unsigned char *)s2;
// 	i = 0;
// 	c = ft_strlen(s1) - 1;
// 	k = ft_strlen(s2) - 1;
// 	if (k == 0 && cut_nl(s1) - 1 == 0)
// 	{
// 		if (ns1[c - 1] != ns2[k])
// 			return (ns1[c] - ns2[k]);
// 		else
// 			return (0);
// 	}
// 	if ((size_t)cut_nl(s1) != ft_strlen(s2))
// 		return (1);
// 	if (ft_strchr(s1, '\n'))
// 		c--;
// 	while (i < n && c >= 0 && k >= 0)
// 	{
// 		if (ns1[c] != ns2[k])
// 			return (ns1[c] - ns2[k]);
// 		i++;
// 		c--;
// 		k--;
// 	}
// 	if (i != n)
// 		return (ns1[c] - ns2[c]);
// 	return (0);
// }
