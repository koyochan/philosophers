/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:55:05 by kotkobay          #+#    #+#             */
/*   Updated: 2023/10/16 13:01:28 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
int		printf_d(int n);
int		printf_p(void *p);
int		printf_s(char *s);
int		printf_u(unsigned int n);
int		printf_x(unsigned int num);
int		printf_capital_x(unsigned int num);
char	*ft_itoa(int n);
int		ft_printf(const char *s, ...);
int		digit_count(int n);
char	*hex(unsigned int num, char *hex);

#endif