/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:54:10 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/01 00:06:04 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	counter(char const *s, char c)
{
	int	i;
	int	len;
	int	counter;

	counter = 0;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static int	ltr(const char *s, char c, int index)
{
	int	count;

	count = 0;
	while (0 <= index)
	{
		if (s[index] != c)
			count++;
		else
			return (count);
		index--;
	}
	return (count);
}

static int	free_all(char **arr, int idx, int maxcount)
{
	if (idx < 0)
		return (0);
	if (!arr[idx] && maxcount != idx + 1)
	{
		while (idx)
		{
			free(arr[idx]);
			idx--;
		}
		free(arr);
		return (1);
	}
	return (0);
}

int	free_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		len;
	int		strcount;
	int		allctr;

	if (s == NULL)
		return (NULL);
	allctr = 0;
	strcount = counter(s, c);
	i = -1;
	len = ft_strlen(s);
	arr = (char **)malloc(sizeof(char *) * (strcount + 1));
	if (arr == NULL)
		return (NULL);
	while (++i < len)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			arr[allctr++] = ft_substr(s, 1 + i - ltr(s, c, i), ltr(s, c, i));
		if (free_all(arr, allctr - 1, strcount))
			return (NULL);
	}
	arr[strcount] = NULL;
	return (arr);
}
