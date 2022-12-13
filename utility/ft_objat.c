/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:27:12 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 11:39:22 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_object	*ft_objat(t_object *head, int idx)
{
	int	i;

	i = 0;
	while (head)
	{
		if (idx == i)
			return (head);
		i++;
		head = head->next;
	}
	return (NULL);
}
