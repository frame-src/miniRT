/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:12:39 by marius            #+#    #+#             */
/*   Updated: 2022/10/30 22:29:08 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	fields_count(char **fields)
{
	int	len;
	
	len = 0;
	while (fields[len])
		len++;
	return (len);
}

int	valid_triple_field(char *field, double min, double max, int is_in)
{
	char **triple;
	int		i;

	i = 0;
	triple = ft_split(field, ',');
	if (!triple && write(2, MALLOC_FAIL, 19) && free_split(triple))
		return (FALSE);
	if (fields_count(triple) != 3 && write(2, NUM3, 35)
		&& free_split(triple))
		return (FALSE);
	while(triple[i])
	{
		if (isnan(get_num(triple[i], min, max, is_in)) && free_split(triple))
			return (FALSE);
		i++;
	}
	free_split(triple);
	return (TRUE);
}


double	ret_num(int *dotcount, char *field, double range[2], int is_int)
{
	double res;


	res = ft_atod(field);
	if (is_int)
	{
		if (*dotcount)
		{
			write(2, NO_FLOAT, 37);
			return (NAN);
		}
	}
	else
	{
		if (1 < *dotcount)
		{
			write(2, MANY_DECIMAL, 49);
			return (NAN);
		}
	}
	if(!in_range(res, range[0], range[1]))
	{
			write(2, RANGE, 27);
			return (NAN);
	}
	return (res);
}

/*Pass Allowed Range, or 0,0 If No Cap*/
/*Return Value is NaN if wrong input, val if true*/
/*is_int = 1 -> integers only, 0 -> float*/
double	get_num(char *field, double min, double max, int is_int)
{
	int	i;
	int	dotcount;
	double	range[2];

	range[0] = min;
	range[1] = max;
	i = -1;
	dotcount = 0;
	while (field[++i])
	{
		if ((!ft_isdigit(field[i]) && field[i] != '.' && field[i] != '-') && write(2, WRONG_CHAR, 23))
			return (NAN);
		if (field[i] == '.' && ++dotcount)
		{
			if (dotcount == 2)
				return (NAN);
			if ((i == 0 || i == ft_strlen(field) - 1)
				&& write(2, TRAIL_DECIMAL_POINT, 53))
				return (NAN);
		}
		if (((field[i] == '-' && i != 0 )|| (field[i] == '-' && field[i + 1] == '.')) && write(2, MINUS_POS, 35))
				return (NAN);
	}
	return (ret_num(&dotcount, field, range, is_int));
}