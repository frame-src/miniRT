/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:13:05 by mawinter          #+#    #+#             */
/*   Updated: 2022/10/31 15:29:28 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define FD_SIZE 10240
# define BUFFER_SIZE 100
# include <stdio.h>
# include "fcntl.h"

int		get_idx_read(char *infobufd, int mode);
int		readnew(char *infobufd, char *buf, int fd);
int		setup(int *linelen, int fd, char **line);
char	*ft_bufjoin(char *line, int bufidx, char *buf, int linelen);
char	*join_line(char *infobufd, char *line, int *linelen);
char	*get_next_line(int fd);
#endif