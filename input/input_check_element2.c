/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_element2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:45:52 by mawinter          #+#    #+#             */
/*   Updated: 2022/11/30 12:33:13 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	valid_cylinder(char *line)
{
	char	**fields;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	fields = ft_split(line, ' ');
	if (!fields && write(2, MALLOC_FAIL, 19))
		return (FALSE);
	if (fields_count(fields) != 6 && free_split(fields)
		&& write(2, CY_WRONG_NUM_FIELDS, 40))
		return (FALSE);
	if (!valid_triple_field(fields[1], 0.0L, 0.0L, 0))
		return (FALSE);
	if (!valid_triple_field(fields[2], -1.0L, 1.0L, 0))
		return (FALSE);
	if (isnan(get_num(fields[3], 0.0L, INFINITY, 0)) && free_split(fields))
		return (FALSE);
	if (isnan(get_num(fields[4], 0.0L, INFINITY, 0)) && free_split(fields))
		return (FALSE);
	if (!valid_triple_field(fields[5], 0.0L, 255.0L, 1))
		return (FALSE);
	return (TRUE);
}
