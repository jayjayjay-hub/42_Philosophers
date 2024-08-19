/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:45:33 by jay               #+#    #+#             */
/*   Updated: 2024/08/19 19:07:23 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_check(argc, argv, &data))
		return (1);
	printf("Philo: %lu\n TimeToDie: %lu\n TimeToEat: %lu\n TimeToSleep: %lu\n NumOfTimesToEat: %lu\n",
		data.args[0], data.args[1], data.args[2], data.args[3], data.args[4]);
	return (0);
}
