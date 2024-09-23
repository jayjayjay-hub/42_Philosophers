/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:45:30 by jtakahas          #+#    #+#             */
/*   Updated: 2024/09/23 18:31:45 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// philosopher : eat -> sleep -> think -> eat -> sleep -> think -> ...
bool	get_forks(t_data *data)
{
	if (data->philos->id % 2 == 0)
	{
		pthread_mutex_lock(data->philos->right_fork);
		pthread_mutex_lock(data->philos->left_fork);
	}
	else
	{
		pthread_mutex_lock(data->philos->left_fork);
		pthread_mutex_lock(data->philos->right_fork);
	}
	data->philos->is_eating = true;
	if (data->stop_simulation)
	{
		pthread_mutex_unlock(data->philos->left_fork);
		pthread_mutex_unlock(data->philos->right_fork);
		return (false);
	}
	log_event(data, data->philos->id, "has taken a fork");
	return (true);
}

void	put_forks(t_data *data)
{
	pthread_mutex_unlock(data->philos->left_fork);
	pthread_mutex_unlock(data->philos->right_fork);
	data->philos->is_eating = false;
}

bool	eat(t_data *data)
{
	if (data->stop_simulation)
		return (false);
	data->philos->last_meal_time = get_time_in_ms();
	log_event(data, data->philos->id, "is eating");
	usleep(data->conditions.time_to_eat * 1000);
	return (true);
}

void	*philosopher_lifecycle(void *arg)
{
	t_philos (*philos) = (t_philos *)arg;
	while (!philos->data->stop_simulation)
	{
		if (!get_forks(philos->data))
			break ;
		if (!eat(philos->data))
			break ;
		put_forks(philos->data);
		if (philos->data->stop_simulation)
			break ;
		log_event(philos->data, philos->id, "is sleeping");
		usleep(philos->data->conditions.time_to_sleep * 1000);
		if (philos->data->stop_simulation)
			break ;
		log_event(philos->data, philos->id, "is thinking");
	}
	return (NULL);
}