/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:14:27 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/24 18:59:37 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_objadd_back(t_object **lst, t_object *new)
{
	t_object	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
