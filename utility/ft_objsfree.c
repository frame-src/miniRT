/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objsfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:45:40 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/25 11:04:03 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_objsfree(t_object *lst)
{
	t_object *tmp;

	while (lst)
	{
		free(lst->cylinder);
		free(lst->plane);
		free(lst->sphere);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	return (1);
}
