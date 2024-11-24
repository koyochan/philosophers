/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:32:03 by kotkobay          #+#    #+#             */
/*   Updated: 2024/11/24 15:17:08 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }

void	argument_assignment(int ac, char **av, t_argument **argument)
{
	(*argument)->stop_simulation = 0;
    (*argument)->total_eat_count = 0; 
	(*argument)->number_of_philosophers = ft_atod(av[1]);
	(*argument)->time_to_die = ft_atod(av[2]);
	(*argument)->time_to_eat = ft_atod(av[3]);
	(*argument)->time_to_sleep = ft_atod(av[4]);
	if (ac == 6)
		(*argument)->times_must_eat = ft_atod(av[5]);
	else
		(*argument)->times_must_eat = -1;
	if (pthread_mutex_init(&(*argument)->end_mutex, NULL) != 0)
    {
		free(*argument); 
       	exit_with_message("Mutex Error");
    }

    if (pthread_mutex_init(&(*argument)->eat_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&(*argument)->end_mutex); 
		free(*argument); 
      	exit_with_message("Mutex Error");
    }
}

void	parse_argument(int ac, char **av, t_argument *argument)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (('0' <= av[i][j] && av[i][j] <= '9') || av[i][j] == '.'
				|| av[i][j] == '+')
				j++;
			else
			{
				exit_with_message("Error\n");
			}
		}
		i++;
	}
	argument_assignment(ac, av, &argument);
}

int	main(int ac, char **av)
{
	t_argument	*argument;
	t_forks		*forks;
	t_timeval	start_timeval;
	long		start_time_in_ms;

	if (gettimeofday(&start_timeval, NULL) != 0)
	{
		exit_with_message("Gettimeofday Error");
		return (1);
	}
	start_time_in_ms = (start_timeval.tv_sec * 1000) + (start_timeval.tv_usec
			/ 1000);
	if (ac != 5 && ac != 6)
		exit_with_message("usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
	argument = malloc(sizeof(t_argument));
    if (!argument)
    {
        exit_with_message("Malloc Error");
    }

	parse_argument(ac, av, &(*argument));
	forks = init_forks(argument->number_of_philosophers);
	operation_thread(&(*argument), forks, start_time_in_ms);
	return (0);
}
