/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:27:12 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/24 19:33:09 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_object *ft_objat(t_object *head, int idx)
{
	int	i;

	i = 0;
	while (head)
	{
		if (idx == i || !head->next)
			return (head);
		i++;
		head = head->next;
	}
	printf("Should Never Be here\n");
	return NULL;
}