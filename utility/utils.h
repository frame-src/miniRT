/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:13:05 by mawinter          #+#    #+#             */
/*   Updated: 2022/10/31 23:47:46 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 15
# include <stdio.h>
# include "fcntl.h"

/* 						getnextline						*/
int				get_idx_read(char *infobufd, int mode);
int				readnew(char *infobufd, char *buf, int fd);
int				setup(int *linelen, int fd, char **line);
char			*ft_bufjoin(char *line, int bufidx, char *buf, int linelen);
char			*join_line(char *infobufd, char *line, int *linelen);
char			*get_next_line(int fd);

/*						Libft							*/

int				ft_strcmp(const char *s1, const char *s2);
int				ft_strlen(const char *s);
int				ft_isalpha(int c);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, int start, int len);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int             ft_isdigit(int c);
int				free_split(char **splitted);
int				free_1(void *ptr);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memset(void *s, int c, size_t n);
int				free_split_void(void **splitted);
#endif