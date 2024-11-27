/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secound_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:16:52 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/26 06:42:31 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/philo.h"

// void	exit_with_message(char *msg)
// {
// 	printf("%s\n", msg);
// 	exit(1);
// }

// void	print_time_stamp_with_message(t_philosophers *philo, char *mes)
// {
// 	t_timeval	timeval;
// 	long		current_time_in_ms;
// 	long		elapsed_time;

// 	if (gettimeofday(&timeval, NULL) == 0)
// 	{
// 		current_time_in_ms = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
// 		elapsed_time = current_time_in_ms - philo->start_time_in_ms;
// 		printf("%ld %d %s\n", elapsed_time, philo->id, mes);
// 	}
// 	else
// 	{
// 		exit_with_message("Error: gettimeofday failed");
// 	}
// 	return ;
// }
