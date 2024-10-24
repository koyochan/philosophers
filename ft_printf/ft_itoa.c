/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:53:56 by kotkobay          #+#    #+#             */
/*   Updated: 2023/10/16 13:01:05 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	digit_count(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	int				len;
	char			*res;

	len = digit_count(n);
	if (n < 0)
		num = -n;
	else
		num = n;
	res = (char *)malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	while (len--)
	{
		res[len] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++ != 0)
		count++;
	return (count);
}

/* int	main(void)
{
	printf("%s\n", ft_itoa(123131));
}
 */