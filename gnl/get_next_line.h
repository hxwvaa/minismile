/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:15:59 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/25 18:26:28 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
// size_t	ft_strlen(const char *s);
// char	*ft_substr(char *s, unsigned int start, size_t len);
// char	*ft_strdup(const char *s);
// char	*ft_strjoin(const char *s1, const char *s2);
// char	*ft_strchr(const char *s, int c);

#endif
