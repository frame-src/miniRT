/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:15:07 by mawinter          #+#    #+#             */
/*   Updated: 2022/10/28 14:29:50 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*newstring;
	int		i;
	int		slen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (len > slen)
		len = slen;
	if (start >= ft_strlen(s))
		return ((char *)ft_calloc(sizeof(char), 1));
	i = -1;
	newstring = (char *)malloc((len + 1) * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	while (++i < len && s[i + start] != '\0')
		newstring[i] = s[i + start];
	newstring[i] = '\0';
	return (newstring);
}
