/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:18:28 by mawinter          #+#    #+#             */
/*   Updated: 2022/12/09 12:28:54 by mawinter         ###   ########.fr       */
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
