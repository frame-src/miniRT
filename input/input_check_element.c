/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:43:57 by mawinter          #+#    #+#             */
/*   Updated: 2022/10/31 15:26:31 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	valid_ambient(char *line)
{
	char	**fields;

	line[ft_strlen(line) -1] = '\0';
	fields = ft_split(line, ' ');
	if (!fields && write(2, MALLOC_FAIL, 19))
		return (FALSE);
	if (fields_count(fields) != 3 && free_split(fields)
		&& write(2, A_WRONG_NUM_FIELDS, 45))
		return (FALSE);
	if (isnan(get_num(fields[1], 0.0L, 1.0L, 0)) && free_split(fields))
		return (FALSE);
	if (!valid_triple_field(fields[2], 0.0L, 255.0L, 1)
		&& free_split(fields))
		return (FALSE);
	free(fields);
	return (TRUE);
}


int	valid_camera(char *line)
{
	char	**fields;

	line[ft_strlen(line) -1] = '\0';
	fields = ft_split(line, ' ');
	if (!fields && write(2, MALLOC_FAIL, 19))
		return (FALSE);
	if (fields_count(fields) != 4 && free_split(fields)
		&& write(2,C_WRONG_NUM_FIELDS, 38))
		return (FALSE);
	if (!valid_triple_field(fields[1], 0.0L, 0.0L, 0))
		return (FALSE);
	if (!valid_triple_field(fields[2], -1.0L, 1.0L, 0))
		return (FALSE);
	if (isnan(get_num(fields[3], 0.0L, 180.0L, 1)) && free_split(fields))
		return (FALSE);

	return (TRUE);
}

int	valid_light(char *line)
{
	char	**fields;

	line[ft_strlen(line) -1] = '\0';
	fields = ft_split(line, ' ');
	if (!fields && write(2, MALLOC_FAIL, 19))
		return (FALSE);
	if (fields_count(fields) != 4 && free_split(fields)
		&& write(2, L_WRONG_NUM_FIELDS, 37))
		return (FALSE);
	if (!valid_triple_field(fields[1], 0.0L, 0.0L, 0))
		return (FALSE);
	if (isnan(get_num(fields[2], 0.0L, 1.0L, 0)) && free_split(fields))
		return (FALSE);
	if (!valid_triple_field(fields[3], 0.0L, 255.0L, 1))
		return (FALSE);
	return (TRUE);
}


int	valid_sphere(char *line)
{
	char	**fields;

	line[ft_strlen(line) -1] = '\0';
	fields = ft_split(line, ' ');
	if (!fields && write(2, MALLOC_FAIL, 19))
		return (FALSE);
	if (fields_count(fields) != 4 && free_split(fields)
		&& write(2, SP_WRONG_NUM_FIELDS, 38))
		return (FALSE);
	if (!valid_triple_field(fields[1], 0.0L, 0.0L, 0))
		return (FALSE);
	if (isnan(get_num(fields[2], 0.0L, INFINITY, 0)) && free_split(fields))
		return (FALSE);
	if (!valid_triple_field(fields[3], 0.0L, 255.0L, 1))
		return (FALSE);
	return (TRUE);
}


int	valid_plane(char *line)
{
	char	**fields;

	line[ft_strlen(line) -1] = '\0';
	fields = ft_split(line, ' ');
	if (!fields && write(2, MALLOC_FAIL, 19))
		return (FALSE);
	if (fields_count(fields) != 4 && free_split(fields)
		&& write(2, PL_WRONG_NUM_FIELDS, 37))
		return (FALSE);
	if (!valid_triple_field(fields[1], 0.0L, 0.0L, 0))
		return (FALSE);
	if (!valid_triple_field(fields[2], -1.0L, 1.0L, 0))
		return (FALSE);
	if (!valid_triple_field(fields[3], 0.0L, 255.0L, 1))
		return (FALSE);
	return (TRUE);
}

