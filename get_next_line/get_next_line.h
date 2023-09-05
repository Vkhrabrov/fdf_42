/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:19:44 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/09/02 22:00:24 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

# include <stdlib.h>
# include <unistd.h>

size_t		ft_strlen_add(const char *c);
char		*ft_strchr_add(const char *str, int c);
char		*ft_strdup_add(const char *s1);
char		*ft_strjoin_add(char *s1, char *s2);
int			get_next_line(int fd, char **line);
size_t		ft_strlcpy_add(char *dest, const char *src, size_t dstsize);

#endif
