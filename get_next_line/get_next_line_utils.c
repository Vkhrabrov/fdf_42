/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:19:35 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/09/02 23:41:35 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*true_free(char **ptr);

size_t	ft_strlen_add(const char *c)
{
	size_t	i;

	if (!c)
		return (0);
	i = 0;
	while (*c)
	{
		i++;
		c++;
	}
	return (i);
}

size_t	ft_strlcpy_add(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;

	n = 0;
	while (src[n] != '\0')
		n++;
	i = 0;
	if (dstsize < 1)
		return (n);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (n);
}

char	*ft_strchr_add(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strdup_add(const char *s1)
{
	char	*s2;
	size_t	i;

	i = ft_strlen_add(s1) + 1;
	s2 = (char *)malloc(i);
	if (s2 == NULL)
		return (s2);
	if (s1 != NULL)
		ft_strlcpy_add(s2, s1, i);
	return (s2);
}

char	*ft_strjoin_add(char *s1, char *s2)
{
	char	*s3;
	ssize_t	iter;
	ssize_t	iter2;

	iter = -1;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	iter2 = ft_strlen_add(s1);
	s3 = malloc(sizeof(char) * (iter2 + ft_strlen_add(s2) + 1));
	if (!s3)
		return (true_free(&s1));
	while (s1[++iter] != '\0')
		s3[iter] = s1[iter];
	iter = -1;
	while (s2[++iter] != '\0')
		s3[iter2 + iter] = s2[iter];
	s3[iter2 + iter] = '\0';
	free(s1);
	return (s3);
}
