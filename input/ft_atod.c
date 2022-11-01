/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 03:08:55 by marius            #+#    #+#             */
/*   Updated: 2022/10/30 22:12:07 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double getfirst(char **field, double *sign)
{
	double first;

	*sign = 1;
	first = 0;
	while (**field && **field != '.')
	{
		if (**field == '-')
			*sign = -1;
		else
			first = first * 10 + (**field - '0');
		*field = *field + 1;
	}
	return (first);
}

double   ft_atod(char *field)
{
    double	first;
    double	second;
	int		digits;
	double	divisor;
	double	sign;

	sign = 1;
	divisor = 1;
	second = 0;
	first = getfirst(&field, &sign);
	digits = 0;
	if (*field)
		field++;
	while (*field)
	{
		digits++;
		second = second * 10 + (*field - '0');
		field++;
	}
	while (digits--)
		divisor *= 10;
	if (sign < 0)
		return (sign * first - second / divisor);
	return (first + second / divisor);
}