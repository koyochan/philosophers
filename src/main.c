/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:32:03 by kotkobay          #+#    #+#             */
/*   Updated: 2024/10/28 22:34:06 by kotkobay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }

void	argument_assignment(int ac, char **av, t_argument **argument)
{
	(*argument)->number_of_philosophers = ft_atod(av[1]);
	(*argument)->time_to_die = ft_atod(av[2]);
	(*argument)->time_to_eat = ft_atod(av[3]);
	(*argument)->time_to_sleep = ft_atod(av[4]);
	if (ac == 6)
		(*argument)->times_must_eat = ft_atod(av[5]);
	else
		(*argument)->times_must_eat = -1;
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
	t_argument	argument;
	t_timeval	timeval;
	t_forks		*forks;

	if (ac != 5 && ac != 6)
		exit_with_message("usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
	parse_argument(ac, av, &argument);
	forks = init_forks(argument.number_of_philosophers);
	print_forks(forks);
	// printf("Arguments:\n");
	// printf("number_of_philosophers: %d\n", argument.number_of_philosophers);
	// printf("time_to_die: %d\n", argument.time_to_die);
	// printf("time_to_eat: %d\n", argument.time_to_eat);
	// printf("time_to_sleep: %d\n", argument.time_to_sleep);
	// printf("times_must_eat: %d\n", argument.times_must_eat);
	if (gettimeofday(&timeval, NULL) == 0)
	{
		printf("%ld %d has taken a fork\n", timeval.tv_sec,
			argument.number_of_philosophers);
	}
	else
	{
		exit_with_message("Error: gettimeofday failed");
	}
	operation_thread(&argument);
}
