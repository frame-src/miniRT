/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:59:37 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/13 11:38:59 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_object	*ft_objnew(void)
{
	t_object	*newnode;

	newnode = ft_calloc(1, sizeof(t_object));
	if (newnode == NULL)
		return (NULL);
	return (newnode);
}
