/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:31:56 by kotkobay          #+#    #+#             */
/*   Updated: 2024/05/05 14:01:08 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_sign_part(const char **str)
{
	int	sign;

	sign = 1;
	while ((9 <= **str && **str <= 13) || **str == ' ')
		(*str)++;
	while (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign *= -1;
		(*str)++;
	}
	return (sign);
}

double	parse_integer_part(const char **str)
{
	double	result;

	result = 0.0;
	while ('0' <= **str && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

double	parse_fraction_part(const char **str)
{
	double		fraction;
	long long	divisor;

	fraction = 0.0;
	divisor = 1;
	if (**str == '.')
	{
		(*str)++;
		while ('0' <= **str && **str <= '9')
		{
			fraction = fraction * 10.0 + (**str - '0');
			divisor *= 10;
			(*str)++;
		}
	}
	return (fraction / divisor);
}

double	ft_atod(const char *str)
{
	double	result;
	int		sign;
	double	fraction;

	sign = parse_sign_part(&str);
	result = parse_integer_part(&str);
	fraction = parse_fraction_part(&str);
	return (sign * (result + fraction));
}

void	exit_with_message(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}
