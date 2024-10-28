/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:26:20 by kotkobay          #+#    #+#             */
/*   Updated: 2024/10/28 22:11:47 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_forks	*init_forks(int number_of_forks)
{
	t_forks	*forks;
	int		i;

	forks = NULL;
	forks->number_of_forks = number_of_forks;
	forks->mutex = malloc(number_of_forks * sizeof(pthread_mutex_t));
	if (!forks->mutex)
	{
		exit_with_message("Error");
	}
	i = 0;
	while (i < number_of_forks)
	{
		pthread_mutex_init(&forks->mutex[i], NULL);
		i++;
	}
	return (forks);
}

void	print_forks(t_forks *forks)
{
	printf("Number of forks: %d\n", forks->number_of_forks);
	for (int i = 0; i < forks->number_of_forks; i++)
	{
		printf("Fork %d mutex address: %p\n", i, (void *)&forks->mutex[i]);
	}
}
