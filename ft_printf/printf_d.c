/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:37:56 by kotkobay          #+#    #+#             */
/*   Updated: 2023/10/16 13:05:05 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_d(int n)
{
	char	*num;
	int		count;

	count = 0;
	num = ft_itoa(n);
	if (!num)
		return (-1);
	count = write(1, num, ft_strlen(num));
	free(num);
	return (count);
}
