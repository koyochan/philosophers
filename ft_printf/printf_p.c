/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:49:28 by kotkobay          #+#    #+#             */
/*   Updated: 2023/10/16 13:05:09 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_p(char *result)
{
	int		count;
	char	*orig_result;

	orig_result = result;
	count = 0;
	count = write(1, "0x", 2);
	count += write(1, result, ft_strlen(result));
	free(orig_result);
	return (count);
}

int	printf_p(void *p)
{
	char		*result;
	int			count;
	char		*hex;
	uintptr_t	tmp;
	uintptr_t	num;

	num = (uintptr_t)p;
	hex = "0123456789abcdef";
	tmp = num;
	count = 1;
	while (tmp / 16)
	{
		tmp /= 16;
		count++;
	}
	result = (char *)malloc(sizeof(char) * (count + 1));
	if (!result)
		return (-1);
	result[count] = '\0';
	while (count-- > 0)
	{
		result[count] = hex[num % 16];
		num /= 16;
	}
	return (write_p(result));
}
