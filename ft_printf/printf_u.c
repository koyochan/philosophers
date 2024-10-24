/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:57:56 by kotkobay          #+#    #+#             */
/*   Updated: 2023/10/16 13:29:37 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	digit_unsigned_int(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_uinttoa(unsigned int n)
{
	int		len;
	char	*res;

	len = digit_unsigned_int(n);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	while (len--)
	{
		res[len] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}

int	printf_u(unsigned int n)
{
	char	*num;
	int		count;

	count = 0;
	num = ft_uinttoa(n);
	count = write(1, num, ft_strlen(num));
	free(num);
	return (count);
}
