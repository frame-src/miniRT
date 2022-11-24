/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:59:37 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/24 20:25:07 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_object	*ft_objnew()
{
	t_object	*newnode;

	newnode = ft_calloc(1, sizeof(t_object));
	if (newnode == NULL)
		return (NULL);
	return (newnode);
}
