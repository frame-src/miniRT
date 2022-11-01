/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:18:28 by mawinter          #+#    #+#             */
/*   Updated: 2022/10/28 15:27:48 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	i_identifier(char **identifiers, char *identifier)
{
	int	i;

	i = 0;
	while (identifiers[i])
	{
		if (!ft_strcmp(identifiers[i], identifier))
			return (i);
		i++;
	}
	return (-1);
}