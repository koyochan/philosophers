/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:26:20 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/06 12:18:29 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_forks	*init_forks(int number_of_forks)
{
	t_forks	*forks;
	int		i;

	forks = malloc(sizeof(t_forks));
	if (!forks)
	{
		exit_with_message("Error: Could not allocate memory for forks");
	}
	forks->mutex = malloc(number_of_forks * sizeof(pthread_mutex_t));
	if (!forks->mutex)
	{
		exit_with_message("Error");
	}
	forks->number_of_forks = number_of_forks;
	i = 0;
	while (i < number_of_forks)
	{
		pthread_mutex_init(&forks->mutex[i], NULL);
		i++;
	}
	return (forks);
}
